#include "PUCSR1.h"

PUCSR1::PUCSR1 ()
{
    list_of_visited_subsets = new Collection ();
    cost_function = NULL;
    cand_part = NULL;
    part_model = NULL;
}


PUCSR1::~PUCSR1 ()
{
    if (list_of_visited_subsets != NULL)
        delete list_of_visited_subsets;
    if (cand_part != NULL)
        delete cand_part;
    if (part_model != NULL)
        delete part_model;
}


void PUCSR1::set_partition_model ()
{
    unsigned int set_size = set->get_set_cardinality ();
    unsigned int partition_set_size = set_size / 2 + 1;
    bool * fixed = new bool[set_size];
    // This is a simple way to partitionate the space. We are choosing
    // the last <partition_set_size> variables of the element set to be
    // free in every subproblem and fixing the other variables
    for (unsigned int i = 0; i < set_size; i++)
        if (i < partition_set_size)
            fixed[i] = true;
        else
            fixed[i] = false;
    this->part_model = new PartitionModel (set, fixed);
    delete[] fixed;
}


void PUCSR1::find_minima_list (unsigned int max_size_of_minima_list)
{
    set_partition_model ();
    cand_part = new ROBDD (part_model->get_fixed_elm_set ());

    timeval begin_exhausting, end_exhausting, begin_program, end_program;
    gettimeofday (& begin_program, NULL);

    // while there are still partitions to be visited
        // choose a partition
        // finds the minimum of this partition
        // look at partition neighbours and perform a walk between 
        // partitions while prunning partitions.

    Collection * L = new Collection ();
    ElementSubset * part_subset;
    part_subset = cand_part->get_random_zero_evaluated_element ();
    while (part_subset != NULL)
    {
        Partition * part = new Partition (part_model, part_subset);
        PUCSR1ToolBox::random_walk (part, cand_part, cost_function, 
            L, max_size_of_minima_list);
        // cout << "size of minima: " << max_size_of_minima_list << endl;
        clean_list_of_minima (max_size_of_minima_list);
        // cout << "Collection after finding minimum: " << L->print_collection (cost_function) << endl;
        
        delete part_subset;
        part_subset = cand_part->get_random_zero_evaluated_element ();
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
