#include "ROBDD.h"


ROBDD::ROBDD (ElementSet * set)
{
	elm_set = set;
	root = new Vertex (false, 1);
	cardinality = 0;
}


ROBDD::ROBDD (ElementSet * set, ElementSubset * subset)
{
	unsigned int set_card = set->get_set_cardinality ();
	elm_set = set;
	Vertex * zero = new Vertex (false, set_card + 1);
	Vertex * one = new Vertex (true, set_card + 1);
	root = new Vertex (elm_set->get_element (0), 1);	
	cardinality = 3;
	build (root, 1, set_card, subset, zero, one);
}


void ROBDD::build (Vertex * v, unsigned int elm_index, unsigned int set_card, \
ElementSubset * subset, Vertex * zero, Vertex * one)
{
	bool zeroside;
	zeroside = !subset->has_element (elm_index - 1);
	v->set_child (zero, zeroside);
	
	if (elm_index == set_card) 
	{
		v->set_child (one, !zeroside);
		return;
	}

	unsigned int child_id = elm_index + 1;
	Vertex * next_vertice = new Vertex (elm_set->get_element (child_id - 1), child_id);
	v->set_child (next_vertice, !zeroside);
	cardinality++;
	build (next_vertice, child_id, set_card, subset, zero, one);	
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
	cout << "  ";
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


void ROBDD::fill_vlist (Vertex * v, list<Vertex *> ** vlists)
{	
	if (v == NULL || v->mark)
		return;
	unsigned int i = v->get_id ();
	cout.flush ();
	vlists[i - 1]->push_back (v);
	v->mark = true;

	fill_vlist (v->get_child (false), vlists);
	fill_vlist (v->get_child (true), vlists);
	return;
}


void ROBDD::reduce ()
{
	unsigned int set_card = elm_set->get_set_cardinality ();
	Vertex ** subgraph = (Vertex **) calloc (cardinality + 1, sizeof (Vertex *));
	list<Vertex *> ** vlists = (list<Vertex *> **) calloc (set_card + 1, sizeof (list<Vertex *> *));
	for (unsigned int i = 0; i < set_card + 1; i++) {
		vlists[i] = new list<Vertex *>();
	}
	unmark_all_vertex ();
	fill_vlist (root, vlists);
	/*for (unsigned int i = 0; i < set_card; i++)
	{
		list<Vertex *> lista = vlist[i];
		for(list<Vertex *>::iterator it = lista.begin (); it != lista.end (); it++)
		{
			cout << *it << endl;
		}
	}*/
	/*
	int next_id = 0;
	for (int i = cardinality; i > 0; i--)
	{
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
	root = subgraph[root->get_id ()];*/
}
