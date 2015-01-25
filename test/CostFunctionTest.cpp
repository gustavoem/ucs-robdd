//
// CostFunctionTest.cpp -- implementation of the namespace "CostFunctionTest".
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

// IMPORTANT: all the tests require the following values for the definitions in "CostFunction.h":
//
// # define PARAMETER_N 1
// # define NUMBER_OF_STATES 3

#include "CostFunctionTest.h"

namespace CostFunctionTest
{
	bool it_should_works_with_an_explicitly_declared_cost_function ()
	{
		ElementSet set_1 ("S", "input/CostFunctionTestExplicitFuncA.xml");
		ElementSet set_2 ("S", "input/CostFunctionTestExplicitFuncB.xml");
		Explicit c1 (& set_1);
		Explicit c2 (& set_2);
		ElementSubset X ("X", & set_1);
		ElementSubset Y ("Y", & set_2);

		if (c1.cost (&X) != 5)
			return false;
		X.add_element (0);
		if (c1.cost (&X) != 4)
			return false;
		X.add_element (2);
		if (c1.cost (&X) != 1)
			return false;
		X.add_element (1);
		if (c1.cost (&X) != 7)
			return false;

		// testing the storage of floating point values
		if (c2.cost (&Y) != (float) 0.77)
			return false;
		Y.add_element (0);
		if (c2.cost (&Y) != 0)
			return false;
		Y.add_element (1);
		if (c2.cost (&Y) != 3)
			return false;
	    Y.remove_element (0);
		if (c2.cost (&Y) != (float) 1.2)
			return false;

		return true;
	}


	// MCE tests

	bool it_should_store_the_frequencies_of_the_samples ()
	{
		ElementSet set ("input/CostFunctionTestMCE01.dat", 7);
		ElementSubset X ("", & set);
		CostFunctionMock cfm (& set);
		string samples_frequencies;

		X.set_complete_subset ();
		samples_frequencies = cfm.print_W_operator_samples_frequencies (& X);
		if (!( (samples_frequencies.find ("<0001001> : 1") != string::npos) &&
               (samples_frequencies.find ("<0101011> : 2") != string::npos) &&
               (samples_frequencies.find ("<0111110> : 1") != string::npos) &&
               (samples_frequencies.find ("<1111111> : ") == string::npos) &&
               (samples_frequencies.find ("<0000000> : ") == string::npos) )
		   )
			return false;

		// |X| must be greater than 0
		//
		X.set_empty_subset ();
		X.add_element(1);
		X.add_element(2);
		X.add_element(3);
		samples_frequencies = cfm.print_W_operator_samples_frequencies (& X);
		if (!( (samples_frequencies.find ("<101> : 2") != string::npos) &&
               (samples_frequencies.find ("<001> : 1") != string::npos) &&
               (samples_frequencies.find ("<111> : 1") != string::npos) &&
               (samples_frequencies.find ("<000> : ") == string::npos) &&
               (samples_frequencies.find ("<110> : ") == string::npos) )
		   )
			return false;

		X.set_empty_subset ();
		X.add_element(0);
		X.add_element(2);
		X.add_element(4);
		X.add_element(6);
		samples_frequencies = cfm.print_W_operator_samples_frequencies (& X);
		if (!( (samples_frequencies.find ("<0001> : 3") != string::npos) &&
               (samples_frequencies.find ("<0110> : 1") != string::npos) &&
               (samples_frequencies.find ("<1010> : ") == string::npos) &&
               (samples_frequencies.find ("<0000> : ") == string::npos) &&
               (samples_frequencies.find ("<1111> : ") == string::npos) )
		   )
			return false;


		X.set_empty_subset ();
		X.add_element(5);
		samples_frequencies = cfm.print_W_operator_samples_frequencies (& X);
		if (!( (samples_frequencies.find ("<1> : 3") != string::npos) &&
               (samples_frequencies.find ("<0> : 1") != string::npos) )
		   )
			return false;

		return true;
	}


