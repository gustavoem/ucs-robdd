#include "UCSROBDDToolBox4Test.h"

namespace UCSROBDDToolBox4Test {
	
	bool it_should_return_null_when_theres_no_unvisited_adjacent ()
	{
		ElementSet elm_set ("", 3, 100);
		ROBDD R (&elm_set);
		ElementSubset X ("", &elm_set);
		UCSROBDDToolBox4::Node * A, * Y;
		unsigned int i = 0;

		X.set_complete_subset ();
		A = UCSROBDDToolBox4::create_node (&X);
		UCSROBDDToolBox4::update_lower_restriction (&R, &X);
                
		Y = UCSROBDDToolBox4::select_an_unvisited_adjacent (&R, A, &i);
		bool ans = Y == NULL;
		if (Y != NULL)
			UCSROBDDToolBox4::delete_node (Y);
		UCSROBDDToolBox4::delete_node (A);
		return ans;
	}

	bool it_should_return_an_unvisited_adjacent ()
	{
		ElementSet elm_set ("", 2, 100);
		map<string, UCSROBDDToolBox4::Node *>  Graph;
		ROBDD R (&elm_set);
		ElementSubset X ("", &elm_set);
		ElementSubset X2 ("", &elm_set);
		UCSROBDDToolBox4::Node * A, * Y;
		unsigned int i = 0;

		X.add_element (0);
		X2.add_element (1);
		A = UCSROBDDToolBox4::create_node (&X2);
		Graph.insert (pair<string, UCSROBDDToolBox4::Node *> (A->vertex->print_subset (), A));
		UCSROBDDToolBox4::update_upper_restriction (&R, &X);
		Y = UCSROBDDToolBox4::select_an_unvisited_adjacent (&R, A, &i);
		// it should return the subset <00>
		if (Y->vertex->print_subset ().find ("1") != string::npos)
			return false;

		UCSROBDDToolBox4::delete_node (A);
		UCSROBDDToolBox4::delete_node (Y);
		return true;
	}


} // end of namespace

