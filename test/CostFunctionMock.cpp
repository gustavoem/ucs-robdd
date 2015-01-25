//
// CostFunctionMock.cpp -- implementation of the mock class "CostFunctionMock".
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

#include "CostFunctionMock.h"


CostFunctionMock::CostFunctionMock (ElementSet * set) :
                                                        MeanConditionalEntropy (set)
{
	// TODO Auto-generated constructor stub
}


CostFunctionMock::~CostFunctionMock ()
{
	// TODO
}


string CostFunctionMock::print_label_frequencies (ElementSubset * X)
{
	map<string, ElementSubset *>::iterator it;
	string printed_samples ("");
	std::ostringstream value;
	ElementSet S ("", X->get_subset_cardinality (), 1);

	calculate_distributions_from_the_samples (& S, X);

	for (it = samples.begin (); it != samples.end (); it++)
	{
		printed_samples.append (it->second->print_subset ());
		printed_samples.append (": ");
		value <<  (int) it->second->Y [0];
		printed_samples.append (value.str ());
		value.str ("");
		printed_samples.append (" ");
		value <<  (int) it->second->Y [1];
		printed_samples.append (value.str ());
		value.str ("");
		printed_samples.append ("\n");
		delete it->second;
	}
	samples.clear ();

	return printed_samples;

}

string CostFunctionMock::print_W_operator_samples_frequencies (ElementSubset * X)
{
	map<string, ElementSubset *>::iterator it;
	string printed_samples ("");
	std::ostringstream value;
	ElementSet S ("", X->get_subset_cardinality (), 1);

	calculate_distributions_from_the_samples (& S, X);

	for (it = samples.begin (); it != samples.end (); it++)
	{
		printed_samples.append (it->second->print_subset ());
		printed_samples.append (": ");
		value <<  (int) it->second->Y[0] + it->second->Y[1];
		delete it->second;
		printed_samples.append (value.str ());
		value.str ("");
		printed_samples.append ("\n");
	}

	samples.clear ();

	return printed_samples;
}


string CostFunctionMock::print_conditional_entropy (ElementSubset * X)
{
	map<string, ElementSubset *>::iterator it;
	string printed_samples ("");
	std::ostringstream value;
	ElementSet S ("", X->get_subset_cardinality (), 1);

	calculate_distributions_from_the_samples (& S, X);

	for (it = samples.begin (); it != samples.end (); it++)
	{
		printed_samples.append (it->second->print_subset ());
		printed_samples.append (": ");
		value <<  calculate_conditional_entropy (it->second);
		delete it->second;
		printed_samples.append (value.str ());
		value.str ("");
		printed_samples.append ("\n");
	}

	samples.clear ();

	return printed_samples;
}


void CostFunctionMock::add_elapsed_time (int microseconds)
{
	timeval begin, end;
	useconds_t micro_seconds = microseconds;

	gettimeofday (& begin, NULL);

	// pause
	usleep (micro_seconds);

	gettimeofday (& end, NULL);

	MeanConditionalEntropy::elapsed_time_of_all_calls_of_the_cost_function +=
			MeanConditionalEntropy::diff_us (end, begin);
}


int CostFunctionMock::override_get_the_elapsed_time_of_the_calls_of_this_cost_function ()
{
	return MeanConditionalEntropy::get_the_elapsed_time_of_the_calls_of_this_cost_function ();
}
