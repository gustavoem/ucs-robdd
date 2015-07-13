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
		cout << "\n";
		robdd.print ();

 		list <pair <bool, ElementSubset *> > l = robdd.get_log ();
 		cout << "\noriginal:\n";
		for (list <pair <bool, ElementSubset *> >::iterator it = l.begin (); 
			it != l.end (); it++)
			cout << it->first << " " << it->second->print_subset () << endl;

		ElementSubset emp_sub ("", &elm_set);
		ElementSubset a_sub ("", &elm_set);
		a_sub.add_element (0);
		ElementSubset b_sub ("", &elm_set);
		b_sub.add_element (1);
		ElementSubset ab_sub = subset;

		OrderingNode solution (&elm_set, &l);
		unsigned int * perm = solution.get_ordering ();
		cout << "\npermutação: ";
		for (unsigned int i = 0; i < elm_set.get_set_cardinality (); i++)
			cout << perm[i] << " ";
		cout << endl;
		GAROBDD * r = solution.get_robdd ();

		r->print ();
		if (r->contains (&b_sub)    ||
			!r->contains (&a_sub)   ||
			!r->contains (&emp_sub) || 
			!r->contains (&ab_sub))
			return false;
		return true;
	}

} // end of namespace

