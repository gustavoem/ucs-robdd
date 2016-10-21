//
// UCSROBDD6Test.cpp -- implementation of the namespace "UCSROBDD6Test".
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

#include "UCSROBDD3Test.h"

namespace UCSROBDD3Test
{

	bool it_should_find_a_global_minimum ()
	{
		ElementSet set1 ("set", "input/CostFunctionTest3ElementsFile.xml");
		ElementSet set2 ("set", "input/UCSTest9ElementsFileA.xml");
		ElementSet set3 ("set", "input/UCSTest7ElementsFileA.xml");
		ElementSet set4 ("set", "input/CostFunctionTestExplicitFuncA.xml");
		MeanAbsSum c1 (&set1);
		MeanAbsSum c2 (&set2);
		HammingDistance c3 (&set3);
		Explicit c4 (&set4);
		UCSROBDD6 ucs1;
		UCSROBDD6 ucs2;
		UCSROBDD6 ucs3;
		UCSROBDD6 ucs4;
		ucs1.set_parameters (&c1, &set1, false);
		ucs1.get_minima_list (1);
		if (ucs1.print_list_of_minima ().find ("<010>") == string::npos)
			return false;
		ucs2.set_parameters (&c2, &set2, false);
		ucs2.get_minima_list (3);
		if ((ucs2.print_list_of_minima ().find ("<000010000>") == string::npos) ||
		    (ucs2.print_list_of_minima ().find ("<100100000>") == string::npos) ||
			(ucs2.print_list_of_minima ().find ("<011000000>") == string::npos) )
			return false;
		ucs3.set_parameters (&c3, &set3, false);
		ucs3.get_minima_list (1);
		if (ucs3.print_list_of_minima ().find ("<0011100>") == string::npos)
			return false;
		ucs4.set_parameters (&c4, &set4, false);
		ucs4.get_minima_list (1);
		if (ucs4.print_list_of_minima ().find ("<101>") == string::npos)
			return false;
		return true;
	}


	// It was tested up to 2^32, but for large n it may take a LONG time... :-)
	//
	bool it_should_converge_for_large_hamming_sets ()
	{
		unsigned int i, n = 12; // 2^16 is around 64K subsets
		string minimum = " <";
		ElementSet set1 ("set", n, 2);   // rand() % 2 results in a "hamming" instance.
		UCSROBDD6 ucs1;
		HammingDistance c1 (&set1);
		ucs1.set_parameters (&c1, &set1, false);
		ucs1.get_minima_list (1);
		for (i = 0; i < n; i++)
		{       // gets the minimum from the set1
			if( (set1.get_element (i))->get_element_value (0) == 0)
				minimum.append ("0");
			else
				minimum.append ("1");
		}
		minimum.append ("> ");
		if (ucs1.print_list_of_minima ().find (minimum) == string::npos)
			return false;
		return true;
	}


	// It was tested up to 2^32, but for large n it may take a LONG time... :-)
	//
	bool it_should_converge_for_large_abs_sum_sets ()
	{
		unsigned int n = 16;
		ElementSet set1 ("set", n, 10000); // mean_abs_sum instance.
		UCSROBDD6 ucs1;
		MeanAbsSum c1 (&set1);
		ucs1.set_parameters (&c1, &set1, false);
		ucs1.get_minima_list (1);
		return true;
	}

