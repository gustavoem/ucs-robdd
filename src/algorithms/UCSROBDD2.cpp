#include "UCSROBDD2.h"

UCSROBDD2::UCSROBDD2 ()
{
	list_of_visited_subsets = new Collection ();
	cost_function = NULL;
}


UCSROBDD2::~UCSROBDD2 ()
{
	if (restrictions != NULL)
		delete restrictions;
	if (list_of_visited_subsets != NULL)
		delete list_of_visited_subsets;
}


void UCSROBDD2::get_minima_list (unsigned int max_size_of_minima_list)
{
	restrictions = new ROBDD (set);
	timeval begin_exhausting, end_exhausting, begin_program, end_program;
	gettimeofday (& begin_program, NULL);

	unsigned int max_graph_of_this_iteration;
	Collection * L = new Collection ();
	bool search_space_is_empty = false;
	ElementSubset * X, Y ("", set);
	UCSROBDDToolBox2::Node * M;

	srand ( (unsigned) time (NULL) );

	do
	{
		// at each iteration it is called either minimal_element or maximal_element
		//
		number_of_calls_of_minimal_and_maximal_element++;
		max_graph_of_this_iteration = 0;
		cout << "restricoes: " << endl;
		restrictions->print ();
		//restrictions->reduce ();
		cout << "reduced: " << endl;
		restrictions->print ();
		X = restrictions->get_random_zero_evaluated_element ();
		if (X != NULL)
			cout << X->print_subset ();
		if (X != NULL)
		{
			if (restrictions->contains (X))
			{
				cout << "smth went wrong, x cant be covered!" << endl;
				UCSROBDDToolBox2::update_lower_restriction (restrictions, X);
			}
			else
			{
				gettimeofday (& begin_exhausting, NULL);
				M = UCSROBDDToolBox2::create_node (X);
				M->vertex->cost = cost_function->cost (M->vertex);
	
				// X is minimal, thus there is no lower adjacent
				//UCSROBDDToolBox2::update_lower_restriction (restrictions, X);
				//M->lower_flag->set_empty_subset ();

				max_graph_of_this_iteration = 1;
				UCSROBDDToolBox2::DFS
					(M, L, restrictions, cost_function,
					 & max_graph_of_this_iteration);
					gettimeofday (& end_exhausting, NULL);
				elapsed_time_of_all_calls_of_the_minima_exhausting +=
						diff_us (end_exhausting, begin_exhausting);
			}
				delete X;
		}
		else
		{
			search_space_is_empty = true;
		}

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

	gettimeofday (& end_program, NULL);
	elapsed_time_of_the_algorithm = diff_us (end_program, begin_program);

}