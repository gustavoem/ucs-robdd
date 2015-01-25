//
// PosetForestSearchTest.cpp -- implementation of the namespace "PosetForestSearchTest".
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

#include "PosetForestSearchTest.h"

namespace PosetForestSearchTest
{

	bool it_should_branch_in_a_lower_tree ()
	{
		bool verification = true;
		ElementSet set1 ("set1", "input/PFSTestExplicitFuncA.xml");
		ElementSubset X ("", & set1);
		Explicit c1 (& set1);
		PosetForestSearch::Node * N;
		PosetForestSearchMock pfsm1;
		map<string, PosetForestSearch::Node *> Forest_A, Forest_B;
		map<string, PosetForestSearch::Node *>::iterator it;

		pfsm1.set_parameters (&c1, &set1, false);

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->leftmost = 0;
		N->cost = c1.cost (N->vertex); // c(000) = 3
		Forest_A.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		N = pfsm1.lower_forest_branch_mock (& Forest_A, & Forest_B);

		// the node N should not be in Forest_A
		//
		if (Forest_A.find (N->vertex->print_subset ()) == Forest_A.end ())
		{

			// if N[vertex] = 101, N[adjacent] = 000, then Forest_A has two nodes:
			// A1[vertex] = 100, A1[adjacent] = 010
			// A2[vertex] = 000, A2[adjacent] = 011
			//
			if (( N->vertex->print_subset ().find ("<101>") != string::npos ) &&
					( N->adjacent->print_subset ().find ("<000>") != string::npos ) )
			{
				X.set_empty_subset (); // <000>
				it = Forest_A.find (X.print_subset());
				X.add_element (1);  // <011>
				X.add_element (2);
				if (! ( (it != Forest_A.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				X.set_empty_subset (); // <100>
				X.add_element (0);
				it = Forest_A.find (X.print_subset());
				X.set_empty_subset (); // <010>
				X.add_element (1);
				if (! ( (it != Forest_A.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				if (Forest_A.size() != 2)
					verification = false;
			}

			// if N[vertex] = 110, N[adjacent] = 001, then Forest_A has two nodes:
			// A1[vertex] = 100, A1[adjacent] = 001
			// A2[vertex] = 000, A2[adjacent] = 011
			//
			else if (( N->vertex->print_subset ().find ("<110>") != string::npos ) &&
					( N->adjacent->print_subset ().find ("<001>") != string::npos ) )
			{
				X.set_empty_subset (); // <100>
				X.add_element (0);
				it = Forest_A.find (X.print_subset());
				X.set_empty_subset (); // <001>
				X.add_element (2);
				if (! ( (it != Forest_A.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				X.set_empty_subset (); // <000>
				it = Forest_A.find (X.print_subset());
				X.add_element (2); // <011>
				X.add_element (1);
				if (! ( (it != Forest_A.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				if (Forest_A.size() != 2)
					verification = false;
			}

			// if N[vertex] = 011, N[adjacent] = 000, then Forest_A has two nodes:
			// A1[vertex] = 010, A1[adjacent] = 000
			// A2[vertex] = 000, A2[adjacent] = 101
			//
			else if (( N->vertex->print_subset ().find ("<011>") != string::npos ) &&
					( N->adjacent->print_subset ().find ("<000>") != string::npos ) )
			{
				X.set_empty_subset (); // <010>
				X.add_element (1);
				it = Forest_A.find (X.print_subset());
				X.set_empty_subset (); // <000>
				if (! ( (it != Forest_A.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				X.set_empty_subset (); // <000>
				it = Forest_A.find (X.print_subset());
				X.add_element (2); // <101>
				X.add_element (0);
				if (! ( (it != Forest_A.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				if (Forest_A.size() != 2)
					verification = false;
			}

			// if N[vertex] = 001, N[adjacent] = 000, then Forest_A has one node:
			// A1[vertex] = 000, A1[adjacent] = 110
			//
			else if (( N->vertex->print_subset ().find ("<001>") != string::npos ) &&
					( N->adjacent->print_subset ().find ("<000>") != string::npos ) )
			{
				X.set_empty_subset (); // <000>
				it = Forest_A.find (X.print_subset());
				X.set_empty_subset (); // <110>
				X.add_element (0);
				X.add_element (1);
				if (! ( (it != Forest_A.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				if (Forest_A.size() != 1)
					verification = false;
			}
			else
				verification = false;
		}
		else
			verification = false;

		delete N->vertex;
		delete N->adjacent;
		delete N;

		// delete the nodes in the collection and end the test.
		//
		for (it = Forest_A.begin (); it != Forest_A.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}
		Forest_A.clear ();

		// Now we will test in a forest with roots:
		// A1[vertex] = 000, A2[adjacent] = 000
		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->adjacent = new ElementSubset ("", & set1);
		N->leftmost = 0;
		N->cost = c1.cost (N->vertex); // c(000) = 3
		Forest_A.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));
		// A2[vertex] = 100, A1[adjacent] = 001
		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->add_element (0);
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->add_element (2);
		N->leftmost = 2;
		N->cost = c1.cost (N->vertex); // c(100) = 2
		Forest_A.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		N = pfsm1.lower_forest_branch_mock (& Forest_A, & Forest_B);

		// the node N should not be in Forest_A
		//
		if (Forest_A.find (N->vertex->print_subset ()) == Forest_A.end ())
		{

			// if N[vertex] = 000, N[adjacent] = 000, then Forest_A has one node:
			// A1[vertex] = 100, A1[adjacent] = 001
			//
			if (( N->vertex->print_subset ().find ("<000>") != string::npos ) &&
					( N->adjacent->print_subset ().find ("<000>") != string::npos ) )
			{
				X.set_empty_subset (); // <100>
				X.add_element (0);
				it = Forest_A.find (X.print_subset());
				X.set_empty_subset ();
				X.add_element (2);  // <001>
				if (! ( (it != Forest_A.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				if (Forest_A.size() != 1)
					verification = false;
			}

			// if N[vertex] = 101, N[adjacent] = 000, then Forest_A has two nodes:
			// A1[vertex] = 100, A1[adjacent] = 000
			// A2[vertex] = 000, A2[adjacent] = 000
			//
			else if (( N->vertex->print_subset ().find ("<101>") != string::npos ) &&
					( N->adjacent->print_subset ().find ("<000>") != string::npos ) )
			{
				X.set_empty_subset (); // <100>
				X.add_element (0);
				it = Forest_A.find (X.print_subset());
				X.set_empty_subset (); // <000>
				if (! ( (it != Forest_A.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				X.set_empty_subset (); // <000>
				it = Forest_A.find (X.print_subset());
				if (! ( (it != Forest_A.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				if (Forest_A.size() != 2)
					verification = false;
			}
			else
				verification = false;
		}
		else
			verification = false;

		delete N->vertex;
		delete N->adjacent;
		delete N;

		// delete the nodes in the collection and end the test.
		//
		for (it = Forest_A.begin (); it != Forest_A.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}
		Forest_A.clear ();

		return verification;
	}


	bool it_should_branch_in_an_upper_tree ()
	{
		bool verification = true;
		ElementSet set1 ("set1", "input/PFSTestExplicitFuncA.xml");
		ElementSubset X ("", & set1);
		Explicit c1 (& set1);
		PosetForestSearch::Node * N;
		PosetForestSearchMock pfsm1;
		map<string, PosetForestSearch::Node *> Forest_A, Forest_B;
		map<string, PosetForestSearch::Node *>::iterator it;

		pfsm1.set_parameters (&c1, &set1, false);

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->set_complete_subset ();
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->leftmost = 0;
		N->cost = c1.cost (N->vertex); // c(111) = 3
		Forest_B.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		N = pfsm1.upper_forest_branch_mock (& Forest_A, & Forest_B);

		// the node N should not be in Forest_B
		//
		if (Forest_B.find (N->vertex->print_subset ()) == Forest_B.end ())
		{

			// if N[vertex] = 000, N[adjacent] = 000, then Forest_B has three nodes:
			// A1[vertex] = 111, A1[adjacent] = 011
			// A2[vertex] = 011, A2[adjacent] = 001
			// A3[vertex] = 001, A3[adjacent] = 000
			//
			if (( N->vertex->print_subset ().find ("<000>") != string::npos ) &&
					( N->adjacent->print_subset ().find ("<000>") != string::npos ) )
			{
				X.set_complete_subset (); // <111>
				it = Forest_B.find (X.print_subset());
				X.remove_element (0);  // <011>
				if (! ( (it != Forest_B.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				it = Forest_B.find (X.print_subset());
				X.remove_element (1); // <001>
				if (! ( (it != Forest_B.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				it = Forest_B.find (X.print_subset());
				X.remove_element (2); // <000>
				if (! ( (it != Forest_B.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				if (Forest_B.size() != 3)
					verification = false;
			}

			// if N[vertex] = 010, N[adjacent] = 000, then Forest_B has two nodes:
			// A1[vertex] = 111, A1[adjacent] = 011
			// A2[vertex] = 011, A2[adjacent] = 010
			//
			else if (( N->vertex->print_subset ().find ("<010>") != string::npos ) &&
					( N->adjacent->print_subset ().find ("<000>") != string::npos ) )
			{
				X.set_complete_subset (); // <111>
				it = Forest_B.find (X.print_subset());
				X.remove_element (0); // <011>
				if (! ( (it != Forest_B.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				it = Forest_B.find (X.print_subset());
				X.remove_element (2); // <010>
				if (! ( (it != Forest_B.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				if (Forest_B.size() != 2)
					verification = false;
			}

			// if N[vertex] = 100, N[adjacent] = 000, then Forest_B has two nodes:
			// A1[vertex] = 111, A1[adjacent] = 101
			// A2[vertex] = 101, A2[adjacent] = 000
			//
			else if (( N->vertex->print_subset ().find ("<100>") != string::npos ) &&
					( N->adjacent->print_subset ().find ("<000>") != string::npos ) )
			{
				X.set_complete_subset (); // <111>
				it = Forest_B.find (X.print_subset());
				X.remove_element (1); // <101>
				if (! ( (it != Forest_B.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				it = Forest_B.find (X.print_subset());
				X.set_empty_subset (); // <000>
				if (! ( (it != Forest_B.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				if (Forest_B.size() != 2)
					verification = false;
			}

			// if N[vertex] = 110, N[adjacent] = 000, then Forest_B has one node:
			// A1[vertex] = 111, A1[adjacent] = 110
			//
			else if (( N->vertex->print_subset ().find ("<110>") != string::npos ) &&
					( N->adjacent->print_subset ().find ("<000>") != string::npos ) )
			{
				X.set_complete_subset (); // <111>
				it = Forest_B.find (X.print_subset());
				X.remove_element (2); // <110>
				if (! ( (it != Forest_B.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				if (Forest_B.size() != 1)
					verification = false;
			}
			else
				verification = false;
		}
		else
			verification = false;

		delete N->vertex;
		delete N->adjacent;
		delete N;

		// delete the nodes in the collection and end the test.
		//
		for (it = Forest_B.begin (); it != Forest_B.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}
		Forest_B.clear ();

		// Now we will test in a forest with roots:
		// A1[vertex] = 111, A2[adjacent] = 000
		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->set_complete_subset ();
		N->adjacent = new ElementSubset ("", & set1);
		N->leftmost = 0;
		N->cost = c1.cost (N->vertex); // c(111) = 3
		Forest_B.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));
		// A2[vertex] = 001, A1[adjacent] = 001
		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->add_element (2);
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->add_element (2);
		N->leftmost = 2;
		N->cost = c1.cost (N->vertex); // c(001) = 2
		Forest_B.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		N = pfsm1.upper_forest_branch_mock (& Forest_A, & Forest_B);

		// the node N should not be in Forest_B
		//
		if (Forest_B.find (N->vertex->print_subset ()) == Forest_B.end ())
		{

			// if N[vertex] = 111, N[adjacent] = 000, then Forest_B has one node:
			// A1[vertex] = 001, A1[adjacent] = 001
			//
			if (( N->vertex->print_subset ().find ("<111>") != string::npos ) &&
					( N->adjacent->print_subset ().find ("<000>") != string::npos ) )
			{
				X.set_empty_subset (); // <001>
				X.add_element (2);
				it = Forest_B.find (X.print_subset());
				if (! ( (it != Forest_B.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				if (Forest_B.size() != 1)
					verification = false;
			}

			// if N[vertex] = 000, N[adjacent] = 000, then Forest_B has two nodes:
			// A1[vertex] = 111, A1[adjacent] = 000
			// A2[vertex] = 001, A2[adjacent] = 000
			//
			else if (( N->vertex->print_subset ().find ("<000>") != string::npos ) &&
					( N->adjacent->print_subset ().find ("<000>") != string::npos ) )
			{

				X.set_complete_subset (); // <111>
				it = Forest_B.find (X.print_subset());
				X.set_empty_subset (); // <000>
				if (! ( (it != Forest_B.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				X.add_element (2); // <001>
				it = Forest_B.find (X.print_subset());
				X.remove_element (2); // <000>
				if (! ( (it != Forest_B.end ()) && (it->second->adjacent->is_equal (&X)) ) )
					verification = false;
				if (Forest_B.size() != 2)
					verification = false;
			}
			else
				verification = false;
		}
		else
			verification = false;

		delete N->vertex;
		delete N->adjacent;
		delete N;

		// delete the nodes in the collection and end the test.
		//
		for (it = Forest_B.begin (); it != Forest_B.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}
		Forest_B.clear ();

		return verification;
	}


	bool it_should_search_the_lower_children ()
	{
		bool verification = true;
		ElementSet set1 ("set1", "input/PFSTestExplicitFuncA.xml");
		ElementSubset M ("", & set1), X ("", & set1), Y ("", & set1);
		Explicit c1 (& set1);
		PosetForestSearch::Node * N, * N2;
		PosetForestSearchMock pfsm1;
		map<string, PosetForestSearch::Node *> Forest_B;
		map<string, PosetForestSearch::Node *>::iterator it;

		pfsm1.set_parameters (&c1, &set1, false);

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->set_complete_subset ();
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->adjacent->remove_element (1);   // <111> does not have the child <101>
		N->leftmost = 0;
		N->cost = c1.cost (N->vertex); // c(111) = 3
		Forest_B.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		M.add_element (2); // M = Y = 001
		Y.add_element (2);

		pfsm1.search_lower_children_mock (& Forest_B, NULL, & M, & Y);

		// Forest B should have <000> and <111> and not have <001>
		//

		X.set_empty_subset (); // <000>
		it = Forest_B.find (X.print_subset());
		if (it == Forest_B.end ())
			verification = false;
		X.set_complete_subset (); // <111>
		it = Forest_B.find (X.print_subset());
		if (it == Forest_B.end ())
			verification = false;
		X.set_empty_subset (); // <001>
		X.add_element (2);
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;
		X.add_element (1);   // <011>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;


		M.add_element (1); // M = 011, Y = 001

		pfsm1.search_lower_children_mock (& Forest_B, NULL, & M, & Y);

		// Forest B should have <010> and not have <001> and <011>
		//

		X.set_empty_subset (); // <010>
		X.add_element (1);
		it = Forest_B.find (X.print_subset());
		if (it == Forest_B.end ())
			verification = false;
		X.add_element (2); // <011>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;
		X.set_empty_subset (); // <001>
		X.add_element (2);
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;


		M.copy (N->vertex); // M = N[vertex] = 111, Y = 001

		N2 = new PosetForestSearch::Node;
		N2->vertex   = new ElementSubset ("", & set1);
		N2->vertex->add_element(1);    // N2[vertex] = 011
		N2->vertex->add_element(2);
		N2->adjacent = new ElementSubset ("", & set1);
		N2->leftmost = 1;
		N2->cost = c1.cost (N2->vertex);
		Forest_B.insert (pair<string, PosetForestSearch::Node *> (N2->vertex->print_subset (), N2));


		pfsm1.search_lower_children_mock (& Forest_B, N, & M, & Y);


		// Forest B should have <111> and <110> such that c(110) = 777,
		// and not have <101> and <011>
		//

		X.set_complete_subset (); // <110>
		X.remove_element (2);
		it = Forest_B.find (X.print_subset());
		if (it == Forest_B.end ())
			verification = false;
		X.set_complete_subset ();
		X.remove_element (0); // <011>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;
		X.set_complete_subset (); // <101>
		X.remove_element (1);
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;
		X.set_complete_subset (); // <111>
		it = Forest_B.find (X.print_subset());
		if (it == Forest_B.end ())
			verification = false;

		// delete the nodes in the collection and end the test.
		//
		for (it = Forest_B.begin (); it != Forest_B.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}

		return verification;
	}


	bool it_should_search_the_upper_children ()
	{
		bool verification = true;
		ElementSet set1 ("set1", "input/PFSTestExplicitFuncA.xml");
		ElementSubset M ("", & set1), X ("", & set1), Y ("", & set1);
		Explicit c1 (& set1);
		PosetForestSearch::Node * N, * N2;
		PosetForestSearchMock pfsm1;
		map<string, PosetForestSearch::Node *> Forest_A;
		map<string, PosetForestSearch::Node *>::iterator it;

		pfsm1.set_parameters (&c1, &set1, false);

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->adjacent->remove_element (1);   // <000> does not have the child <010>
		N->leftmost = 0;
		N->cost = c1.cost (N->vertex); // c(000) = 3
		Forest_A.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		M.add_element (0); // M = Y = 110
		M.add_element (1);
		Y.copy (& M);

		pfsm1.search_upper_children_mock (& Forest_A, NULL, & M, & Y);

		// Forest A should have <000> and <111> and not have <110>
		//

		X.set_empty_subset (); // <000>
		it = Forest_A.find (X.print_subset());
		if (it == Forest_A.end ())
			verification = false;
		X.set_complete_subset (); // <111>
		it = Forest_A.find (X.print_subset());
		if (it == Forest_A.end ())
			verification = false;
		X.set_empty_subset (); // <110>
		X.add_element (0);
		X.add_element (1);
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		M.remove_element (1); // M = 100, Y = 110

		pfsm1.search_upper_children_mock (& Forest_A, NULL, & M, & Y);

		// Forest A should have <101> and not have <110> and <100>
		//

		X.set_complete_subset (); // <101>
		X.remove_element (1);
		it = Forest_A.find (X.print_subset());
		if (it == Forest_A.end ())
			verification = false;
		X.remove_element (2); // <100>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;
		X.add_element (1); // <110>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		M.copy (N->vertex); // M = N[vertex] = 000, Y = 001

		N2 = new PosetForestSearch::Node;
		N2->vertex   = new ElementSubset ("", & set1);
		N2->vertex->add_element(0);    // N2[vertex] = 100
		N2->adjacent = new ElementSubset ("", & set1);
		N2->leftmost = 1;
		N2->cost = c1.cost (N2->vertex);
		Forest_A.insert (pair<string, PosetForestSearch::Node *> (N2->vertex->print_subset (), N2));

		pfsm1.search_upper_children_mock (& Forest_A, N, & M, & Y);

		// Forest A should have <000> and <001> such that c(001) = 777,
		// and not have <010> and <100>
		//

		X.set_empty_subset (); // <001>
		X.add_element (2);
		it = Forest_A.find (X.print_subset());
		if (it == Forest_A.end ())
			verification = false;
		X.set_empty_subset ();
		X.add_element (0); // <100>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;
		X.set_empty_subset (); // <010>
		X.add_element (1);
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;
		X.set_empty_subset (); // <000>
		it = Forest_A.find (X.print_subset());
		if (it == Forest_A.end ())
			verification = false;

		// delete the nodes in the collection and end the test.
		//
		for (it = Forest_A.begin (); it != Forest_A.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}

		return verification;
	}


	bool it_should_search_an_upper_root ()
	{
		bool verification = true;
		ElementSet set1 ("set1", "input/PFSTestExplicitFuncA.xml");
		ElementSubset M ("", & set1), X ("", & set1);
		Explicit c1 (& set1);
		PosetForestSearch::Node * N;
		PosetForestSearchMock pfsm1;
		map<string, PosetForestSearch::Node *> Forest_B;
		map<string, PosetForestSearch::Node *>::iterator it;

		pfsm1.set_parameters (&c1, &set1, false);

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->set_complete_subset ();
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->leftmost = 0;
		N->cost = c1.cost (N->vertex); // c(111) = 3
		Forest_B.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		M.set_empty_subset (); // M = 000

		pfsm1.search_upper_root_mock (& Forest_B, & M);

		// Forest B should have <001>, <011>, and <111> and not have <000>
		//
		X.set_empty_subset (); // <000>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.set_complete_subset (); // <111>
		it = Forest_B.find (X.print_subset());
		if ((it == Forest_B.end ()) ||
				(it->second->adjacent->has_element (0))  // N[adjacent] = 011
					|| (! it->second->adjacent->has_element (1))
					|| (! it->second->adjacent->has_element (2)) )
			verification = false;

		X.set_empty_subset (); // <001>
		X.add_element (2);
		it = Forest_B.find (X.print_subset());
		if ((it == Forest_B.end ()) || (! it->second->adjacent->is_empty ()) )  // N[adjacent] = 000
			verification = false;

		X.set_empty_subset ();
		X.add_element (1);   // <011>
		X.add_element (2);
		it = Forest_B.find (X.print_subset());
		if ((it == Forest_B.end ()) ||
				(it->second->adjacent->has_element (0))  // N[adjacent] = 001
					|| (it->second->adjacent->has_element (1))
					|| (! it->second->adjacent->has_element (2)) )
			verification = false;

		// delete the nodes in the collection and end the test.
		//
		for (it = Forest_B.begin (); it != Forest_B.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}
		Forest_B.clear ();

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->set_complete_subset ();
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->leftmost = 0;
		N->cost = c1.cost (N->vertex); // c(111) = 3
		Forest_B.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		M.set_complete_subset ();  // <101>
		M.remove_element (1);

		pfsm1.search_upper_root_mock ( & Forest_B, & M);

		// Forest B should have <111> and not have <101>
		//
		X.set_complete_subset (); // <101>
		X.remove_element (1);
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.set_complete_subset (); // <111>
		it = Forest_B.find (X.print_subset());
		if ((it == Forest_B.end ()) ||
				(! it->second->adjacent->has_element (0))  // N[adjacent] = 101
					|| (it->second->adjacent->has_element (1))
					|| (! it->second->adjacent->has_element (2)) )
			verification = false;

		for (it = Forest_B.begin (); it != Forest_B.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}

		return verification;
	}


	bool it_should_search_a_lower_root ()
	{
		bool verification = true;
		ElementSet set1 ("set1", "input/PFSTestExplicitFuncA.xml");
		ElementSubset M ("", & set1), X ("", & set1);
		Explicit c1 (& set1);
		PosetForestSearch::Node * N;
		PosetForestSearchMock pfsm1;
		map<string, PosetForestSearch::Node *> Forest_A;
		map<string, PosetForestSearch::Node *>::iterator it;

		pfsm1.set_parameters (&c1, &set1, false);

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->leftmost = 0;
		N->cost = c1.cost (N->vertex); // c(000) = 3
		Forest_A.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		M.set_complete_subset (); // M = 111

		pfsm1.search_lower_root_mock (& Forest_A, & M);

		// Forest A should have <110>, <100>, and <000> and not have <111>
		//
		X.set_complete_subset (); // <111>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.set_empty_subset (); // <000>
		it = Forest_A.find (X.print_subset());
		if ((it == Forest_A.end ()) ||
				(it->second->adjacent->has_element (0))  // N[adjacent] = 011
					|| (! it->second->adjacent->has_element (1))
					|| (! it->second->adjacent->has_element (2)) )
			verification = false;

		X.set_complete_subset (); // <110>
		X.remove_element (2);
		it = Forest_A.find (X.print_subset());
		if ((it == Forest_A.end ()) || (! it->second->adjacent->is_empty ()) ) // N[adjacent] = 000
			verification = false;

		X.set_empty_subset ();
		X.add_element (0);   // <100>
		it = Forest_A.find (X.print_subset());
		if ((it == Forest_A.end ()) ||
				(it->second->adjacent->has_element (0))  // N[adjacent] = 001
					|| (it->second->adjacent->has_element (1))
					|| (! it->second->adjacent->has_element (2)) )
			verification = false;

		// delete the nodes in the collection and end the test.
		//
		for (it = Forest_A.begin (); it != Forest_A.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}
		Forest_A.clear ();

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->leftmost = 0;
		N->cost = c1.cost (N->vertex); // c(000) = 3
		Forest_A.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		M.set_empty_subset ();  // <010>
		M.add_element (1);

		pfsm1.search_lower_root_mock (& Forest_A, & M);

		// Forest A should have <000> and not have <010>
		//
		X.set_empty_subset (); // <010>
		X.add_element (1);
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.set_empty_subset (); // <000>
		it = Forest_A.find (X.print_subset());
		if ((it == Forest_A.end ()) ||
				(! it->second->adjacent->has_element (0))  // N[adjacent] = 101
					|| (it->second->adjacent->has_element (1))
					|| (! it->second->adjacent->has_element (2)) )
			verification = false;

		for (it = Forest_A.begin (); it != Forest_A.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}
		return verification;
	}


	bool it_should_prune_an_upper_tree ()
	{
		bool verification = true;
		ElementSet set1 ("set1", "input/PFSTestExplicitFuncA.xml");
		ElementSubset M ("", & set1), X ("", & set1);
		Explicit c1 (& set1);
		PosetForestSearch::Node * N;
		PosetForestSearchMock pfsm1;
		map<string, PosetForestSearch::Node *> Forest_B;
		map<string, PosetForestSearch::Node *>::iterator it;

		pfsm1.set_parameters (&c1, &set1, false);

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->set_complete_subset ();
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->leftmost = 0;
		N->cost = c1.cost (N->vertex); // c(111) = 3
		Forest_B.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->add_element (0);  // M = 100
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->adjacent->remove_element (0);
		N->leftmost = 1;
		N->cost = c1.cost (N->vertex); // c(100) = 2

		pfsm1.upper_forest_pruning_mock (& Forest_B, N);

		// Forest B should have <011> and not have <111>, <100>, <101> or <110>
		//
		X.set_complete_subset (); // <111>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.remove_element (1); // <101>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.remove_element (2); // <100>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.add_element (1); // <110>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.set_complete_subset (); // <011>
		X.remove_element (0);
		it = Forest_B.find (X.print_subset());
		if ((it == Forest_B.end ()) ||
				(it->second->adjacent->has_element (0))  // N[adjacent] = 011
					|| (! it->second->adjacent->has_element (1))
					|| (! it->second->adjacent->has_element (2)) )
			verification = false;

		// delete the nodes in the collection and end the test.
		//
		for (it = Forest_B.begin (); it != Forest_B.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}
		Forest_B.clear ();

		delete N->vertex;
		delete N->adjacent;
		delete N;

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->set_complete_subset ();
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->leftmost = 0;
		N->cost = c1.cost (N->vertex); // c(111) = 3
		Forest_B.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->add_element (2);   // <001>
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_empty_subset (); // N[adjacent] = 000
		N->leftmost = 3;

		pfsm1.upper_forest_pruning_mock (& Forest_B, N);

		// Forest B should have <111>, <011>, and <000> and not have <001>, <010>, <101>, <100>, and <110>
		//
		X.set_complete_subset (); // <101>
		X.remove_element (1);
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.remove_element (2); // <100>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.add_element (1); // <110>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.set_empty_subset ();
		X.add_element (1); // <010>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.set_empty_subset ();
		X.add_element (2); // <001>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.set_empty_subset (); // <000>
		it = Forest_B.find (X.print_subset());
		if ((it == Forest_B.end ()) ||
				(it->second->adjacent->has_element (0))  // N[adjacent] = 000
					|| (it->second->adjacent->has_element (1))
					|| (it->second->adjacent->has_element (2)) )
			verification = false;

		X.set_complete_subset (); // <111>
		it = Forest_B.find (X.print_subset());
		if ((it == Forest_B.end ()) ||
				(it->second->adjacent->has_element (0))  // N[adjacent] = 011
					|| (! it->second->adjacent->has_element (1))
					|| (! it->second->adjacent->has_element (2)) )
			verification = false;

		X.remove_element (0); // <011>
		it = Forest_B.find (X.print_subset());
		if ((it == Forest_B.end ()) ||
				(it->second->adjacent->has_element (0))  // N[adjacent] = 001
					|| (it->second->adjacent->has_element (1))
					|| (! it->second->adjacent->has_element (2)) )
			verification = false;

		// delete the nodes in the collection and end the test.
		//
		for (it = Forest_B.begin (); it != Forest_B.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}
		Forest_B.clear ();

		delete N->vertex;
		delete N->adjacent;
		delete N;

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->set_complete_subset ();
		N->vertex->remove_element (0);  // <011>
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->adjacent->remove_element (0);  // <011>
		N->leftmost = 1;
		N->cost = c1.cost (N->vertex); // c(011) = 2
		Forest_B.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->add_element (2); // N[adjacent] = 001
		N->leftmost = 2;

		pfsm1.upper_forest_pruning_mock ( & Forest_B, N);

		// Forest B should have <011> and not have <000>, <001>, <010>, and <111>
		//
		X.set_complete_subset (); // <111>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.set_empty_subset (); // <000>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.add_element (2); // <001>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.set_empty_subset ();
		X.add_element (1); // <010>
		it = Forest_B.find (X.print_subset());
		if (it != Forest_B.end ())
			verification = false;

		X.set_complete_subset ();
		X.remove_element (0); // <011>
		it = Forest_B.find (X.print_subset());
		if ((it == Forest_B.end ()) ||
				(it->second->adjacent->has_element (0))  // N[adjacent] = 001
					|| (it->second->adjacent->has_element (1))
					|| (! it->second->adjacent->has_element (2)) )
			verification = false;


		// delete the nodes in the collection and end the test.
		//
		for (it = Forest_B.begin (); it != Forest_B.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}
		Forest_B.clear ();

		delete N->vertex;
		delete N->adjacent;
		delete N;

		return verification;
	}


	bool it_should_prune_a_lower_tree ()
	{
		bool verification = true;
		ElementSet set1 ("set1", "input/PFSTestExplicitFuncA.xml");
		ElementSubset M ("", & set1), X ("", & set1);
		Explicit c1 (& set1);
		PosetForestSearch::Node * N;
		PosetForestSearchMock pfsm1;
		map<string, PosetForestSearch::Node *> Forest_A;
		map<string, PosetForestSearch::Node *>::iterator it;

		pfsm1.set_parameters (&c1, &set1, false);

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->leftmost = 0;
		N->cost = c1.cost (N->vertex); // c(000) = 3
		Forest_A.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->set_complete_subset ();
		N->vertex->remove_element (0);  // M = 011
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->adjacent->remove_element (0);
		N->leftmost = 1;
		N->cost = c1.cost (N->vertex); // c(011) = 2

		pfsm1.lower_forest_pruning_mock (& Forest_A, N);

		// Forest A should have <100> and not have <000>, <011>, <010> or <001>
		//
		X.set_empty_subset (); // <000>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.add_element (1); // <010>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.add_element (2); // <011>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.remove_element (1); // <001>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.set_empty_subset (); // <100>
		X.add_element (0);
		it = Forest_A.find (X.print_subset());
		if ((it == Forest_A.end ()) ||
				(it->second->adjacent->has_element (0))  // N[adjacent] = 011
					|| (! it->second->adjacent->has_element (1))
					|| (! it->second->adjacent->has_element (2)) )
			verification = false;

		// delete the nodes in the collection and end the test.
		//
		for (it = Forest_A.begin (); it != Forest_A.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}
		Forest_A.clear ();

		delete N->vertex;
		delete N->adjacent;
		delete N;

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->leftmost = 0;
		N->cost = c1.cost (N->vertex); // c(000) = 3
		Forest_A.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->add_element (0);
		N->vertex->add_element (1);   // <110>
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_empty_subset (); // N[adjacent] = 000
		N->leftmost = 3;

		pfsm1.lower_forest_pruning_mock (& Forest_A, N);

		// Forest A should have <111>, <100>, and <000> and not have <110>, <101>, <010>, <011>, and <001>
		//
		X.set_complete_subset (); // <101>
		X.remove_element (1);
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.set_complete_subset ();
		X.remove_element (0); // <011>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.set_complete_subset ();
		X.remove_element (2); // <110>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.set_empty_subset ();
		X.add_element (1); // <010>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.set_empty_subset ();
		X.add_element (2); // <001>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.set_empty_subset (); // <000>
		it = Forest_A.find (X.print_subset());
		if ((it == Forest_A.end ()) ||
				(it->second->adjacent->has_element (0))  // N[adjacent] = 011
					|| (! it->second->adjacent->has_element (1))
					|| (! it->second->adjacent->has_element (2)) )
			verification = false;

		X.set_complete_subset (); // <111>
		it = Forest_A.find (X.print_subset());
		if ((it == Forest_A.end ()) ||
				(it->second->adjacent->has_element (0))  // N[adjacent] = 000
					|| (it->second->adjacent->has_element (1))
					|| (it->second->adjacent->has_element (2)) )
			verification = false;

		X.set_empty_subset ();
		X.add_element (0); // <011>
		it = Forest_A.find (X.print_subset());
		if ((it == Forest_A.end ()) ||
				(it->second->adjacent->has_element (0))  // N[adjacent] = 001
					|| (it->second->adjacent->has_element (1))
					|| (! it->second->adjacent->has_element (2)) )
			verification = false;

		// delete the nodes in the collection and end the test.
		//
		for (it = Forest_A.begin (); it != Forest_A.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}
		Forest_A.clear ();

		delete N->vertex;
		delete N->adjacent;
		delete N;

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->add_element (0);  // <100>
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->set_complete_subset ();
		N->adjacent->remove_element (0);  // <011>
		N->leftmost = 1;
		N->cost = c1.cost (N->vertex); // c(100) = 2
		Forest_A.insert (pair<string, PosetForestSearch::Node *> (N->vertex->print_subset (), N));

		N = new PosetForestSearch::Node;
		N->vertex   = new ElementSubset ("", & set1);
		N->vertex->set_complete_subset ();
		N->adjacent = new ElementSubset ("", & set1);
		N->adjacent->add_element (2); // N[adjacent] = 001
		N->leftmost = 2;

		pfsm1.lower_forest_pruning_mock (& Forest_A, N);

		// Forest A should have <100> and not have <000>, <110>, <101>, and <111>
		//
		X.set_complete_subset (); // <111>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.set_empty_subset (); // <000>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.add_element (0);
		X.add_element (2); // <101>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.set_empty_subset ();
		X.add_element (0);
		X.add_element (1); // <110>
		it = Forest_A.find (X.print_subset());
		if (it != Forest_A.end ())
			verification = false;

		X.set_empty_subset ();
		X.add_element (0); // <100>
		it = Forest_A.find (X.print_subset());
		if ((it == Forest_A.end ()) ||
				(it->second->adjacent->has_element (0))  // N[adjacent] = 001
					|| (it->second->adjacent->has_element (1))
					|| (! it->second->adjacent->has_element (2)) )
			verification = false;

		// delete the nodes in the collection and end the test.
		//
		for (it = Forest_A.begin (); it != Forest_A.end (); it++)
		{
			delete it->second->vertex;
			delete it->second->adjacent;
			delete it->second;
		}
		Forest_A.clear ();

		delete N->vertex;
		delete N->adjacent;
		delete N;

		return verification;
	}


	bool a_poset_with_constant_cost_should_be_totally_exausted ()
	{
		ElementSet a_set1 ("S1", 3, 1);    // |S1| = 3
		ElementSet a_set2 ("S2", 10, 1);   // |S2| = 10
		ElementSet a_set3 ("S3", 1, 1);    // |S3| = 1
		MeanAbsSum c1 (&a_set1);
		MeanAbsSum c2 (&a_set2);
		MeanAbsSum c3 (&a_set3);
		PosetForestSearch pfs1;
		PosetForestSearch pfs2;
		PosetForestSearch pfs3;
		string list;
		pfs1.set_parameters (&c1, &a_set1, false);
		pfs1.get_minima_list (16);
		list = pfs1.print_list_of_minima ();
		pfs2.set_parameters (&c2, &a_set2, false);
		pfs2.get_minima_list (1024);
		pfs3.set_parameters (&c3, &a_set3, false);
		pfs3.get_minima_list (2);

		if (!((list.find ("<000>") != string::npos) &&
		      (list.find ("<001>") != string::npos) &&
		      (list.find ("<010>") != string::npos) &&
		      (list.find ("<011>") != string::npos) &&
		      (list.find ("<100>") != string::npos) &&
		      (list.find ("<101>") != string::npos) &&
		      (list.find ("<110>") != string::npos) &&
		      (list.find ("<111>") != string::npos) ) )
			return false;

		if (!(pfs1.number_of_minima () >= 8))
			return false;

		if (!(pfs2.number_of_minima() == 1024))
			return false;

		if (!(pfs3.number_of_minima() == 2) )
			return false;

		return true;
	}


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
		PosetForestSearch pfs1;
		PosetForestSearch pfs2;
		PosetForestSearch pfs3;
		PosetForestSearch pfs4;
		pfs1.set_parameters (&c1, &set1, false);
		pfs1.get_minima_list (1);
		if (pfs1.print_list_of_minima ().find ("<010>") == string::npos)
			return false;
		pfs2.set_parameters (&c2, &set2, false);
		pfs2.get_minima_list (10);
		if ((pfs2.print_list_of_minima ().find ("<000010000>") == string::npos) ||
		    (pfs2.print_list_of_minima ().find ("<100100000>") == string::npos) ||
			(pfs2.print_list_of_minima ().find ("<011000000>") == string::npos) )
			return false;
		pfs3.set_parameters (&c3, &set3, false);
		pfs3.get_minima_list (1);
		if (pfs3.print_list_of_minima ().find ("<0011100>") == string::npos)
			return false;
		pfs4.set_parameters (&c4, &set4, false);
		pfs4.get_minima_list (1);
		if (pfs4.print_list_of_minima ().find ("<101>") == string::npos)
			return false;
		return true;
	}


	// It was tested up to 2^32, but for large n it may take a LONG time... :-)
	//
	bool it_should_converge_for_large_hamming_sets ()
	{
		unsigned int i, n = 16; // 2^16, around 64K subsets
		string minimum = " <";
		ElementSet set1 ("set", n, 2);   // rand() % 2 results in a "hamming" instance.
		HammingDistance c1 (&set1);
		PosetForestSearch pfs;
		pfs.set_parameters (&c1, &set1, false);
		pfs.get_minima_list (1);
		for (i = 0; i < n; i++)
		{       // gets the minimum from the set1
			if( (set1.get_element (i))->get_element_value (0) == 0)
				minimum.append ("0");
			else
				minimum.append ("1");
		}
		minimum.append ("> ");
		if (pfs.print_list_of_minima ().find (minimum) == string::npos)
			return false;
		return true;
	}


	// It was tested up to 2^32, but for large n it may take a LONG time... :-)
	//
	bool it_should_converge_for_large_abs_sum_sets ()
	{
		unsigned int n = 16;
		ElementSet set1 ("set", n, 10000); // abs_sum instance.
		PosetForestSearch pfs;
		MeanAbsSum c1 (&set1);
		pfs.set_parameters (&c1, &set1, false);
		pfs.get_minima_list (1);
		return true;
	}


	bool it_should_store_all_the_visited_subsets ()
	{
		ElementSet set1 ("S1", 3, 1);    // |S1| = 3
		PosetForestSearch pfs;
		MeanAbsSum c1 (&set1);
		string list;
		pfs.set_parameters (&c1, &set1, true);
		pfs.get_minima_list (1);
		list = pfs.print_list_of_visited_subsets ();
		if ((list.find ("<000>") != string::npos) &&
		    (list.find ("<001>") != string::npos) &&
		    (list.find ("<010>") != string::npos) &&
		    (list.find ("<011>") != string::npos) &&
		    (list.find ("<100>") != string::npos) &&
		    (list.find ("<101>") != string::npos) &&
		    (list.find ("<110>") != string::npos) &&
		    (list.find ("<111>") != string::npos))
			return true;
		else
			return false;
	}

	// It may visit a node more than once (for instance, when the cost function if a constant)
	//
	bool it_should_give_the_number_of_the_visited_subsets ()
	{
		ElementSet set1 ("S1", 3, 1);    // |S1| = 3
		PosetForestSearch pfs;
		MeanAbsSum c1 (&set1);
		pfs.set_parameters (&c1, &set1, false);
		pfs.get_minima_list (1);
		if (pfs.print_number_of_visited_subsets () >= 8)
			return true;
		else
			return false;
	}

	// repeats the test k times (default: k = 10)
	//
	bool it_should_always_give_the_correct_answer ()
	{
		ElementSet set1 ("set", "input/UCSTest4ElementsFileA.xml");
		ElementSet set2 ("set", "input/UCSTest4ElementsFileB.xml");
		ElementSet set3 ("set", "input/UCSTest9ElementsFileB.xml");
		ElementSet set4 ("set", "input/UCSTest7ElementsFileB.xml");
		ElementSet set5 ("set", "input/UCSTest13ElementsFileA.xml");
		ElementSet set6 ("set", "input/UCSTest7ElementsFileC.xml");
		MeanAbsSum c1 (&set1);
		MeanAbsSum c2 (&set2);
		MeanAbsSum c3 (&set3);
		MeanAbsSum c4 (&set4);
		MeanAbsSum c5 (&set5);
		MeanAbsSum c6 (&set6);
		PosetForestSearch * pfs;
		int i, k = 10;
		string result;
		for (i = 1; i <= k; i++)
		{
			pfs = new PosetForestSearch ();
			pfs->set_parameters (&c1, &set1, false);
			pfs->get_minima_list (1);
			result.clear ();
			result = pfs->print_list_of_minima ();
			delete pfs;
			if (result.find ("<0110>") == string::npos)
				return false;
		}
		for (i = 1; i <= k; i++)
		{
			pfs = new PosetForestSearch ();
			pfs->set_parameters (&c2, &set2, false);
			pfs->get_minima_list (1);
			result.clear ();
			result = pfs->print_list_of_minima ();
			delete pfs;
			if (result.find ("<0011>") == string::npos)
				return false;
		}

		for (i = 1; i <= k; i++)
		{
			pfs = new PosetForestSearch ();
			pfs->set_parameters (&c3, &set3, false);
			pfs->get_minima_list (1);
			result.clear ();
			result = pfs->print_list_of_minima ();
			delete pfs;
			if (result.find ("<010001100>") == string::npos)
				return false;
		}
		for (i = 1; i <= k; i++)
		{
			pfs = new PosetForestSearch ();
			pfs->set_parameters (&c4, &set4, false);
			pfs->get_minima_list (1);
			result.clear ();
			result = pfs->print_list_of_minima ();
			delete pfs;
			if (result.find ("<0101101>") == string::npos)
				return false;
		}
		for (i = 1; i <= k; i++)
		{
			pfs = new PosetForestSearch ();
			pfs->set_parameters (&c5, &set5, false);
			pfs->get_minima_list (1);
			result.clear ();
			result = pfs->print_list_of_minima ();
			delete pfs;
			if (result.find ("<0000001000010>") == string::npos)
				return false;
		}
		for (i = 1; i <= k; i++)
		{
			pfs = new PosetForestSearch ();
			pfs->set_parameters (&c6, &set6, false);
			pfs->get_minima_list (1);
			result.clear ();
			result = pfs->print_list_of_minima ();
			delete pfs;
			if (result.find ("<0001101>") == string::npos)
				return false;
		}
		return true;
	}

} // end of namespace
