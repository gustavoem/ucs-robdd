#include "PUCSR1ToolBox.h"

namespace PUCSR1ToolBox 
{

    void create_minima_list (Collection * L, PartitionNode * P,
        list<ElementSubset *> * l)
    {
        while (l->size () > 0) 
        {
            ElementSubset * pX = l->back ();
            // cout << "pX: " << pX->print_subset () << endl;
            l->pop_back ();
            // cout.flush ();
            ElementSubset * X = P->get_original_subset (pX);
            // cout << "X: " << X->print_subset () << endl;
            X->cost = pX->cost;
            L->add_subset (X);
            delete X;
            delete pX;
        }
    }


    Collection * part_minimum (PartitionNode * P,
        CostFunction * c, unsigned int max_size_of_minima_list)
    {
        Collection * L = new Collection ();
        list<ElementSubset *> p_min_lst;
        Partition * partition = P->get_partition ();
        ElementSet * p_elm_set = partition->get_unfixed_elm_set ();
        /*debug*/
        // ElementSubset * sel_elms = P->get_selected_elements ();
        // cout << "Part: " << sel_elms->print_subset () << endl;
        /*debug*/
        if (p_elm_set->get_set_cardinality () == 0)
        {
            ElementSubset * minimal = P->get_least_subset ();
            minimal->cost = c->cost (minimal);
            p_min_lst.push_back (minimal);
        }
        else
        {
            PartitionCost * P_cost = new PartitionCost (c, P);
            Solver * sub_solver = new ExhaustiveSearch ();
            sub_solver->set_parameters (P_cost, p_elm_set, false);
            sub_solver->find_minima_list (max_size_of_minima_list);
            p_min_lst = sub_solver->get_minima_list ();
            delete P_cost;
            delete sub_solver;
        }
        create_minima_list (L, P, &p_min_lst);
        return L;
    }


    PartitionNode * adjacent_part (PartitionNode * P, 
        unsigned int i)
    {
        ElementSubset * sel_elms = P->get_selected_elements ();
        if (sel_elms->has_element (i))
            sel_elms->remove_element (i);
        else
            sel_elms->add_element (i);
        Partition * partition = P->get_partition ();
        PartitionNode * Q = new PartitionNode (partition, sel_elms);
        delete sel_elms;
        return Q;
    }


    PartitionNode * prune_and_walk (PartitionNode * P, PartitionNode * Q, 
        CostFunction * c, ROBDD * R) 
    {
        PartitionNode * P1, * P2, * next;
        ElementSubset * e1, * e2;
        ElementSubset * p_sub = P->get_least_subset ();
        ElementSubset * q_sub = Q->get_least_subset ();
        if (P->is_upper_adjacent (Q))
            P1 = P, P2 = Q;
        else
            P1 = Q; P2 = P;
        
        e1 = P1->get_least_subset ();
        e2 = P2->get_least_subset ();
        if (c->cost (e1) > c->cost (e2)) 
            R->add_interval (e1, true);
        delete e1;
        delete e2;
        e1 = P1->get_greatest_subset ();
        e2 = P2->get_greatest_subset ();
        if (c->cost (e1) < c->cost (e2))
            R->add_interval (e2, false);
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

    bool is_restricted (PartitionNode * P, ROBDD * R) 
    {
        bool answ = false;
        ElementSubset * p_subset = P->get_selected_elements ();
        if (R->contains (p_subset))
            answ = true;
        delete p_subset;
        return answ;
    }

    void restrict_part (PartitionNode * P, ROBDD * R)
    {
        ElementSubset * p_subset = P->get_selected_elements ();
        R->add_subset (p_subset);
        delete p_subset;
    }
}