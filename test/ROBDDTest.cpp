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
		robdd->add_interval (subset, false);
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

	bool an_added_subset_must_be_covered ()
	{
		ElementSet * elm_set = new ElementSet ("", 3, 3);
		ElementSubset * subset = new ElementSubset ("", elm_set);
		subset->add_element (0);
		subset->add_element (1);
		subset->add_element (2);
		ROBDD * robdd = new ROBDD (elm_set, subset);
		bool answ = robdd->contains (subset);
		delete robdd;
		delete subset;
		delete elm_set;
		return answ;
	}

	bool the_function_one_covers_all_subsets ()
	{
		ElementSet elm_set ("", 2, 2);	
		ElementSubset subset ("", &elm_set);
		subset.add_element (0);
		subset.add_element (1);
		ROBDD robdd (&elm_set);
		robdd.add_interval (&subset, false);
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
		robdd.add_interval (&subset, false);
		ElementSubset * elm = robdd.get_random_zero_evaluated_element ();
		return elm == NULL;
	}


	bool its_possible_to_get_a_random_subset_evaluated_zero ()
	{
		ElementSet elm_set ("", 2, 2);	
		ROBDD robdd (&elm_set);
		ElementSubset subset1 ("", &elm_set);
		ElementSubset subset2 ("", &elm_set);
		subset1.add_element (0);
		subset2.add_element (1);
		robdd.add_interval (&subset1, true);
		robdd.add_interval (&subset2, true);
		ElementSubset expected_subset ("", &elm_set);
		ElementSubset * answ_subset = robdd.get_random_zero_evaluated_element ();
		bool answ = answ_subset->is_equal(&expected_subset);
		delete answ_subset;
		return answ;
	}

	bool the_robdd_maintains_a_log_of_restrictions ()
	{
		ElementSet elm_set ("", 2, 2);	
		ROBDD robdd (&elm_set);
		ElementSubset subset1 ("", &elm_set);
		ElementSubset subset2 ("", &elm_set);
		subset1.add_element (0);
		subset2.add_element (1);
		robdd.add_interval (&subset1, true);
		robdd.add_interval (&subset2, false);
		list < pair<bool, ElementSubset *> > l (robdd.get_log ());
		
		pair <bool, ElementSubset *> first_pair = l.back ();
		if (! l.empty ())
			l.pop_back ();
		pair <bool, ElementSubset *> second_pair = l.back ();
		if (first_pair.second->print_subset () != subset1.print_subset ()  ||
			first_pair.first != true    ||
			second_pair.second->print_subset () != subset2.print_subset () ||
			second_pair.first != false)
			return false;
		else
			return true;
	}


	bool it_should_represent_the_same_space_after_reordering ()
	{
		bool answ;
		ElementSet elm_set ("", 3, 2);	
		ROBDD robdd (&elm_set);
		ElementSubset subset1 ("", &elm_set);
		ElementSubset subset2 ("", &elm_set);
		subset1.add_element (0);
		subset2.add_element (1);
		robdd.add_interval (&subset1, false);
		GeneticOrdering genord (&robdd);
		list <pair <bool, ElementSubset *> > robdd_log = robdd.get_log ();
		unsigned int * perm = genord.reorder ();
		robdd.change_ordering (perm);
		free (perm);
		
		robdd.add_interval (&subset2, true);

		ElementSubset empty_subset ("", &elm_set);
		ElementSubset a_subset ("", &elm_set);
		a_subset.add_element (0);
		ElementSubset b_subset ("", &elm_set);
		b_subset.add_element (1);
		ElementSubset c_subset ("", &elm_set);
		c_subset.add_element (2);
		ElementSubset ab_subset ("", &elm_set);
		ab_subset.add_element (0);
		ab_subset.add_element (1);
		ElementSubset ac_subset ("", &elm_set);
		ac_subset.add_element (0);
		ac_subset.add_element (2);
		ElementSubset bc_subset ("", &elm_set);
		bc_subset.add_element (1);
		bc_subset.add_element (2);
		ElementSubset abc_subset ("", &elm_set);
		abc_subset.add_element (0);
		abc_subset.add_element (1);
		abc_subset.add_element (2);

		if (robdd.contains (&empty_subset) &&
			robdd.contains (&a_subset)     &&
			robdd.contains (&b_subset)     &&
			!robdd.contains (&c_subset)    &&
			robdd.contains (&ab_subset)    &&
			robdd.contains (&bc_subset)    &&
			!robdd.contains (&ac_subset)   &&
			robdd.contains (&abc_subset)
			)
			answ = true;
		else
			answ = false;
		return answ;
	}


	/*not a test*/
	bool print_r () 
	{
		ElementSet * elm_set = new ElementSet ("", 3, 100);
		
		ROBDD * robdd = new ROBDD (elm_set);
		robdd->print ();
		cout.flush();
		robdd->reduce ();
		cout << "depois de reduzir" << endl;
		robdd->print ();
		cout << " fim da robdd 1 " << endl  << endl;
		delete robdd;
		
		ElementSubset * subset = new ElementSubset("", elm_set);
		subset->add_element(0);
		subset->add_element(1);
		subset->add_element(2);
		ROBDD * robdd2 = new ROBDD (elm_set, subset);
		robdd2->print ();
		robdd2->reduce ();
		cout << "depois de reduzir" << endl;
		robdd2->print ();
		cout << " fim da robdd 2. |G| = " << endl << endl;
		delete subset;

		// ElementSet * elm_set2 = new ElementSet ("", 2, 100);
		// ROBDD * robdd3 = new ROBDD (elm_set2, 1);
		// cout << "robdd 3" << endl;
		// robdd3->print ();
		// robdd3->reduce ();
		// cout << "depois de reduzir" << endl;
		// robdd3->print ();
		// cout << " fim da robdd 3. |G| = "  << endl << endl;
		// delete robdd3;
		// delete elm_set2;

		/*agora para testar a union */
		ElementSubset * subset1 = new ElementSubset("", elm_set);
		subset1->add_element(0);
		subset1->add_element(2);
		ROBDD * robdd4 = new ROBDD (elm_set, subset1);
		cout << "robdd4" << endl;
		robdd4->print ();
		ElementSubset * subset2 = new ElementSubset("", elm_set);
		subset2->add_element (1);
		ROBDD * robdd5 = new ROBDD (elm_set, subset2);
		cout << "robdd5" << endl;
		robdd5->print ();
		robdd5->union_to (robdd4->get_root ());
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

