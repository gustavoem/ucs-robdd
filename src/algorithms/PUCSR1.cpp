#include "PUCSR1.h"

PUCSR1::PUCSR1 ()
{
    list_of_visited_subsets = new Collection ();
    cost_function = NULL;
    cand_part = NULL;
    partition = NULL;
}


PUCSR1::~PUCSR1 ()
{
    if (list_of_visited_subsets != NULL)
        delete list_of_visited_subsets;
    if (cand_part != NULL)
        delete cand_part;
    if (partition != NULL)
        delete partition;
}


void PUCSR1::set_partition_model ()
{
    unsigned int set_size = set->get_set_cardinality ();
    unsigned int partition_set_size = set_size * (1 / 2.0) + 1;
    bool * fixed = new bool[set_size];
    for (unsigned int i = 0; i < set_size; i++)
        fixed[i] = false;
    // This is a simple way to partitionate the space. We are choosing
    // the last <partition_set_size> variables of the element set to be
    // free in every subproblem and fixing the other variables
    // for (unsigned int i = 0; i < set_size; i++)
    //     if (i < partition_set_size)
    //         fixed[i] = true;
    //     else
    //         fixed[i] = false;

    // Random partitioning
    ElementSubset X ("", set);
    X.set_complete_subset ();
    for (unsigned int i = 0; i < partition_set_size; i++)
    {
        unsigned int e = X.remove_random_element ();
        // cout << "Fixing: " << e << endl;
        fixed[e] = true;
    }
    this->partition = new Partition (set, fixed);
    delete[] fixed;
}   


void PUCSR1::find_minima_list (unsigned int max_size_of_minima_list)
{
    timeval begin_program, end_program;
    gettimeofday (& begin_program, NULL);

    list<PartitionNode *> parts_to_solve;
    ElementSubset * p_subset;
    set_partition_model ();
    cand_part = new ROBDD (partition->get_fixed_elm_set ());

    p_subset = cand_part->get_random_zero_evaluated_element ();
    while (p_subset != NULL)
    {
        PartitionNode * P = new PartitionNode (partition, p_subset);
        random_walk (P, &parts_to_solve);
        delete p_subset;
        p_subset = cand_part->get_random_zero_evaluated_element ();
    }

    list<ElementSubset *> * min_list = &list_of_minima;
    #pragma omp parallel shared (min_list, parts_to_solve)
    #pragma omp single
    solve_parts (&parts_to_solve, min_list, max_size_of_minima_list);
    #pragma omp taskwait
    number_of_visited_subsets =  
        cost_function->get_number_of_calls_of_cost_function ();
    number_of_restrictions_consults = 0;
    number_of_restrictions_updates = 0;
    elapsed_time_consulting_restrictions = 0;
    elapsed_time_updating_restrictions = 0;
    elapsed_time_reducing_restrictions = 0;
    max_restriction_size = 0;

    gettimeofday (& end_program, NULL);
    elapsed_time_of_the_algorithm = diff_us (end_program, begin_program);
}


void PUCSR1::random_walk (PartitionNode * P, list<PartitionNode *> * TQ)
{
    // cout << "\n-------\nEntrou em random walk com P = " << 
        // P->get_selected_elements ()->print_subset () << endl;
    unsigned int i = 0;
    unsigned int n = P->get_number_of_fixed_elms ();
    TQ->push_back (new PartitionNode (P));
    PUCSR1ToolBox::restrict_part (P, cand_part);
    PartitionNode * Q;
    while (i < n)
    {
        Q = PUCSR1ToolBox::adjacent_part (P, i++);
        // cout << "- Q = " << Q->get_selected_elements ()->print_subset () << endl;
        if (PUCSR1ToolBox::is_restricted (Q, cand_part))
        {   
            // cout << "- Q é restrito já" << endl;
            delete Q;
            continue;
        }
        PartitionNode * next;
        next = PUCSR1ToolBox::prune_and_walk (P, Q,
            cost_function, cand_part);
        // if (next != NULL)
        //     cout << "- next = " << next->get_selected_elements ()->print_subset () << endl;
        // else
        //     cout << "- next = NULL" << endl;
        if (next == P)
            delete Q;
        else if (next == Q)
        {
            i = 0;
            delete P;
            P = Q;
            TQ->push_back (new PartitionNode (P));
            PUCSR1ToolBox::restrict_part (P, cand_part);
        }
        else
        {
            delete P;
            delete Q;
            return;
        }
    }
    delete P;
    // cout << "Saindo de random walk\n-";
}

void PUCSR1::solve_parts (list<PartitionNode *> * parts, 
    list<ElementSubset *> * min_list, 
    unsigned int max_size_of_minima_list)
{
    PartitionNode * P = NULL;
    Collection * L = NULL;
    while (parts->size () > 0) 
    {
        #pragma omp critical
        {
            P = parts->back ();
            parts->pop_back ();
        }
        #pragma omp task 
        {
            L = PUCSR1ToolBox::part_minimum (P, cost_function,
                max_size_of_minima_list);
            #pragma omp taskwait
            while (L->size () > 0) 
            {
                ElementSubset * X = L->remove_last_subset ();
                #pragma omp critical
                {
                    min_list->push_back (X);
                    if (store_visited_subsets)
                        list_of_visited_subsets->add_subset (X);
                }
            }
            #pragma omp critical
            clean_list_of_minima (max_size_of_minima_list);
            delete L;
            delete P;
        }
    }
}