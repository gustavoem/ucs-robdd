#include "ROBDDTest.h"

namespace ROBDDTest {

	bool a_new_robdd_has_only_a_terminal_node ()
	{
		ElementSet * elm_set = new ElementSet ("", 3, 100);
		ROBDD * robdd = new ROBDD (elm_set);
		Vertex * root = robdd->get_root ();
		bool answ = true;
		answ = root->get_var () == NULL && root->get_hi () == NULL && root->get_lo () == NULL;
		return answ;
	}

} // end of namespace

