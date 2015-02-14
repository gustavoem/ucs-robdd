#include "ROBDD.h"


ROBDD::ROBDD (ElementSet * set)
{
	elm_set = set;
	root = new Vertex (false, elm_set->get_set_cardinality () + 1);
	cardinality = 0;
}

ROBDD::ROBDD (ElementSet * set, int a)
{
	elm_set = set;
	Element * elm = elm_set->get_element (0);
	root = new Vertex (elm, 1);
	elm = elm_set->get_element (1);
	Vertex * v_lo = new Vertex (elm, 2);
	Vertex * v_hi = new Vertex (elm, 2);
	root->set_child (v_hi, true);
	root->set_child (v_lo, false);
	Vertex * zero = new Vertex (false, 4);
	Vertex * one = new Vertex (true, 4);
	v_lo->set_child (one, true);
	v_lo->set_child (zero, false);
	v_lo->set_child (one, true);
	v_lo->set_child (zero, false);
	cardinality = 5;
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
	Vertex ** subgraph = (Vertex **) calloc (cardinality, sizeof (Vertex *));
	unsigned int set_card = elm_set->get_set_cardinality ();
	list<Vertex *> ** vlists = (list<Vertex *> **) calloc (set_card + 1, sizeof (list<Vertex *> *));
	for (unsigned int i = 0; i < set_card + 1; i++) {
		vlists[i] = new list<Vertex *>();
	}
	
	unmark_all_vertex ();
	fill_vlist (root, vlists);

	// Debugging purposes only
	/*for (unsigned int i = 0; i <= set_card; i++)
	{
		list<Vertex *> * lista = vlists[i];
		cout << "lista de id: " << i + 1 << endl;
		for(list<Vertex *>::iterator it = lista->begin (); it != lista->end (); it++)
		{
			cout << *it << endl;
		}
	}*/

	int next_id = 0;
	for (int i = set_card + 1; i > 0; i--)
	{
		map<pair<int, int>, Vertex *> Q;
		list<Vertex *> * l = vlists[i - 1];
		for (list<Vertex*>::iterator it = l->begin (); it != l->end (); it++)
		{
			Vertex * u = *it;
			Vertex * u_lo = u->get_child (false);
			Vertex * u_hi = u->get_child (true);
			if (u->get_id () == set_card + 1) 
			{
				pair<int,  int> key (u->get_value (), -1);
				Q.insert(make_pair (key, u));
			}
			else if (u_hi->get_id () == u_lo->get_id ())
				u->set_id (u_lo->get_id ());
			else
			{
				pair<int, int> key (u_lo->get_id (), u_hi->get_id ());
				Q.insert(make_pair(key, u));
			}
		}
		pair<int, int> oldkey (-1, -1);
		for (map<pair<int, int>, Vertex *>::iterator it = Q.begin(); it != Q.end(); it++)
		{
			pair<int, int> key = it->first;
			Vertex * u = it->second;
			if (key.first == oldkey.first && key.second == oldkey.second)
				u->set_id (next_id);
			else
			{
				next_id++;
				u->set_id (next_id);
				subgraph[next_id] = u;
				if (u->get_child (false) != NULL)
					u->set_child (subgraph[u->get_child (false)->get_id ()], false);
				if (u->get_child (true) != NULL)
					u->set_child (subgraph[u->get_child (true)->get_id ()], true);
				oldkey = key;
			}
		}
	}
	root = subgraph[root->get_id ()];
}