	bool it_should_store_the_label_frequencies_of_the_samples ()
	{
		ElementSet set ("input/CostFunctionTestMCE02.dat", 3);
		ElementSubset X ("", & set);
		CostFunctionMock cfm (& set);
		string samples_frequencies;

		// |X| must be greater than 0
		//
		X.set_complete_subset ();
		samples_frequencies = cfm.print_label_frequencies (& X);
		if (! ((samples_frequencies.find ("<011> : 2 0") != string::npos) &&
               (samples_frequencies.find ("<110> : 1 2") != string::npos) &&
               (samples_frequencies.find ("<010> : 2 2") != string::npos) &&
               (samples_frequencies.find ("<000> : 3 2") != string::npos) &&
               (samples_frequencies.find ("<111> : ") == string::npos))
		   )
			return false;

		// |X| must be greater than 0
		//
		X.remove_element (0);
		samples_frequencies = cfm.print_label_frequencies (& X);
		if (! ((samples_frequencies.find ("<00> : 3 2") != string::npos) &&
               (samples_frequencies.find ("<10> : 3 4") != string::npos) &&
               (samples_frequencies.find ("<11> : 2 0") != string::npos) &&
               (samples_frequencies.find ("<01> : ") == string::npos))
		   )
			return false;

		return true;
	}


	bool it_should_calculate_the_conditional_entropy ()
	{
		ElementSet set ("input/CostFunctionTestMCE03.dat", 3);
		ElementSubset X ("", & set);
		CostFunctionMock cfm (& set);
		string entropy;

		X.set_complete_subset ();
		entropy = cfm.print_conditional_entropy (& X);
		if (! ((entropy.find ("<011> : 0.918296") != string::npos) &&
               (entropy.find ("<000> : 0.970951") != string::npos) &&
               (entropy.find ("<010> : 0") != string::npos) &&
               (entropy.find ("<111> : ") == string::npos))
		   )
			return false;

		return true;
	}


	bool it_should_calculate_the_mean_conditional_entropy ()
	{
		ElementSet set_1 ("input/CostFunctionTestMCE03.dat", 3);
		ElementSet set_2 ("input/CostFunctionTestMCE04.dat", 3);
		MeanConditionalEntropy cf_1 (& set_1);
		MeanConditionalEntropy cf_2 (& set_2);
		ElementSubset X ("X", & set_1);
		ElementSubset Y ("Y", & set_2);
		float cost;

		X.set_complete_subset ();
		cost = cf_1.cost (& X);
		if (! ((cost >= 0.760) && (cost <= 0.761)) )
			return false;

		X.remove_element (2);
		cost = cf_1.cost (& X);
		if (! ((cost >= 0.8463) && (cost <= 0.8465)) )
			return false;

		Y.set_complete_subset ();  // testing the penalty for one occurrence
		cost = cf_2.cost (& Y);
		if (! ((cost >= 0.6666) && (cost <= 0.6667)) )
			return false;

		return true;
	}


	bool it_should_add_and_retrieve_the_elapsed_time ()
	{
		ElementSet set ("a_set", 1, 1);
		CostFunctionMock cfm (& set);
		int t1 =    10,     // 0.00001 second
		    t2 =   100,     // 0.0001 second
		    t3 =   500,     // 0.0005 second
		    t4 =  1000,     // 0.001 second
		    t5 = 2000000,   // 2 seconds
            elapsed_time;

		// elapsed_time = 1500 microseconds
		cfm.add_elapsed_time (t3);
		cfm.add_elapsed_time (t4);
		elapsed_time = cfm.override_get_the_elapsed_time_of_the_calls_of_this_cost_function();
		if (!(elapsed_time >= 0 && elapsed_time <= 3500)) // 2000 us == 2 ms precision
			return false;

		// elapsed_time = 1520 usec
		cfm.add_elapsed_time (t1);
		cfm.add_elapsed_time (t1);
		elapsed_time = cfm.override_get_the_elapsed_time_of_the_calls_of_this_cost_function();
		if (!(elapsed_time >= 0 && elapsed_time <= 3520)) // 2 ms precision
			return false;

		// elapsed_time = 2120 usec
		cfm.add_elapsed_time (t3);
		cfm.add_elapsed_time (t2);
		elapsed_time = cfm.override_get_the_elapsed_time_of_the_calls_of_this_cost_function();
		if (!(elapsed_time >= 120 && elapsed_time <= 4120)) // 2 ms precision
			return false;

		// elapsed_time = 2002120 usec
		cfm.add_elapsed_time (t5);
		elapsed_time = cfm.override_get_the_elapsed_time_of_the_calls_of_this_cost_function();
		if (!(elapsed_time >= 2000120 && elapsed_time <= 2004120)) // 2 ms precision
			return false;

		return true;
	}

} // end of namespace

