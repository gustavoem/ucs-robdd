#include "GAROBDD.h"

GAROBDD::GAROBDD (ElementSet * set, list <pair <bool, ElementSubset *> > * l, 
	unsigned int * ord) : ROBDD (set, ord)
{
	cout << "(GARO) Ordem que chegou na GAROBDD: ";
	for (unsigned int i = 0; i < set->get_set_cardinality (); i++)
		cout << ord[i] << " ";
	cout << endl;
	
	cout << "(GARO) Meu endereço: " << this << endl;

	for (list <pair <bool, ElementSubset *> >::iterator it = l->begin (); 
		it != l->end (); it++)
		this->add_interval (it->second, it->first);
	
	while (!log_of_intervals->empty())
		log_of_intervals->pop_back ();
	
	delete log_of_intervals;
	log_of_intervals = NULL;
	log_of_intervals = l;
}

GAROBDD::~GAROBDD ()
{
	cout << "\nDestrutor da GAROBDD\n";
	delete_subtree (&root, &cardinality);
	if (ordering != NULL)
		free (ordering);
	ordering = NULL;

	for (list <pair <bool, ElementSubset *> >::iterator it = log_of_intervals->begin (); 
		it != log_of_intervals->end (); it++)
		delete it->second;
	delete log_of_intervals;
	log_of_intervals = NULL;
}