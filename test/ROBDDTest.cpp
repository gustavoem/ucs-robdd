#include "ROBDDTest.h"

namespace ROBDDTest {

	bool a_new_robdd_has_only_a_terminal_node ()
	{
		ElementSet * elm_set = new ElementSet ("", 3, 100);
		ROBDD * robdd = new ROBDD (elm_set);
		Vertex * root = robdd->get_root ();
		bool answ = true;
		answ = root->get_var () == NULL && root->get_child (true) == NULL && root->get_child (false) == NULL;
		delete elm_set;
		delete robdd;
		return answ;
	}

	/*not a test*/
	bool print_r () 
	{
		ElementSet * elm_set = new ElementSet ("", 3, 100);
		
		/*ROBDD * robdd = new ROBDD (elm_set);
		robdd->print ();
		cout.flush();
		robdd->reduce ();
		cout << "depois de reduzir" << endl;
		robdd->print ();
		cout << " fim da robdd 1 " << endl  << endl;
		delete robdd;*/
		
		ElementSubset * subset = new ElementSubset("", elm_set);
		subset->add_element(0);
		subset->add_element(1);
		subset->add_element(2);
		ROBDD * robdd2 = new ROBDD (elm_set, subset);
		robdd2->print ();
		robdd2->reduce ();
		cout << "depois de reduzir" << endl;
		robdd2->print ();
		cout << " fim da robdd 2. |G| = " << robdd2->cardinality << endl << endl;
		delete subset;

		/*ElementSet * elm_set2 = new ElementSet ("", 2, 100);
		ROBDD * robdd3 = new ROBDD (elm_set2, 1);
		cout << "robdd 3" << endl;
		robdd3->print ();
		robdd3->reduce ();
		cout << "depois de reduzir" << endl;
		robdd3->print ();
		cout << " fim da robdd 3. |G| = " << robdd3->cardinality << endl << endl;
		delete robdd3;
		delete elm_set2;*/

		/*agora para testar a union*/
		/*ElementSubset * subset1 = new ElementSubset("", elm_set);
		subset1->add_element(0);
		subset1->add_element(2);
		ROBDD * robdd4 = new ROBDD (elm_set, subset1);
		cout << "robdd4" << endl;
		robdd4->print ();*/
		ElementSubset * subset2 = new ElementSubset("", elm_set);
		subset2->add_element (1);
		ROBDD * robdd5 = new ROBDD (elm_set, subset2);
		cout << "robdd5" << endl;
		robdd5->print ();
		robdd5->union_to (robdd2->get_root ());
		cout << "juntas:" << endl;
		robdd5->print ();
		//delete robdd4;
		delete robdd2;
		delete robdd5;
		//delete subset1;
		delete subset2;



		delete elm_set;
		return true;
	}

} // end of namespace

