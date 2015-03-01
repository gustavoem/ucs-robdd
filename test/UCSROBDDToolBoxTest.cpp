#include "UCSROBDDToolBoxTest.h"

namespace UCSROBDDToolBoxTest {

	bool theres_no_minial_element_when_all_subsets_are_restricted ()
	{
		ElementSet elm_set ("", 2, 2);
		ElementSubset subset ("", &elm_set);
		subset.add_element (0);
		subset.add_element (1);
		ROBDD R (&elm_set);
		UCSROBDDToolBox::update_lower_restriction (&R, &subset);
		ElementSubset * min_subset = UCSROBDDToolBox::get_minimal_subset (&R, &elm_set);
		bool ans = min_subset == NULL;
		return ans;
	}

	bool theres_no_maximal_element_when_all_subsets_are_restricted ()
	{
		ElementSet elm_set ("", 2, 2);
		ElementSubset subset ("", &elm_set);
		ROBDD R (&elm_set);
		UCSROBDDToolBox::update_upper_restriction (&R, &subset);
		ElementSubset * max_subset = UCSROBDDToolBox::get_maximal_subset (&R, &elm_set);
		bool ans = max_subset == NULL;
		delete max_subset;
		return ans;
	}

	bool when_empty_set_is_not_restricted_its_the_minimal_subset ()
	{
		ElementSet elm_set ("", 2, 2);
		ROBDD R (&elm_set);
		ElementSubset * min_subset = UCSROBDDToolBox::get_minimal_subset (&R, &elm_set);
		bool ans = min_subset->get_subset_cardinality () == 0;
		delete min_subset;
		return ans;
	}

	bool it_should_return_null_when_theres_no_unvisited_adjacent ()
	{
		ElementSet elm_set ("", 3, 100);
		map<string, UCSROBDDToolBox::Node *>  Graph;
		ROBDD R (&elm_set);
		ElementSubset X ("", &elm_set);
		UCSROBDDToolBox::Node * A, * Y;
		unsigned int i;

		X.set_complete_subset ();
		A = UCSROBDDToolBox::create_node (&X);
		Graph.insert (pair<string, UCSROBDDToolBox::Node *> (A->vertex->print_subset (), A));
		UCSROBDDToolBox::update_lower_restriction (&R, &X);
		Y = UCSROBDDToolBox::select_an_unvisited_adjacent (&Graph, &R, A, &i);
		bool ans = Y == NULL;
		if (Y != NULL)
			UCSROBDDToolBox::delete_node (Y);
		UCSROBDDToolBox::delete_node (A);
		return ans;
	}

	bool it_should_return_an_unvisited_adjacent ()
	{
		ElementSet elm_set ("", 2, 100);
		map<string, UCSROBDDToolBox::Node *>  Graph;
		ROBDD R (&elm_set);
		ElementSubset X ("", &elm_set);
		ElementSubset X2 ("", &elm_set);
		UCSROBDDToolBox::Node * A, * Y;
		unsigned int i;

		X.add_element (0);
		X2.add_element (1);
		A = UCSROBDDToolBox::create_node (&X2);
		Graph.insert (pair<string, UCSROBDDToolBox::Node *> (A->vertex->print_subset (), A));
		UCSROBDDToolBox::update_upper_restriction (&R, &X);
		Y = UCSROBDDToolBox::select_an_unvisited_adjacent (&Graph, &R, A, &i);
		// it should return the subset <00>
		if (Y->vertex->print_subset ().find ("1") != string::npos)
			return false;

		UCSROBDDToolBox::delete_node (A);
		UCSROBDDToolBox::delete_node (Y);
		return true;
	}


} // end of namespace

