//
// SFSTest.cpp -- implementation of the namespace "SFSTest".
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

#include "SFSTest.h"

namespace SFSTest
{

	bool it_should_find_a_local_minimum ()
	{
		ElementSet set1 ("set", "input/CostFunctionTest3ElementsFile.xml");
		ElementSet set3 ("set", "input/UCSTest7ElementsFileA.xml");
		SFS sfs1;
		SFS sfs3;
		MeanAbsSum c1 (&set1);
		HammingDistance c3 (&set3);
		sfs1.set_parameters (&c1, &set1, false);
		sfs1.get_minima_list (1);
		if (sfs1.print_list_of_minima ().find ("<010>") == string::npos)
			return false;
		sfs3.set_parameters (&c3, &set3, false);
		sfs3.get_minima_list (1);
		if (sfs3.print_list_of_minima ().find ("<0011100>") == string::npos)
			return false;
		return true;
	}



	bool it_should_find_a_global_minimum(){
		ElementSet set1 ("set", "input/CostFunctionTest3ElementsFile.xml");
		ElementSet set2 ("set", "input/UCSTest9ElementsFileA.xml");
		ElementSet set3 ("set", "input/UCSTest7ElementsFileA.xml");
		SFS sfs1;
		SFS sfs2;
		SFS sfs3;
		MeanAbsSum c1 (&set1);
		MeanAbsSum c2 (&set2);
		HammingDistance c3 (&set3);
		sfs1.set_parameters (&c1, &set1, false);
		sfs1.get_minima_list (1);
		if (sfs1.print_list_of_minima ().find ("<010>") == string::npos)
			return false;
		sfs2.set_parameters (&c2, &set2, false);
		sfs2.get_minima_list( 3);
		if ((sfs2.print_list_of_minima ().find ("<000010000>") == string::npos) ||
		    (sfs2.print_list_of_minima ().find ("<100100000>") == string::npos) ||
			(sfs2.print_list_of_minima ().find ("<011000000>") == string::npos) )
			return false;
		sfs3.set_parameters (&c3, &set3, false);
		sfs3.get_minima_list (1);
		if (sfs3.print_list_of_minima ().find ("<0011100>") == string::npos)
			return false;
		return true;
	}

	bool it_should_store_all_the_visited_subsets ()
	{
		ElementSet set1 ("S1", 3, 1);    // |S1| = 3
		SFS sfs1;
		string list;
		MeanAbsSum c1 (&set1);
		sfs1.set_parameters (&c1, &set1, true);
		sfs1.get_minima_list (1);
		list = sfs1.print_list_of_visited_subsets ();
		//
		// For 2^3 it should miss either <110>, <101> or <011>!!!
		//
		if ((list.find ("<000>") != string::npos) &&
		    (list.find ("<001>") != string::npos) &&
		    (list.find ("<010>") != string::npos) &&
		    (list.find ("<100>") != string::npos) &&
		    (list.find ("<101>") != string::npos) &&
		    (list.find ("<011>") != string::npos) &&
		    (list.find ("<111>") != string::npos))
			return true;
		else
			return false;
	}


	bool it_should_give_the_number_of_the_visited_subsets ()
	{
		ElementSet set1 ("S1", 3, 1);    // |S1| = 3
		SFS sfs;
		MeanAbsSum c1 (&set1);
		sfs.set_parameters (&c1, &set1, true);
		sfs.get_minima_list (1);
		if ((sfs.print_list_of_visited_subsets ().size () / (set1.get_set_cardinality() + 4)) == 7)
			return true;
		else
			return false;
	}


	// It was tested up to 2^32, but for large n it may take a LONG time... :-)
	//
	bool it_should_converge_for_large_hamming_sets ()
	{
		unsigned int i, n = 16; // 2^16, around 64K subsets
		string minimum = " <";
		ElementSet set1 ("set", n, 2);   // rand() % 2 results in a "hamming" instance.
		SFS sfs1;
		HammingDistance c1 (&set1);
		sfs1.set_parameters (&c1, &set1, false);
		sfs1.get_minima_list (1);
		for(i = 0; i < n; i++)
		{       // gets the minimum from the set1
			if ((set1.get_element (i))->get_element_value (0) == 0)
				minimum.append ("0");
			else
				minimum.append ("1");
		}
		minimum.append ("> ");
		if (sfs1.print_list_of_minima ().find (minimum) == string::npos)
			return false;
		return true;
	}

} // end of namespace
