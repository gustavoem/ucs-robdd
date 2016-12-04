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
            delete pX;
        }
    }


    void partition_minimum (Partition * P, Collection * L,
        CostFunction * c, unsigned int max_size_of_minima_list)
    {
        ElementSet * elm_set = P->get_original_set ();
        PartitionCost * p_cost = new PartitionCost (c, P);
        Solver * sub_solver = new ExhaustiveSearch ();
        sub_solver->set_parameters (p_cost, elm_set, false);
        sub_solver->find_minima_list (max_size_of_minima_list);
        list<ElementSubset *> p_min_lst;
        p_min_lst = sub_solver->get_minima_list ();
        update_minima_list (L, P, &p_min_lst);
    }

    void find_minimum (Partition * P, Collection * L, CostFunction * c, 
        unsigned int max_size_of_minima_list)
    {
        
        partition_minimum (P, L, c, max_size_of_minima_list);
    }
    
 //     void random_walk (Partition * P, ROBDD * pt_robdd, 
 //         CostFunction * c, Collection * L, 
 //         unsigned int max_size_of_minima_list)
 //     {
 //         find_minimum (P, L);
 //     }

}