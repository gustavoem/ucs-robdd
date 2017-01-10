#include "PUCSR1ToolBox.h"

namespace PUCSR1ToolBox 
{

    void create_minima_list (Collection * L, PartitionNode * P,
        list<ElementSubset *> * l)
    {
        while (l->size () > 0) 
        {
            ElementSubset * pX = l->back ();
            l->pop_back ();
            ElementSubset * X = P->get_original_subset (pX);
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
        if (p_elm_set->get_set_cardinality () == 0)
        {
            ElementSubset * minimal = P->get_least_subset ();
            minimal->cost = c->cost (minimal);
            p_min_lst.push_back (minimal);
        }
        else
        {
            Solver * sub_solver;
            if (p_elm_set->get_set_cardinality () > UCS_CUTOFF)
                sub_solver = new PUCSR1 ();
            else
                sub_solver = new UCSROBDD6 ();
            PartitionCost * P_cost = new PartitionCost (c, P);
            sub_solver->set_parameters (P_cost, p_elm_set, false);
            // TODO: does it run faster when we run the next line as a
            // task?
            sub_solver->find_minima_list (max_size_of_minima_list);
            #pragma omp taskwait
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
        ElementSubset * e1, * e2, * p1_sub, * p2_sub;
        ElementSubset * p_sub = P->get_least_subset ();
        ElementSubset * q_sub = Q->get_least_subset ();
        if (P->is_upper_adjacent (Q))
            P1 = P, P2 = Q;
        else
            P1 = Q; P2 = P;
        p1_sub = P1->get_selected_elements ();
        p2_sub = P2->get_selected_elements ();
        e1 = P1->get_least_subset ();
        e2 = P2->get_least_subset ();
        if (c->cost (e1) > c->cost (e2)) 
            R->add_interval (p1_sub, true);
        delete e1;
        delete e2;
        e1 = P1->get_greatest_subset ();
        e2 = P2->get_greatest_subset ();
        if (c->cost (e1) < c->cost (e2))
            R->add_interval (p2_sub, false);
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
        delete p1_sub;
        delete p2_sub;
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