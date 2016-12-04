#include "PUCSR1.h"

PUCSR1::PUCSR1 ()
{
    list_of_visited_subsets = new Collection ();
    cost_function = NULL;
    restrictions = NULL;
    cand_part = NULL;
    fixed_elms = NULL;
    unfixed_elms = NULL;
}


PUCSR1::~PUCSR1 ()
{
    // if (restrictions != NULL)
    //     delete restrictions;
    if (list_of_visited_subsets != NULL)
        delete list_of_visited_subsets;
    if (cand_part != NULL)
        delete cand_part;
    if (fixed_elms != NULL)
        delete unfixed_elms;
    if (fixed_elms != NULL)
        delete fixed_elms;
}


void PUCSR1::set_partition_model ()
{
    unsigned int set_size = set->get_set_cardinality ();
    // The number partition_set_size determines the cardinality of each
    // subposet in which we will solve the u-curve
    part_set_size = 2;
    unsigned int fixed_set_size = set_size - part_set_size;
    bool * fixed = new bool[set_size];
    // This is a simple way to partitionate the space. We are choosing
    // the last <partition_set_size> variables of the element set to be
    // free in every subproblem and fixing the other variables
    for (unsigned int i = 0; i < set_size; i++)
        if (i < fixed_set_size)
            fixed[i] = true;
        else
            fixed[i] = false;
    this->part_model = new PartitionModel (set, fixed);
}


void PUCSR1::find_minima_list (unsigned int max_size_of_minima_list)
{
    set_partition_model ();
    cand_part = new ROBDD (part_model->get_fixed_elm_set ());

    // timeval begin_exhausting, end_exhausting, begin_program, end_program;
    // gettimeofday (& begin_program, NULL);

    // enquanto tiver partições para serem visitadas
        // escolhe uma partição
            // enquanto a partição não for minima localmente***
            // acha o mínimo da partição
            // olha para os vizinhos e caminha nas partições

    Collection * L = new Collection ();
    ElementSubset * part_subset;
    part_subset = cand_part->get_random_zero_evaluated_element ();
    while (part_subset != NULL)
    {
        part = new Partition (part_model, part_subset);
        PUCSR1ToolBox::random_walk (part, cand_part, L);
        // clean minima list
        delete part;
        delete part_subset;
        part_subset = cand_part->get_random_zero_evaluated_element ();
    }

    delete L;

    number_of_visited_subsets =  cost_function->get_number_of_calls_of_cost_function ();
    number_of_restrictions_consults = restrictions->get_nof_consults ();
    number_of_restrictions_updates = restrictions->get_nof_updates ();
    elapsed_time_consulting_restrictions = restrictions->get_time_consulting ();
    elapsed_time_updating_restrictions = restrictions->get_time_updating ();
    elapsed_time_reducing_restrictions = restrictions->get_time_reducing ();

    gettimeofday (& end_program, NULL);
    elapsed_time_of_the_algorithm = diff_us (end_program, begin_program);
}
