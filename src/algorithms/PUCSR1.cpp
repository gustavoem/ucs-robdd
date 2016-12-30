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
    unsigned int partition_set_size = set_size - 8;
    bool * fixed = new bool[set_size];
    // This is a simple way to partitionate the space. We are choosing
    // the last <partition_set_size> variables of the element set to be
    // free in every subproblem and fixing the other variables
    for (unsigned int i = 0; i < set_size; i++)
        if (i < partition_set_size)
            fixed[i] = true;
        else
            fixed[i] = false;
    this->partition = new Partition (set, fixed);
    delete[] fixed;
}


void PUCSR1::find_minima_list (unsigned int max_size_of_minima_list)
{
    set_partition_model ();
    cand_part = new ROBDD (partition->get_fixed_elm_set ());

    timeval begin_exhausting, end_exhausting, begin_program, end_program;
    gettimeofday (& begin_program, NULL);

    Collection * L = new Collection ();
    ElementSubset * p_subset;
    p_subset = cand_part->get_random_zero_evaluated_element ();
    while (p_subset != NULL)
    {
        PartitionNode * P = new PartitionNode (partition, p_subset);
        random_walk (P, L);
        clean_list_of_minima (max_size_of_minima_list);
        delete p_subset;
        p_subset = cand_part->get_random_zero_evaluated_element ();
        while (L->size() > 0)
        {
            ElementSubset * X = L->remove_last_subset ();
            list_of_minima.push_back (X);
        }
        clean_list_of_minima (max_size_of_minima_list);
    }
    delete L;

    number_of_visited_subsets =  cost_function->get_number_of_calls_of_cost_function ();
    number_of_restrictions_consults = 0;
    number_of_restrictions_updates = 0;
    elapsed_time_consulting_restrictions = 0;
    elapsed_time_updating_restrictions = 0;
    elapsed_time_reducing_restrictions = 0;

    gettimeofday (& end_program, NULL);
    elapsed_time_of_the_algorithm = diff_us (end_program, begin_program);
}


void PUCSR1::random_walk (PartitionNode * P, Collection * L)
{
    unsigned int i = 0;
    /*temp*/ unsigned int max_size_of_minima_list = 10;
    unsigned int n = P->get_number_of_fixed_elms ();
    PUCSR1ToolBox::part_minimum (P, L, cost_function,
        max_size_of_minima_list);
    PUCSR1ToolBox::restrict_part (P, cand_part);
    PartitionNode * Q;
    while (i < n)
    {
        Q = PUCSR1ToolBox::adjacent_part (P, i++);
        if (PUCSR1ToolBox::is_restricted (Q, cand_part))
        {
            delete Q;
            continue;
        }
        PartitionNode * next;
        next = PUCSR1ToolBox::prune_and_walk (P, Q,
            cost_function, cand_part);
        if (next == P)
            delete Q;
        else if (next == Q)
        {
            i = 0;
            delete P;
            P = Q;
            PUCSR1ToolBox::part_minimum (P, L, cost_function,
                max_size_of_minima_list);
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
}