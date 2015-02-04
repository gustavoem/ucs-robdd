#include "ROBDD.h"


ROBDD::ROBDD (ElementSet * set)
{
	elm_set = set;
	root = new Vertex (false);
	cardinality = 0;
}


ROBDD::ROBDD (ElementSet * set, ElementSubset * subset)
{
	unsigned int set_card = set->get_set_cardinality ();
	elm_set = set;
	Vertex * zero = new Vertex (false);
	Vertex * one = new Vertex (true);
	root = new Vertex (elm_set->get_element (0));	
	cardinality = 3;
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
	cardinality++;
	build (next_vertice, elm_index + 1, set_card, subset, zero, one);	
}


void ROBDD::fill_vlist (Vertex ** vlist, Vertex * v)
{
	if (v == NULL)
		return;
	vlist[v->get_id ()] = v;
}


void ROBDD::unmark_all_vertex ()
{
	unmark_all_vertex (root);
}


void ROBDD::unmark_all_vertex (Vertex * v)
{
	if (v == NULL)
		return;
	v->mark = false;
	unmark_all_vertex (v->get_child(true));
	unmark_all_vertex (v->get_child(false));
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
	if (var != NULL)
	{
		cout << var->get_element_name () << " & id: " << v->get_id () <<  " addres: " << v << endl;
		cout << "L ";
		print (v->get_child (false));
		cout << "R ";
		print (v->get_child (true));
		return;
	}
	cout << v->get_value () << "      & id: " << v->get_id () <<  " addres: " << v << endl;
	return;
}


void ROBDD::identify ()
{
	unsigned int * last_id = (unsigned int *) malloc (sizeof (unsigned int));
	*last_id = 1;
	unmark_all_vertex ();
	identify (root, last_id);
	free (last_id);
}


void ROBDD::identify (Vertex * v, unsigned int * last_id)
{	
	if (v == NULL || v->mark)
		return;
	
	cout << "setting " << v << " id as " << * last_id << endl;
	v->set_id (* last_id);
	(* last_id)++;
	v->mark = true;

	identify (v->get_child (false), last_id);
	identify (v->get_child (true), last_id);
	return;
}


void ROBDD::reduce ()
{
	Vertex ** vlist = (Vertex **) malloc (sizeof (*vlist) * elm_set->get_set_cardinality ());
	Vertex ** subgraph;
	
	identify();	
	fill_vlist (vlist, root);

	int next_id = 0;
	for (int i = elm_set->get_set_cardinality (); i > 0; i--)
	{
		cout << "id: " << i << " | address: " << vlist[i] << endl;
	}
}
