//
// Solver.cpp -- implementation of the class "Solver".
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

#include "Solver.h"


Solver::Solver ()
{
	cost_function = NULL;
	list_of_visited_subsets = NULL;
	set = NULL;
	store_visited_subsets = false;
	number_of_visited_subsets = 0;
	elapsed_time_of_the_algorithm = 0;
	elapsed_time_of_all_calls_of_the_minima_exhausting = 0;

	// Used by UCS and similar ones
	number_of_calls_of_minimum_exhausting = 0;
	number_of_calls_of_minimal_and_maximal_element = 0;
	max_size_of_the_graph = 0;
	number_of_restrictions_consults = 0;
	number_of_restrictions_updates = 0;

	// Used by UCS7
	elapsed_time_reordering_restrictions = 0;
	number_of_restrictions_reorderings = 0;

	// Used by PFS and similar ones
	number_of_iterations = 0;
	max_size_of_the_forest_A = 0;
	max_size_of_the_forest_B = 0;
}


Solver::~Solver ()
{
	ElementSubset * X;

	while (list_of_minima.size () > 0)
	{
		X = list_of_minima.back ();
		list_of_minima.pop_back ();
		delete X;
	}
}


void Solver::set_parameters (CostFunction * a_cost_function, ElementSet * a_set, bool keep_subsets)
{
	set = a_set;
	cost_function = a_cost_function;
	store_visited_subsets = keep_subsets;
}


float Solver::subset_cost (ElementSubset * X)
{
	return cost_function->cost (X);
}


string Solver::print_list_of_minima ()
{
	list<ElementSubset *>::iterator it;
	string list_string ("");
	for (it = list_of_minima.begin (); it != list_of_minima.end (); it++)
		list_string.append ((*it)->print_subset ());
	return list_string;
}


string Solver::print_list_of_visited_subsets ()
{
	return list_of_visited_subsets->print_collection ();
}


string Solver::print_search_report ()
{
	list<ElementSubset *>::iterator it;
	string report_string ("");
	std::ostringstream value;
	for (it = list_of_minima.begin (); it != list_of_minima.end (); it++)
	{
		report_string.append ((*it)->print_subset ());
		report_string.append (": ");
		value <<  (*it)->cost;
		report_string.append (value.str ());
		report_string.append ("\n");
		value.str ("");
	}
	return report_string;
}


unsigned int Solver::print_number_of_visited_subsets ()
{
	return number_of_visited_subsets;
}


// cleans the minima list up to 'max_number_of_minima'
//
void Solver::clean_list_of_minima (unsigned int max_size_of_minima_list)
{
	ElementSubset * X;
	Functor f;              // struct of class Solver that stores the comparison function

	int number_of_elements_to_remove = list_of_minima.size () - (int) max_size_of_minima_list;
	f.cf = cost_function;

	list_of_minima.sort (f);

	while (number_of_elements_to_remove > 0)
	{
		X = list_of_minima.back ();
		list_of_minima.pop_back ();
		delete X;
		number_of_elements_to_remove--;
	}
}


unsigned int Solver::number_of_minima ()
{
	return list_of_minima.size ();
}


int Solver::get_elapsed_time_of_the_algorithm ()
{
	return elapsed_time_of_the_algorithm;
}


int Solver::get_elapsed_time_updating_restrictions ()
{
	return elapsed_time_updating_restrictions;
}


int Solver::get_elapsed_time_consulting_restrictions ()
{
	return elapsed_time_consulting_restrictions;
}


int Solver::get_elapsed_time_reducing_restrictions ()
{
	return elapsed_time_reducing_restrictions;
}


int Solver::get_elapsed_time_reordering_restrictions ()
{
	return elapsed_time_reordering_restrictions;
}


int Solver::get_elapsed_time_of_all_calls_of_the_minima_exhausting()
{
	return elapsed_time_of_all_calls_of_the_minima_exhausting;
}


unsigned int Solver::get_number_of_calls_of_minimum_exhausting ()
{
	return number_of_calls_of_minimum_exhausting;
}


unsigned int Solver::get_max_size_of_the_graph ()
{
	return max_size_of_the_graph;
}


unsigned int Solver::get_number_of_restrictions_consults ()
{
	return number_of_restrictions_consults;
}


unsigned int Solver::get_number_of_restrictions_updates ()
{
	return number_of_restrictions_updates;
}


unsigned int Solver::get_number_of_restrictions_reorderings ()
{
	return number_of_restrictions_reorderings;
}


unsigned int Solver::get_number_of_calls_of_minimal_and_maximal_element ()
{
	return number_of_calls_of_minimal_and_maximal_element;
}


unsigned int Solver::get_number_of_iterations ()
{
	return number_of_iterations;
}


unsigned int Solver::get_max_size_of_the_forest_A ()
{
	return max_size_of_the_forest_A;
}


unsigned int Solver::get_max_size_of_the_forest_B ()
{
	return max_size_of_the_forest_B;
}


unsigned int Solver::get_max_restriction_size ()
{
	return max_restriction_size;
}


// "diff" in microseconds
//
int Solver::diff_us (timeval t1, timeval t2)
{
    return (((t1.tv_sec - t2.tv_sec) * 1000000) + (t1.tv_usec - t2.tv_usec));
}


void Solver::store_visited_subset (ElementSubset * X)
{
	if (store_visited_subsets)
		list_of_visited_subsets->add_subset (X);
}


void Solver::store_minimum_subset (ElementSubset * X)
{
	ElementSubset * Y;
	Y = new ElementSubset ("", set);
	Y->copy (X);
	list_of_minima.push_back (Y);
}
