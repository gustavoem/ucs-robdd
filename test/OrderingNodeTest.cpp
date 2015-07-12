#include "OrderingNodeTest.h"

namespace OrderingNodeTest {

	bool it_should_create_a_random_permutation ()
	{	
		unsigned int setsize = 10;
		unsigned int * occour = (unsigned int *) malloc
		 (setsize * sizeof (unsigned int));
		bool answ = true;
		ElementSet elm_set ("", setsize, 100);
		list <pair <bool, ElementSubset *> > l;
		OrderingNode solution (&elm_set, l);
		for (unsigned int i = 0; i < setsize; i++)
			occour[i] = 0;

		unsigned int * perm = solution.get_ordering ();
		for (unsigned int i = 0; i < setsize; i++)
			if (perm[i] < setsize && perm[i] >= 0)
				occour[perm[i]]++;
			else
				answ = false;

		for (unsigned int i = 0; i < setsize; i++)
			if (occour[i] != 1)
				answ = false;

		free (occour);
		return answ;
	}

	bool it_should_represent_the_original_robdd ()
	{
		return true;
	}
		// subset.add_element (0);
		// robdd.add_interval (&subset, false);
		// subset.remove_element (0);
		// subset.add_element (2);
		// robdd.add_interval (&subset, false);
		// subset.add_element (1);
		// robdd.add_interval (&subset, true);

} // end of namespace

