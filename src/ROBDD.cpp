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


void ROBDD::traverse (Vertex * v, unsigned int * last_id, Vertex ** vlist)
{	
	if (v == NULL || v->mark)
		return;

	v->set_id (* last_id);
	vlist[(* last_id) - 1] = v;
	(* last_id)++;
	v->mark = true;

	traverse (v->get_child (false), last_id, vlist);
	traverse (v->get_child (true), last_id, vlist);
	return;
}


void ROBDD::reduce ()
{
	Vertex ** vlist = (Vertex **) malloc (sizeof (*vlist) * elm_set->get_set_cardinality () + 1);
	Vertex ** subgraph = (Vertex **) malloc (sizeof (*vlist) * elm_set->get_set_cardinality () + 1);

	for (int i = 0; i < (int) elm_set->get_set_cardinality () + 1; i++)
		subgraph[i] = NULL;

	unsigned int * last_id = (unsigned int *) malloc (sizeof (unsigned int));
	*last_id = 1;
	unmark_all_vertex ();	
	traverse (root, last_id, vlist);
	free (last_id);

	int next_id = 0;
	for (int i = cardinality; i > 0; i--)
	{
		cout << "id: " << i << " | address: " << vlist[i - 1] << endl;
		map<unsigned int, Vertex *> Q;
		for (int j = cardinality - 1; j >= 0; j--)
		{
			Vertex * u = vlist[j];
			if (u->is_terminal ()) 
			{
				cout << "Inserting: " << "(" << u->get_value () << ", " << u << ")" << endl;
				Q.insert(make_pair (u->get_value (), u));
			}
			else if (u->get_child(true)->get_id () == u->get_child(false)->get_id ())
				u->set_id (u->get_child(true)->get_id ());
			else
			{
				cout << "Inserting: " << "(" << u->get_child(true)->get_id () << ", " << u << ")" << endl;
				Q.insert(make_pair (u->get_child(true)->get_id (), u));
				cout << "Inserting: " << "(" << u->get_child(false)->get_id () << ", " << u << ")" << endl;
				Q.insert(make_pair (u->get_child(false)->get_id (), u));
			}
		}
		int oldkey = -1;
		for (map<unsigned int, Vertex *>::iterator it = Q.begin(); it != Q.end(); it++)
		{
			unsigned int key = it->first;
			Vertex * u = it->second;
			cout << "U address: " << u << endl;
			if ((int) key == oldkey)
				u->set_id (next_id);
			else
			{
				next_id++;
				u->set_id (next_id);
				subgraph[next_id] = u;
				if (!u->is_terminal ())
				{
					u->set_child (subgraph[u->get_child (false)->get_id ()], false);
					u->set_child (subgraph[u->get_child (true)->get_id ()], true);
				}
				oldkey = key;
			}
		}
	}
	root = subgraph[root->get_id ()];
}
