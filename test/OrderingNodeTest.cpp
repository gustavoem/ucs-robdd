#include "OrderingNodeTest.h"

namespace OrderingNodeTest {

	bool it_should_create_a_random_permutation ()
	{	
		unsigned int setsize = 3;
		ElementSet elm_set ("", setsize, 100);
		ROBDD robdd (&elm_set);
		ElementSubset subset ("", &elm_set);
		list <pair <bool, ElementSubset *> > l;
		OrderingNode solution (&elm_set, l);
		// subset.add_element (0);
		// robdd.add_interval (&subset, false);
		// subset.remove_element (0);
		// subset.add_element (2);
		// robdd.add_interval (&subset, false);
		// subset.add_element (1);
		// robdd.add_interval (&subset, true);

		return true;
	}

} // end of namespace

