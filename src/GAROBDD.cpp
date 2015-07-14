#include "GAROBDD.h"

GAROBDD::GAROBDD (ElementSet * set, list <pair <bool, ElementSubset *> > * l, 
	unsigned int * ord) : ROBDD (set, ord)
{
	cout << "\nordem que chegou na ROBDD: ";
	for (unsigned int i = 0; i < set->get_set_cardinality (); i++)
		cout << ord[i] << " ";
	for (list <pair <bool, ElementSubset *> >::iterator it = l->begin (); 
		it != l->end (); it++)
		add_interval (it->second, it->first);
	delete log_of_intervals;

	log_of_intervals = l;
}

GAROBDD::~GAROBDD ()
{
	delete_subtree (&root, &cardinality);
	if (ordering != NULL)
		free (ordering);

	for (list <pair <bool, ElementSubset *> >::iterator it = log_of_intervals->begin (); 
		it != log_of_intervals->end (); it++)
		delete it->second;
	delete log_of_intervals;
}