//
// UCurveSearch.cpp -- implementation of the class "UCurveSearch" (UCS).
//
//    This file is part of the featsel program
//    Copyright (C) 2010  Marcelo S. Reis
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "UCurveSearch.h"


UCurveSearch::UCurveSearch ()
{
	lower_restriction = new Collection ();
	upper_restriction = new Collection ();
	list_of_visited_subsets = new Collection ();
	cost_function = NULL;
}


UCurveSearch::~UCurveSearch ()
{
	if (lower_restriction != NULL)
		delete lower_restriction;
	if (upper_restriction != NULL)
		delete upper_restriction;
	if (list_of_visited_subsets != NULL)
		delete list_of_visited_subsets;
}


void UCurveSearch::find_minima_list (unsigned int max_size_of_minima_list)
{
	timeval begin_exhausting, end_exhausting, begin_program, end_program;
	gettimeofday (& begin_program, NULL);

	unsigned int direction, max_graph_of_this_iteration;
	Collection * L = new Collection ();
	bool search_space_is_empty = false;
	ElementSubset * X, Y ("", set);
	UCurveToolBox::Node * M;

	srand ( (unsigned) time (NULL) );

	do
	{
		// at each iteration it is called either minimal_element or maximal_element
		//
		number_of_calls_of_minimal_and_maximal_element++;
		max_graph_of_this_iteration = 0;

		direction = rand () % 2;
		if (direction == 0)
		{
			X = UCurveToolBox::get_minimal_subset (lower_restriction, upper_restriction, set);
			if (X != NULL)
			{
				// if X is upper covered by the upper restrictions then
				// we may add X into the collection of lower restrictions; once X
				// is minimal, there is no risk of losing an element from the search space!
				//
				if (upper_restriction->upper_covers (X))
					UCurveToolBox::update_lower_restriction (lower_restriction, X);
				else
				{
					gettimeofday (& begin_exhausting, NULL);

					M = UCurveToolBox::create_node (X);
					M->vertex->cost = cost_function->cost (M->vertex);

					// X is minimal, thus there is no lower adjacent
					UCurveToolBox::update_lower_restriction (lower_restriction, X);
					M->lower_flag->set_empty_subset ();

					max_graph_of_this_iteration = 1;
					UCurveToolBox::DFS
						(M, L, lower_restriction, upper_restriction, cost_function,
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
		}
		else
		{
			X = UCurveToolBox::get_maximal_subset (lower_restriction, upper_restriction, set);
			if (X != NULL)
			{
				if (lower_restriction->lower_covers (X))
					UCurveToolBox::update_upper_restriction (upper_restriction, X);
				else
				{
					gettimeofday (& begin_exhausting, NULL);

					M = UCurveToolBox::create_node (X);
					M->vertex->cost = cost_function->cost (M->vertex);

					// X is maximal, thus there is no upper adjacent
					UCurveToolBox::update_upper_restriction (upper_restriction, X);
					M->upper_flag->set_empty_subset ();

					max_graph_of_this_iteration = 1;
					UCurveToolBox::DFS
						(M, L, lower_restriction, upper_restriction, cost_function,
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
	number_of_restrictions_consults = lower_restriction->get_nof_consults () \
									+ upper_restriction->get_nof_consults ();
	number_of_restrictions_updates = lower_restriction->get_nof_updates () \
									+ upper_restriction->get_nof_updates ();

	elapsed_time_consulting_restrictions = lower_restriction->get_time_consulting () \
										 + upper_restriction->get_time_consulting ();
	elapsed_time_updating_restrictions = lower_restriction->get_time_updating () \
									   + upper_restriction->get_time_consulting ();							

	gettimeofday (& end_program, NULL);
	elapsed_time_of_the_algorithm = diff_us (end_program, begin_program);

}



