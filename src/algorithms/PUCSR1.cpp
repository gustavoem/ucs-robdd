#include "UCSROBDD6.h"

UCSROBDD6::UCSROBDD6 ()
{
    list_of_visited_subsets = new Collection ();
    cost_function = NULL;
}


UCSROBDD6::~UCSROBDD6 ()
{
    if (restrictions != NULL)
        delete restrictions;
    if (list_of_visited_subsets != NULL)
        delete list_of_visited_subsets;
    if (candidate_partitions != NULL)
        delete candidate_partitions;
}


void UCSROBDD6::set_fixed_elements ()
{
    unsigned int set_size = set->get_set_cardinality ();
    // The number partition_set_size determines the cardinality of each
    // subposet in which we will solve the u-curve
    unsigned int partition_set_size = 2;
    unsigned int fixed_set_size = set_size - partition_set_size;
    unsigned int *fixed = new unsigned int[fixed_set_size];
    unsigned int *unfixed = new unsigned int[partition_set_size];

    // This is a simple way to partitionate the space. We are choosing
    // the last <partition_set_size> variables of the element set to be
    // free in every subproblem and fixing the other variables
    // 
    for (unsigned int i = 0; i < fixed_set_size; i++)
        fixed[i] = i;
    for (unsigned int i = 0; i < partition_set_size; i++)
        unfixed[i] = fixed_set_size + i;

    fixed_elements = new ElementSet (set, fixed, );
}


void UCSROBDD6::get_minima_list (unsigned int max_size_of_minima_list)
{
    restrictions = new ROBDD (set);
    set_fixed_elements ();

    // candidate_partitions = new ROBDD ();
    // timeval begin_exhausting, end_exhausting, begin_program, end_program;
    // gettimeofday (& begin_program, NULL);

    // Collection * L = new Collection ();
    // bool search_space_is_empty = false;
    // ElementSubset * X, Y ("", set);
    // UCSROBDDToolBox6::Node * M;

    // srand ( (unsigned) time (NULL) );

    // do
    // {
    //     X = restrictions->get_random_zero_evaluated_element ();
    //     if (X != NULL)
    //     {
    //         gettimeofday (& begin_exhausting, NULL);
    //         M = UCSROBDDToolBox6::create_node (X);
    //         M->vertex->cost = cost_function->cost (M->vertex);
            
    //         UCSROBDDToolBox6::DFS
    //             (M, L, restrictions, cost_function);
    //         number_of_calls_of_minimum_exhausting++;
            
    //         gettimeofday (& end_exhausting, NULL);
    //         elapsed_time_of_all_calls_of_the_minima_exhausting +=
    //         diff_us (end_exhausting, begin_exhausting);     
    //         delete X;
    //     }
    //     else
    //         search_space_is_empty = true;

    //     while (L->size() > 0)
    //     {
    //         X = L->remove_last_subset ();
    //         list_of_minima.push_back (X);
    //         if (store_visited_subsets)
    //             list_of_visited_subsets->add_subset (X);
    //     }

    //     // Reminder: this function DOES NOT compute again the
    //     // cost function, instead it uses the cost value stored
    //     // into the ElementSubsets.
    //     //
    //     clean_list_of_minima (max_size_of_minima_list);

    // } while ( (! search_space_is_empty) && (! cost_function->has_reached_threshold () ) );

    // delete L;

    // number_of_visited_subsets =  cost_function->get_number_of_calls_of_cost_function ();
    // number_of_restrictions_consults = restrictions->get_nof_consults ();
    // number_of_restrictions_updates = restrictions->get_nof_updates ();
    // elapsed_time_consulting_restrictions = restrictions->get_time_consulting ();
    // elapsed_time_updating_restrictions = restrictions->get_time_updating ();
    // elapsed_time_reducing_restrictions = restrictions->get_time_reducing ();

    // gettimeofday (& end_program, NULL);
    // elapsed_time_of_the_algorithm = diff_us (end_program, begin_program);
}