	// repeats the test k times (default: k = 10)
	//
	bool it_should_always_give_the_correct_answer ()
	{
		ElementSet set1 ("set1", "input/UCSTest4ElementsFileA.xml");
		ElementSet set2 ("set2", "input/UCSTest4ElementsFileB.xml");
		ElementSet set3 ("set3", "input/UCSTest9ElementsFileB.xml");
		ElementSet set4 ("set4", "input/UCSTest7ElementsFileB.xml");
		ElementSet set5 ("set5", "input/UCSTest13ElementsFileA.xml");
		ElementSet set6 ("set6", "input/UCSTest7ElementsFileC.xml");
	//	ElementSet set7 ("set7", "input/UCSTest7ElementsFileD.xml");
	//	ElementSet set8 ("set8", "input/UCSTest5ElementsFileA.xml");
	//	ElementSet set9 ("set9", "input/UCSTest17ElementsFileA.xml");
	//	ElementSet setA ("setA", "input/UCSTest11ElementsFileA.xml");

		MeanAbsSum c1 (&set1);
		MeanAbsSum c2 (&set2);
		MeanAbsSum c3 (&set3);
		MeanAbsSum c4 (&set4);
		MeanAbsSum c5 (&set5);
		MeanAbsSum c6 (&set6);

	//	AbsSum c7 (&set7);
	//	AbsSum c8 (&set8);
	//	AbsSum c9 (& set9);
	//	AbsSum cA (& setA);

		UCSROBDD6 * ucs;

		int i,
		    k = 10;  // change the value of k for more (less) tests
		string result;
	    for (i = 1; i <= k; i++)
		{
			ucs = new UCSROBDD6 ();
			ucs->set_parameters (&c1, &set1, false);
			ucs->get_minima_list (1);
			result.clear ();
			result = ucs->print_list_of_minima ();
			delete ucs;
			if (result.find ("<0110>") == string::npos)
				return false;
		}
		for (i = 1; i <= k; i++)
		{
			ucs = new UCSROBDD6 ();
			ucs->set_parameters (&c2, &set2, false);
			ucs->get_minima_list (1);
			result.clear ();
			result = ucs->print_list_of_minima ();
			delete ucs;
			if (result.find ("<0011>") == string::npos)
				return false;
		}
		for (i = 1; i <= k; i++)
		{
			ucs = new UCSROBDD6 ();
			ucs->set_parameters (&c3, &set3, false);
			ucs->get_minima_list (1);
			result.clear ();
			result = ucs->print_list_of_minima ();
			delete ucs;
			if (result.find ("<010001100>") == string::npos)
				return false;
		}
		for (i = 1; i <= k; i++)
		{
			ucs = new UCSROBDD6 ();
			ucs->set_parameters (&c4, &set4, false);
			ucs->get_minima_list (1);
			result.clear ();
			result = ucs->print_list_of_minima ();
			delete ucs;
			if (result.find ("<0101101>") == string::npos)
				return false;
		}
		for (i = 1; i <= k; i++)
		{
			ucs = new UCSROBDD6 ();
			ucs->set_parameters (&c5, &set5, false);
			ucs->get_minima_list (1);
			result.clear ();
			result = ucs->print_list_of_minima ();
			delete ucs;
			if (result.find ("<0000001000010>") == string::npos)
				return false;
		}
		for (i = 1; i <= k; i++)
		{
			ucs = new UCSROBDD6 ();
			ucs->set_parameters (&c6, &set6, false);
			ucs->get_minima_list (1);
			result.clear ();
			result = ucs->print_list_of_minima ();
			delete ucs;
			if (result.find ("<0001101>") == string::npos)
				return false;
		}
		// TODO -- to fix the bug loading set7 and set8 in a row
		/* (set_name of the former is appended into the latter;
		 *  probably error in the XML parser)
	 	for (i = 1; i <= k; i++)
		{
			ucs = new UCSROBDD6 ();
			ucs->set_parameters (&c7, &set7, false);
			ucs->get_minima_list (1);
			result.clear ();
			result = ucs->print_list_of_minima ();
			delete ucs;
			if (result.find ("<0100101>") == string::npos)
				return false;
		}
		for (i = 1; i <= k; i++)
		{
			ucs = new UCSROBDD6 ();
			ucs->set_parameters (&c8, &set8, false);
			ucs->get_minima_list (1);
			result.clear ();
			result = ucs->print_list_of_minima ();
			delete ucs;
			if (result.find ("<10101>") == string::npos)
				return false;
		}
		for (i = 1; i <= k; i++)
		{
			ucs = new UCSROBDD6 ();
			ucs->set_parameters (& c9, & set9, false);
			ucs->get_minima_list (1);
			result.clear ();
			result = ucs->print_search_report ();
			delete ucs;
			if (result.find ("<00010000010010110>") == string::npos)
			{
				cout << "\nError: " << i << " : " << result <<  endl;
				return false;

			}
		}
		for (i = 1; i <= k; i++)
		{
			ucs = new UCSROBDD6 ();
			ucs->set_parameters (& cA, & setA, false);
			ucs->get_minima_list (1);
			result.clear ();
			result = ucs->print_search_report ();
			delete ucs;
			if (result.find ("<01000000101>") == string::npos)
			{
				cout << "\nError: " << i << " : " << result <<  endl;
				return false;

			}
		} */
		return true;
	}

} // end of namespace
