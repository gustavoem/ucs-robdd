#include "PUCSR1ToolBox.h"

namespace PUCSR1ToolBox 
{

    void update_minima_list (Collection * L, PartitionNode * P,
        list<ElementSubset *> * l)
    {
        // cout << "List of minima: " << endl;
        while (l->size () > 0) 
        {
            ElementSubset * pX = l->back ();
            // cout << pX->print_subset () << ": " << pX->cost << endl;
            l->pop_back ();
            ElementSubset * X = P->get_original_subset (pX);
            X->cost = pX->cost;
            // cout << X->print_subset () << ": " << X->cost << endl;
            L->add_subset (X);
            delete X;
            delete pX;
        }
    }


    void partition_minimum (PartitionNode * P, Collection * L,
        CostFunction * c, unsigned int max_size_of_minima_list)
    {
        list<ElementSubset *> p_min_lst;
        // cout << "Finding the minimum of " << P->get_minimal_element ()->print_subset () << endl;
        PartitionModel * p_model = P->get_partition_model ();
        ElementSet * p_elm_set = p_model->get_unfixed_elm_set ();
        if (p_elm_set->get_set_cardinality () == 0)
        {
            ElementSubset * minimal = P->get_minimal_element ();    
            minimal->cost = c->cost (minimal);
            p_min_lst.push_back (minimal);
        }
        else
        {
            PartitionCost * p_cost = new PartitionCost (c, P);
            Solver * sub_solver = new ExhaustiveSearch ();
            sub_solver->set_parameters (p_cost, p_elm_set, false);
            sub_solver->find_minima_list (max_size_of_minima_list);
            p_min_lst = sub_solver->get_minima_list ();
            delete p_cost;
            delete sub_solver;
        }
        update_minima_list (L, P, &p_min_lst);
        // cout << "Minima List Collection: " << endl;
        // cout << L->print_collection () << endl;
    }


    PartitionNode * adjacent_partition (PartitionNode * P, 
        unsigned int i)
    {
        ElementSubset * sel_elms = P->get_selected_elements ();
        if (sel_elms->has_element (i))
            sel_elms->remove_element (i);
        else
            sel_elms->add_element (i);
        PartitionModel * part_model = P->get_partition_model ();
        PartitionNode * Q = new PartitionNode (part_model, sel_elms);
        delete sel_elms;
        return Q;
    }


    //  we can make this uglier but faster
    PartitionNode * prune_and_walk (PartitionNode * P, PartitionNode * Q, 
        CostFunction * c, ROBDD * R) 
    {
        PartitionNode * P1, * P2, * next;
        ElementSubset * e1, * e2;
        ElementSubset * p_sub = P->get_minimal_element ();
        ElementSubset * q_sub = Q->get_minimal_element ();
        if (P->is_upper_adjacent (Q))
            P1 = P, P2 = Q;
        else
            P1 = Q; P2 = P;
        
        e1 = P1->get_minimal_element ();
        e2 = P2->get_minimal_element ();
        if (c->cost (e1) > c->cost (e2)) 
        {
            if (e1->is_equal (p_sub))
                cout << "heyo! " << e1->print_subset () << endl;
            R->add_interval (e1, true);
        }
        delete e1;
        delete e2;
        e1 = P1->get_maximal_element ();
        e2 = P2->get_maximal_element ();
        if (c->cost (e1) < c->cost (e2))
        {
            if (e2->is_equal (p_sub))
                cout << "heyo! " << e2->print_subset () << endl;
            R->add_interval (e2, false);
        }
        delete e1;
        delete e2;
        next = Q;
        if (R->contains (q_sub))
        {
            if (R->contains (p_sub))
                next = NULL;
            else
                next = P;
        }
        delete p_sub;
        delete q_sub;
        return next;
    }

    
    void random_walk (PartitionNode * P, ROBDD * pt_robdd, 
         CostFunction * c, Collection * L, 
         unsigned int max_size_of_minima_list)
    {
        unsigned int i = 0;
        unsigned int n = P->get_number_of_fixed_elms ();
        partition_minimum (P, L, c, max_size_of_minima_list);
        restrict_partition (P, pt_robdd);
        PartitionNode * Q;
        while (i < n)
        {
            Q = adjacent_partition (P, i++);
            if (is_restricted (Q, pt_robdd)) 
            {
                delete Q;
                continue;
            }
            // cout << "Partition: " << P->get_minimal_element ()->print_subset () << endl;
            PartitionNode * next;
            next = prune_and_walk (P, Q, c, pt_robdd);
            if (next == P)
                delete Q;
            else if (next == Q)
            {
                i = 0;
                delete P;
                P = Q;
                // cout << "Now going to Q: " << Q->get_minimal_element ()->print_subset () << endl;
                partition_minimum (P, L, c, max_size_of_minima_list);
                restrict_partition (P, pt_robdd);
            }
            else
            {
                delete P;
                delete Q;
                return;
            }
        }
        delete P;
    }

    bool is_restricted (PartitionNode * P, ROBDD * R) 
    {
        bool answ = false;
        ElementSubset * p_subset = P->get_selected_elements ();
        if (R->contains (p_subset))
            answ = true;
        delete p_subset;
        return answ;
    }

    void restrict_partition (PartitionNode * P, ROBDD * R)
    {
        ElementSubset * p_subset = P->get_selected_elements ();
        R->add_subset (p_subset);
        delete p_subset;
    }
}