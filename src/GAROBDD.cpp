#include "GAROBDD.h"

GAROBDD::GAROBDD (ElementSet * set, list <pair <bool, ElementSubset *> > * l, 
	unsigned int * ord) : ROBDD (set, ord)
{
	for (list <pair <bool, ElementSubset *> >::iterator it = l->begin (); 
		it != l->end (); it++)
	{
		this->add_interval (it->second, it->first);
	}
	
	for (list <pair <bool, ElementSubset *> >::iterator it = log_of_intervals->begin (); 
		it != log_of_intervals->end (); it++)
		delete it->second;
	
	delete log_of_intervals;
	log_of_intervals = NULL;
	log_of_intervals = l;
}


GAROBDD::~GAROBDD ()
{
	if (ordering != NULL)
		free (ordering);
	ordering = NULL;
	log_of_intervals = NULL;
}


list< pair<bool, ElementSubset *> > * GAROBDD::get_log ()
{
	return log_of_intervals;
}