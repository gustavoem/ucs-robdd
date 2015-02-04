#include "ROBDDTest.h"

namespace ROBDDTest {

	bool a_new_robdd_has_only_a_terminal_node ()
	{
		ElementSet * elm_set = new ElementSet ("", 3, 100);
		ROBDD * robdd = new ROBDD (elm_set);
		Vertex * root = robdd->get_root ();
		bool answ = true;
		answ = root->get_var () == NULL && root->get_child (true) == NULL && root->get_child (false) == NULL;
		return answ;
	}

	/*not a test*/
	bool print_r () 
	{
		ElementSet * elm_set = new ElementSet ("", 3, 100);
		ROBDD * robdd = new ROBDD (elm_set);
		robdd->print ();
		cout << " fim da robdd 1 " << endl  << endl;
		ElementSubset * subset = new ElementSubset("", elm_set);
		subset->add_element(0);
		subset->add_element(1);
		subset->add_element(2);
		ROBDD * robdd2 = new ROBDD (elm_set, subset);
		robdd2->print ();
		cout << " fim da robdd 2. |G| = " << robdd2->cardinality << endl << endl;
		robdd2->reduce ();
		return true;
	}

} // end of namespace

