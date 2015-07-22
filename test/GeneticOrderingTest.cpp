#include "GeneticOrderingTest.h"

namespace GeneticOrderingTest {

	bool it_should_create_an_initial_population ()
	{	
		unsigned int setsize = 5;
		ElementSet elm_set ("", setsize, 2);
		ROBDD robdd (&elm_set);
		ElementSubset subset ("", &elm_set);
		subset.add_element (0);
		robdd.add_interval (&subset, false);
		subset.add_element (2);
		robdd.add_interval (&subset, true);
		subset.add_element (5);
		robdd.add_interval (&subset, false);
		GeneticOrdering gen_ord (&robdd);
		return true;
	}

	bool it_should_give_a_better_ordering_robdd ()
	{
		bool answ;
		unsigned int setsize = 5;
		ElementSet elm_set ("", setsize, 2);
		ROBDD robdd (&elm_set);
		ElementSubset subset ("", &elm_set);
		subset.add_element (0);
		robdd.add_interval (&subset, false);
		subset.add_element (2);
		robdd.add_interval (&subset, true);
		subset.add_element (5);
		robdd.add_interval (&subset, false);
		GeneticOrdering gen_ord (&robdd);
		
		unsigned int old_size = robdd.get_cardinality ();
		unsigned int * new_order = gen_ord.reorder ();
		robdd.change_ordering (new_order);
		answ = old_size >= robdd.get_cardinality ();
		free (new_order);
		return answ;
	}

} // end of namespace

