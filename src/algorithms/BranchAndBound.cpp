/*
 * BranchAndBound.cpp
 *
 *  Created on: Apr 6, 2011
 *      Author: marceloreis
 */

#include "BranchAndBound.h"

BranchAndBound::BranchAndBound ()
{
	list_of_visited_subsets = new Collection ();
	cost_function = NULL;
}


BranchAndBound::~BranchAndBound ()
{
	if (list_of_visited_subsets != NULL)
		delete list_of_visited_subsets;
}


void BranchAndBound::get_minima_list (unsigned int max_size_of_minima_list)
{
	timeval begin_program, end_program;
	gettimeofday (& begin_program, NULL);

	ElementSubset * A, * B;
	unsigned int i, n;
	float bound, current_cost, last_cost;
	list<ElementSubset *> Stack;
	list<unsigned int> Leftmost_free_elem;
	list<float> Last_cost_stack;

	A = new ElementSubset ("A", set);
	bound = INFINITY_COST;
	Stack.push_back (A);
	Leftmost_free_elem.push_back (0);
	Last_cost_stack.push_back (bound);

	while ((! Stack.empty ()) && (! cost_function->has_reached_threshold ()) )
	{
		A = Stack.back ();
		Stack.pop_back ();
		n = Leftmost_free_elem.back ();
		Leftmost_free_elem.pop_back ();
		last_cost = Last_cost_stack.back ();
		Last_cost_stack.pop_back ();

		current_cost = A->cost = cost_function->cost(A);

		if ((current_cost <= last_cost) && (A->get_subset_cardinality() <= MAX_SUBSET_SIZE) )
		{
			// the bound helps to keep the list of minimum small
			//
			if (current_cost <= bound)
			{
				bound = current_cost;
				B = new ElementSubset ("", set);
				B->copy (A);
				list_of_minima.push_back (B);
			}
			if (store_visited_subsets)
				list_of_visited_subsets->add_subset (A);

			for (i = n; i < set->get_set_cardinality (); i++)
			{
				A->add_element (i);
				B = new ElementSubset ("", set);
				B->copy (A);
				Stack.push_back (B);
				Leftmost_free_elem.push_back (i+1);
				Last_cost_stack.push_back (current_cost);
				A->remove_element (i);
			}
		} // if

		delete A;

	} // while

	number_of_visited_subsets =  cost_function->get_number_of_calls_of_cost_function ();

	clean_list_of_minima (max_size_of_minima_list);

	gettimeofday (& end_program, NULL);
	elapsed_time_of_the_algorithm = diff_us (end_program, begin_program);


}
