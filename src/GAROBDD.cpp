#include "GAROBDD.h"

GAROBDD::GAROBDD (ElementSet * set, list <pair <bool, ElementSubset *> > * l, 
	unsigned int * ord) : ROBDD (set, ord)
{

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
	delete log_of_intervals;
}