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
		OrderingNode solution (&elm_set, &l);
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
		ElementSet elm_set ("", 2, 100);
		ROBDD robdd (&elm_set);
		ElementSubset subset ("", &elm_set);
		
		subset.add_element (0);
		robdd.add_interval (&subset, false);
		subset.add_element (1);
		robdd.add_interval (&subset, true);

 		list <pair <bool, ElementSubset *> > l = robdd.get_log ();
		ElementSubset emp_sub ("", &elm_set);
		ElementSubset a_sub ("", &elm_set);
		a_sub.add_element (0);
		ElementSubset b_sub ("", &elm_set);
		b_sub.add_element (1);
		ElementSubset ab_sub ("", &elm_set);
		ab_sub.copy (&subset);

		OrderingNode solution (&elm_set, &l);
		GAROBDD * r = solution.get_robdd ();

		if (r->contains (&b_sub)    ||
			!r->contains (&a_sub)   ||
			!r->contains (&emp_sub) || 
			!r->contains (&ab_sub))
			return false;
		return true;
	}

	bool it_should_recombine_to_other_permutations ()
	{
		unsigned int setsize = 5;
		unsigned int * occour = (unsigned int *) malloc
		 (setsize * sizeof (unsigned int));
		bool answ = true;
		ElementSet elm_set ("", setsize, 100);
		list <pair <bool, ElementSubset *> > l;
		OrderingNode solution (&elm_set, &l);
		unsigned int * v =
			(unsigned int *) malloc (setsize * sizeof (unsigned int));
		for (unsigned int i = 0; i < setsize; i++)
		{
			v[i] = i;
			occour[i] = 0;
		}

		solution.recombine_to (v);
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
		free (v);
		return answ;
	}

	bool it_should_perform_a_mut ()
	{
		unsigned int setsize = 5;
		bool answ = true;
		ElementSet elm_set ("", setsize, 100);
		list <pair <bool, ElementSubset *> > l;
		OrderingNode solution (&elm_set, &l);
		unsigned int * perm =
			(unsigned int *) malloc (setsize * sizeof (unsigned int));
		for (unsigned int i = 0; i < setsize; i++)
			perm[i] = solution.get_ordering ()[i];

		solution.mut ();
		unsigned int i = 0;
		while (i < setsize && perm[i] == solution.get_ordering ()[i])
			i++;	
		unsigned int j = i + 1;
		while (j < setsize && perm[j] == solution.get_ordering ()[j])
			j++;
		if (i < setsize) {
			if (!(j < setsize))
				answ = false;
			else
				answ = perm[i] == solution.get_ordering ()[j] && \
					   perm[j] == solution.get_ordering ()[i];
		}

		free (perm);
		return answ;
	}


	bool it_should_perform_a_neighbour_mut ()
	{
		unsigned int setsize = 5;
		bool answ = true;
		ElementSet elm_set ("", setsize, 100);
		list <pair <bool, ElementSubset *> > l;
		OrderingNode solution (&elm_set, &l);
		unsigned int * perm =
			(unsigned int *) malloc (setsize * sizeof (unsigned int));
		for (unsigned int i = 0; i < setsize; i++)
			perm[i] = solution.get_ordering ()[i];

		
		solution.neighbour_mut ();
		unsigned int i = 0;
		while (i < setsize - 1 && perm[i] == solution.get_ordering ()[i])
			i++;
		unsigned int j = i + 1;
		if (i < setsize) {
			if (!(j < setsize))
				answ = false;
			else
			{
				answ = (perm[i] == solution.get_ordering ()[j]) && (perm[j] == solution.get_ordering ()[i]);
			}
		}

		free (perm);
		return answ;
	}

} // end of namespace

