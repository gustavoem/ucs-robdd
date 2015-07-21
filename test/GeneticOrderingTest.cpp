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
		cout << "\ncardinality: " << robdd.get_cardinality () << endl;
		GeneticOrdering gen_ord (&robdd, 10, setsize);
		return true;
	}

	bool it_should_give_a_better_ordering_robdd ()
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
		GeneticOrdering gen_ord (&robdd, 10, setsize);
		ROBDD * robdd2 = gen_ord.reorder ();
		robdd2->print ();
		return true;
	}

} // end of namespace

