#include "ROBDD.h"


ROBDD::ROBDD (ElementSet * set)
{
	elm_set = set;
	root = new Vertex (false);
}


ROBDD::ROBDD (ElementSet * set, ElementSubset * subset)
{
	unsigned int set_card = set->get_set_cardinality ();
	elm_set = set;
	Vertex * zero = new Vertex (false);
	Vertex * one = new Vertex (true);
	root = new Vertex (elm_set->get_element (0));	
	build (root, 0, set_card, subset, zero, one);
}


void ROBDD::build (Vertex * v, unsigned int elm_index, unsigned int set_card, ElementSubset * subset, Vertex * zero, Vertex * one)
{
	bool zeroside;
	zeroside = !subset->has_element (elm_index);
	v->set_child (zero, zeroside);
	
	if (elm_index == set_card - 1) 
	{
		v->set_child (one, !zeroside);
		return;
	}

	Vertex * next_vertice = new Vertex (elm_set->get_element (elm_index + 1));
	v->set_child (next_vertice, !zeroside);
	build (next_vertice, elm_index + 1, set_card, subset, zero, one);	
}


void ROBDD::identify (Vertex * v, unsigned int * last_id)
{	
	if (v == NULL)
		return;
	v->set_id (* last_id);
	(* last_id)++;
	identify (v->get_lo (), last_id);
	identify (v->get_hi (), last_id);
}


ROBDD::~ROBDD ()
{
	return;
}


Vertex * ROBDD::get_root()
{
	return root;
}


void ROBDD::print ()
{
	print (root);
}


void ROBDD::print (Vertex * v) 
{
	Element * var = v->get_var ();
	identify();	
	if (var != NULL)
	{
		cout << var->get_element_name () << " & id: " << v->get_id () << endl;
		cout << "L ";
		print (v->get_lo ());
		cout << "R ";
		print (v->get_hi ());
		return;
	}
	cout << v->get_value () << " & id: " << v->get_id () <<  " addres: " << v << endl;
	return;
}

void ROBDD::identify ()
{
	unsigned int * last_id = (unsigned int *) malloc (sizeof (unsigned int));
	*last_id = 1;
	identify (root, last_id);
}