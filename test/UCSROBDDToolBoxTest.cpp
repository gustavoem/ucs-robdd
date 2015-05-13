#include "UCSROBDDToolBoxTest.h"

namespace UCSROBDDToolBoxTest {
	
	bool it_should_return_null_when_theres_no_unvisited_adjacent ()
	{
		ElementSet elm_set ("", 3, 100);
		map<string, UCSROBDDToolBox::Node *>  Graph;
		ROBDD RU (&elm_set);
		ROBDD RL (&elm_set);
		ElementSubset X ("", &elm_set);
		UCSROBDDToolBox::Node * A, * Y;
		unsigned int i;

		X.set_complete_subset ();
		A = UCSROBDDToolBox::create_node (&X);
		Graph.insert (pair<string, UCSROBDDToolBox::Node *> (A->vertex->print_subset (), A));
		UCSROBDDToolBox::update_lower_restriction (&RU, &X);
		Y = UCSROBDDToolBox::select_an_unvisited_adjacent (&Graph, &RL, &RU, A, &i);
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
		ROBDD RU (&elm_set);
                ROBDD RL (&elm_set);
		ElementSubset X ("", &elm_set);
		ElementSubset X2 ("", &elm_set);
		UCSROBDDToolBox::Node * A, * Y;
		unsigned int i;

		X.add_element (0);
		X2.add_element (1);
		A = UCSROBDDToolBox::create_node (&X2);
		Graph.insert (pair<string, UCSROBDDToolBox::Node *> (A->vertex->print_subset (), A));
		UCSROBDDToolBox::update_upper_restriction (&RU, &X);
		Y = UCSROBDDToolBox::select_an_unvisited_adjacent (&Graph, &RL, &RU, A, &i);
		// it should return the subset <00>
		if (Y->vertex->print_subset ().find ("1") != string::npos)
			return false;

		UCSROBDDToolBox::delete_node (A);
		UCSROBDDToolBox::delete_node (Y);
		return true;
	}


} // end of namespace

