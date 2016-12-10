#include "PUCSR1ToolBox.h"

namespace PUCSR1ToolBox 
{

    void update_minima_list (Collection * L, Partition * P,
        list<ElementSubset *> * l)
    {
        while (l->size () > 0) 
        {
            ElementSubset * pX = l->back ();
            l->pop_back ();
            ElementSubset * X = P->get_original_subset (pX);
            L->add_subset (X);
            delete X;
            delete pX;
        }
    }


    void partition_minimum (Partition * P, Collection * L,
        CostFunction * c, unsigned int max_size_of_minima_list)
    {
        PartitionModel * p_model = P->get_partition_model ();
        ElementSet * p_elm_set = p_model->get_unfixed_elm_set ();
        PartitionCost * p_cost = new PartitionCost (c, P);
        Solver * sub_solver = new ExhaustiveSearch ();
        sub_solver->set_parameters (p_cost, p_elm_set, false);
        sub_solver->find_minima_list (max_size_of_minima_list);
        list<ElementSubset *> p_min_lst;
        p_min_lst = sub_solver->get_minima_list ();
        update_minima_list (L, P, &p_min_lst);
        delete p_cost;
        delete sub_solver;
    }


    Partition * adjacent_partition (Partition * P, unsigned int i)
    {
        ElementSubset * sel_elms = P->get_selected_elements ();
        if (sel_elms->has_element (i))
            sel_elms->remove_element (i);
        else
            sel_elms->add_element (i);
        PartitionModel * part_model = P->get_partition_model ();
        Partition * Q = new Partition (part_model, sel_elms);
        delete sel_elms;
        return Q;
    }


    //  we can make this uglier but faster
    Partition * prune_and_walk (Partition * P, Partition * Q, 
        CostFunction * c, ROBDD * R) 
    {
        Partition * P1, * P2, * next;
        ElementSubset * e1, * e2;
        if (P->is_upper_adjacent (Q))
            P1 = P, P2 = Q;
        else
            P1 = Q; P2 = P;
        
        e1 = P1->get_minimal_element ();
        e2 = P2->get_minimal_element ();
        if (c->cost (e1) > c->cost (e2)) 
            R->add_interval (e1, true);
        delete e1;
        delete e2;
        e1 = P1->get_maximal_element ();
        e2 = P2->get_maximal_element ();
        if (c->cost (e1) < c->cost (e2))
            R->add_interval (e2, false);
        delete e1;
        delete e2;
        ElementSubset * p_sub = P->get_selected_elements ();
        ElementSubset * q_sub = P->get_selected_elements ();
        next = P;
        if (R->contains (p_sub))
        {
            if (R->contains (q_sub))
                next = NULL;
            else
                next = Q;
        }
        delete p_sub;
        delete q_sub;
        return next;
    }
    
    
    void random_walk (Partition * P, ROBDD * pt_robdd, 
         CostFunction * c, Collection * L, 
         unsigned int max_size_of_minima_list)
    {
        unsigned int i = 0;
        unsigned int n = P->get_number_of_fixed_elms ();
        Partition * Q = adjacent_partition (P, i++);
        while (i < n)
        {
            Partition * next;
            partition_minimum (P, L, c, max_size_of_minima_list);
            next = prune_and_walk (P, Q, c, pt_robdd);
            
            if (next == P)
                i++;
            else if (next == Q)
            {
                i = 0;
                free (P);
                P = Q;
            }
            else
            {
                free (P);
                free (Q);
                return;
            }
        }
    }

}