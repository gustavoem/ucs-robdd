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


    Partition * adjacent_partition (Partition * P, unsigned int i)
    {
        ElementSubset * sel_elms = P->get_selected_elements ();
        unsigned int n = sel_elms->get_set_cardinality ();
        if (i >= n || i < 0)
            return NULL;

        if (sel_elms->has_element (i))
            sel_elms->remove_element (i);
        else
            sel_elms->add_element (i);
        PartitionModel * part_model = P->get_partition_model ();
        Partition * Q = new Partition (part_model, sel_elms);
        delete sel_elms;
        return Q;
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
    
    void random_walk (Partition * P, ROBDD * pt_robdd, 
         CostFunction * c, Collection * L, 
         unsigned int max_size_of_minima_list)
     {
        unsigned int i = 0;
        Partition * Q = adjacent_partition (P, i++);
        while (Q != NULL)
        {

        }

        // partition_minimum (P, L, c, max_size_of_minima_list);
     }

}