//
// Solver.h -- definition of the class "Solver".
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

//
// This is an abstract class; solver implementations should inherit this class.
//

#ifndef SOLVER_H_
#define SOLVER_H_

#include "global.h"
#include "ElementSet.h"
#include "ElementSubset.h"
#include "Collection.h"
#include "CostFunction.h"


class Solver
{

protected:

	// Name of the used cost function.
	//
	CostFunction * cost_function;

    // Returns the difference between times in microseconds
    //
    int diff_us (timeval, timeval);

	// Stores the time (in microseconds) spent by all
	// calls of the minimum exhausting (for the solvers that use it)
	//
    int elapsed_time_of_all_calls_of_the_minima_exhausting;

	// Stores the time (in microseconds) spent by the
	// execution of the solver
	//
    int elapsed_time_of_the_algorithm;

	
	// Stores the time (in microseconds) spent by the
	// updates of restrictions
	//
    int elapsed_time_updating_restrictions;


    // Stores the time (in microseconds) spent by the
	// reduction of the restriction
	//
    int elapsed_time_reducing_restrictions;


    // Stores the time (in microseconds) spent by the
	// consults of restrictions
	//
    int elapsed_time_consulting_restrictions;

	
	// Stores the time (in microseconds) spent by the
	// reordering of restrictions
	//
    int elapsed_time_reordering_restrictions;


    // Stores the maximum size of the restrictions
    //
    int max_restriction_size;
	
	// Stores the maximum size that a forest A achieves during all
	// iterations of the PFS algorithm and similar ones.
	//
    unsigned int max_size_of_the_forest_A;

	// Stores the maximum size that a forest B achieves during all
	// iterations of the PFS algorithm and similar ones.
	//
    unsigned int max_size_of_the_forest_B;

	// Stores the maximum size that a graph achieves during all
	// calls of the minimum exhausting (for the solvers that use it)
	//
    unsigned int max_size_of_the_graph;

	// Stores the the number of calls of the minimum
	// exhausting subroutine (for the solvers that use it)
	//
    unsigned int number_of_calls_of_minimum_exhausting;

	// Stores the the number of calls of the minimal_element and
	// the maximal_element subroutines (for the solvers that use it)
	//
    unsigned int number_of_calls_of_minimal_and_maximal_element;

	// Stores the the number of iterations of a given solver
	//
    unsigned int number_of_iterations;

    // Stores the number of consults to the restrictions
    //
    unsigned int number_of_restrictions_consults;

    // Stores the number of updates to the restrictions
    //
    unsigned int number_of_restrictions_updates;

	// Stores the number of reorders applied to the restrictions
    //
    unsigned int number_of_restrictions_reorderings;


	// Functor with operator () as a comparison function.
	//
	struct Functor
	{
		CostFunction * cf; // it is not computed if the cost is stored in the ElementSubset X and Y
		                   //
		bool operator () (ElementSubset * first, ElementSubset * second)
		{
			if (first->cost < second->cost)
				return true;
			else
				return false;
		}
	};

	// cleans the minima list up to 'max_number_of_minima'
	//
	void clean_list_of_minima (unsigned int);

	// Collection of the minima subsets found by the solver.
	//
	list<ElementSubset *> list_of_minima;

	// Collection of the subsets visited by the search.
	//
	Collection * list_of_visited_subsets;

	// Number of visited subsets of the search.
	//
	unsigned int number_of_visited_subsets;

	// The set used in the search of the minima subsets.
	//
	ElementSet * set;

	// True if the search must keep the visited subsets, false otherwise.
	//
	bool store_visited_subsets;

public:

	// Default constructor.
	//
	Solver ();


	// Default destructor.
	//
	virtual ~Solver ();


	// Generates a list of minima with up to n subsets (abstract method).
	//
	virtual void get_minima_list (unsigned int) = 0;


	// Returns the size of the obtained list of minima.
	//
	unsigned int number_of_minima ();


	// Returns the elapsed time of the all calls of the minima exhausting.
	//
	int get_elapsed_time_of_all_calls_of_the_minima_exhausting ();


	// Returns the elapsed time of the solver execution.
	//
	int get_elapsed_time_of_the_algorithm ();


	// Returns the elapsed time updating restrictions
	//
	int get_elapsed_time_updating_restrictions ();


	// Returns the elapsed time consulting restrictions
	//
	int get_elapsed_time_consulting_restrictions ();


	// Returns the elapsed time reducing restrictions
	//
	int get_elapsed_time_reducing_restrictions ();


	// Returns the elapsed time reordering restrictions
	//
	int get_elapsed_time_reordering_restrictions ();


	// Returns the number of calls of the minimal and maximal element subroutines.
	//
	unsigned int get_number_of_calls_of_minimal_and_maximal_element ();


	// Returns the number of calls of the minimum exhausting subroutine.
	//
	unsigned int get_number_of_calls_of_minimum_exhausting ();


	// Returns the number of iterations of a given algorithm.
	//
	unsigned int get_number_of_iterations ();


	// Returns the number of consults to the restriction list
	//
	unsigned int get_number_of_restrictions_consults ();


	// Returns the number of updates to the restriction list
	//
	unsigned int get_number_of_restrictions_updates ();


	// Returns the number of reorderings to the restriction list
	//
	unsigned int get_number_of_restrictions_reorderings ();


	// Returns the maximum size of the forest A.
	//
	unsigned int get_max_size_of_the_forest_A ();


	// Returns the maximum size of the forest A.
	//
	unsigned int get_max_size_of_the_forest_B ();


	// Returns the maximum size of the graph data structure.
	//
	unsigned int get_max_size_of_the_graph ();


	// Returns the maximum sizeo of the restriction
	//
	unsigned int get_max_restriction_size ();


	// Returns a string with all the subsets of the list of minima.
	// (e.g. returns " [010] [101] [111] ").
	//
	string print_list_of_minima ();


	// Returns a string with all the subsets visited by the search.
	// (e.g. returns " [000] [001] [011] ... ").
	//
	string print_list_of_visited_subsets ();


	// Returns the number of visited subsets during a search.
	//
	unsigned int print_number_of_visited_subsets ();

	// Returns a string with all the subsets of the list of minima with their
	// respective cost (one subset-cost per line).
	// (e.g. returns " [010] : 1.12
	//                 [101] : 0.73
	//                 [111] : 0.12 ").
	//
	string print_search_report ();


	// Sets the used set, the cost function, and 'true' if it should store the
	// visited subsets, 'false' otherwise.
	//
	void set_parameters(CostFunction *, ElementSet *, bool);


	// Given the subset X, returns the calculated subset cost.
	//
	float subset_cost (ElementSubset *);


	// If "store_visited_subsets" is true, then this method stores a copy of X
	// into list_of_visited_subsets.
	//
	void store_visited_subset (ElementSubset * X);


	// This method stores a copy of X
	// into list_of_minima.
	//
	void store_minimum_subset (ElementSubset * X);

};

#endif /* SOLVER_H_ */
