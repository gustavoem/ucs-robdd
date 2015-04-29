#include "UCSRT.h"

UCSRT::UCSRT ()
{
	list_of_visited_subsets = new Collection ();
	lower_restriction = new Collection ();
	upper_restriction = new Collection ();
	cost_function = NULL;
}


UCSRT::~UCSRT ()
{
	if (restrictions != NULL)
		delete restrictions;
	if (lower_restriction != NULL)
		delete lower_restriction;
	if (upper_restriction != NULL)
		delete upper_restriction;
	if (list_of_visited_subsets != NULL)
		delete list_of_visited_subsets;
}


void UCSRT::get_minima_list (unsigned int max_size_of_minima_list)
{
	timeval begin_exhausting, end_exhausting, begin_program, end_program;
	gettimeofday (& begin_program, NULL);

	restrictions = new ROBDD (set);
	unsigned int max_graph_of_this_iteration;
	Collection * L = new Collection ();
	bool search_space_is_empty = false;
	ElementSubset * X, Y ("", set);
	UCSRTToolBox::Node * M;

	srand ( (unsigned) time (NULL) );

	do
	{
		max_graph_of_this_iteration = 0;
		X = restrictions->get_random_zero_evaluated_element ();
		//X = UCSRTToolBox::get_minimal_subset (restrictions, set);

		if (X != NULL)
		{
			gettimeofday (& begin_exhausting, NULL);

			M = UCSRTToolBox::create_node (X);
			M->vertex->cost = cost_function->cost (M->vertex);

			// X is minimal, thus there is no lower adjacent
			//UCSRTToolBox::update_lower_restriction (restrictions, lower_restriction, X);
			//M->lower_flag->set_empty_subset ();

			max_graph_of_this_iteration = 1;
			UCSRTToolBox::DFS
				(M, L, restrictions, upper_restriction, lower_restriction,
				 cost_function, & max_graph_of_this_iteration);

			gettimeofday (& end_exhausting, NULL);
			elapsed_time_of_all_calls_of_the_minima_exhausting +=
			diff_us (end_exhausting, begin_exhausting);		
			delete X;
		}
		else
			search_space_is_empty = true;

		if (max_graph_of_this_iteration >= 1) // this operation just counts the calls of DFS that explores
		{                                    // more than one node
			if (max_size_of_the_graph < max_graph_of_this_iteration)
				max_size_of_the_graph = max_graph_of_this_iteration;
			number_of_calls_of_minimum_exhausting++;
		}

		while (L->size() > 0)
		{
			X = L->remove_last_subset ();
			list_of_minima.push_back (X);
			if (store_visited_subsets)
				list_of_visited_subsets->add_subset (X);
		}

		// Reminder: this function DOES NOT compute again the
		// cost function, instead it uses the cost value stored
		// into the ElementSubsets.
		//
		clean_list_of_minima (max_size_of_minima_list);

	} while ( (! search_space_is_empty) && (! cost_function->has_reached_threshold () ) );

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