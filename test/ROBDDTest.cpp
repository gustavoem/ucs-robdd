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

	bool the_union_of_a_new_robdd_with_itself_should_be_itself ()
	{
		ElementSet * elm_set = new ElementSet ("", 3, 100);
		ROBDD * robdd = new ROBDD (elm_set);
		Vertex * root = robdd->get_root ();
		robdd->union_to (root);
		root = robdd->get_root ();
		bool answ = (root->get_child (true) == NULL) && (root->get_child (false) == NULL) \
					&& root->get_value () == 0;
		delete elm_set;
		delete robdd;
		return answ;
	}

	bool the_union_of_all_subsets_must_be_the_function_1 ()
	{
		ElementSet * elm_set = new ElementSet ("", 3, 3);
		ElementSubset * subset = new ElementSubset ("", elm_set);
		subset->add_element (0);
		subset->add_element (1);
		subset->add_element (2);
		ROBDD * robdd = new ROBDD (elm_set);
		robdd->add_lower_interval (subset);
		Vertex * root = robdd->get_root ();
		bool answ = (root->get_child (true) == NULL) && (root->get_child (false) == NULL) \
					&& root->get_value () == 1;
		delete robdd;
		delete elm_set;
		delete subset;
		return answ;
	}

	bool a_new_robdd_contais_no_subset ()
	{
		ElementSet * elm_set = new ElementSet ("", 3, 100);
		ROBDD * robdd = new ROBDD (elm_set);
		ElementSubset * subset1 = new ElementSubset ("", elm_set);
		subset1->add_element (0);
		ElementSubset * subset2 = new ElementSubset ("", elm_set);
		subset2->add_element (1);
		ElementSubset * subset3 = new ElementSubset ("", elm_set);
		subset3->add_element (2);
		bool answ = !robdd->contains (subset1) && !robdd->contains (subset2) && \
					!robdd->contains (subset3);
		delete elm_set;
		delete robdd;
		delete subset1;
		delete subset2;
		delete subset3;
		return answ;
	}

	bool an_added_subset_must_be_contained ()
	{
		ElementSet * elm_set = new ElementSet ("", 3, 3);
		ElementSubset * subset = new ElementSubset ("", elm_set);
		subset->add_element (0);
		subset->add_element (1);
		subset->add_element (2);
		ROBDD * robdd = new ROBDD (elm_set, subset);
		bool answ = robdd->contains (subset);
		delete elm_set;
		delete subset;
		delete robdd;
		return answ;
	}

	bool the_function_one_covers_all_subsets ()
	{
		ElementSet elm_set ("", 2, 2);	
		ElementSubset subset ("", &elm_set);
		subset.add_element (0);
		subset.add_element (1);
		ROBDD robdd (&elm_set);
		robdd.add_lower_interval (&subset);
		ElementSubset sub0 ("", &elm_set);
		ElementSubset sub1 ("", &elm_set);
		sub1.add_element (0);
		ElementSubset sub2 ("", &elm_set);
		sub2.add_element (1);
		ElementSubset sub3 ("", &elm_set);
		sub3.add_element (0);
		sub3.add_element (1);
		bool answ = robdd.contains (&sub0) && robdd.contains (&sub1) && \
					robdd.contains (&sub2) && robdd.contains (&sub3);
		return answ;
	}

	bool the_function_one_have_no_subset_evaluated_zero ()
	{
		ElementSet elm_set ("", 2, 2);	
		ElementSubset subset ("", &elm_set);
		subset.add_element (0);
		subset.add_element (1);
		ROBDD robdd (&elm_set);
		robdd.add_lower_interval (&subset);
		ElementSubset * elm = robdd.get_random_zero_evaluated_element ();
		return elm == NULL;
	}

	bool its_possible_to_get_a_random_subset_evaluated_zero ()
	{

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

