#include "ROBDD.h"


ROBDD::ROBDD (ElementSet * set)
{
	elm_set = set;
	root = new Vertex (false, elm_set->get_set_cardinality () + 1);
	cardinality = 1;
}

ROBDD::ROBDD (ElementSet * set, int a)
{
	elm_set = set;
	Element * elm = elm_set->get_element (0);
	root = new Vertex (elm, 1);
	// teste obdd1
	elm = elm_set->get_element (1);
	Vertex * v_lo = new Vertex (elm, 2);
	Vertex * v_hi = new Vertex (elm, 2);
	Vertex * zero = new Vertex (false, 3);
	Vertex * one = new Vertex (true, 3);
	v_lo->set_child (one, true);
	v_lo->set_child (zero, false);
	v_hi->set_child (one, true);
	v_hi->set_child (zero, false);
	root->set_child (v_hi, true);
	root->set_child (v_lo, false);
	cardinality = 5;

	// test obdd2
/*	elm = elm_set->get_element (1);
	Vertex * v_lo = new Vertex (elm, 2);
	Vertex * v_hi = new Vertex (elm, 2);
	Vertex * zero = new Vertex (false, 3);
	Vertex * one = new Vertex (true, 3);
	v_lo->set_child (one, true);
	v_lo->set_child (one, false);
	v_hi->set_child (one, true);
	v_hi->set_child (zero, false);
	root->set_child (v_hi, true);
	root->set_child (v_lo, false);
	cardinality = 5;*/

	// teste obdd3
	/*elm = elm_set->get_element (1);
	Vertex * v_lo = new Vertex (elm, 2);
	Vertex * v_hi = new Vertex (elm, 2);
	Vertex * one = new Vertex (true, 3);
	v_lo->set_child (one, true);
	v_lo->set_child (one, false);
	v_hi->set_child (one, true);
	v_hi->set_child (one, false);
	root->set_child (v_hi, true);
	root->set_child (v_lo, false);
	cardinality = 4;*/
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
	unmark_all_vertex ();
	Vertex ** vertice = get_all_vertex ();
	for (unsigned int i = 0; i < cardinality; i++)
	{
		cout.flush ();
		delete vertice[i];
	}
	free (vertice);
}


Vertex ** ROBDD::get_all_vertex ()
{
	Vertex ** v = (Vertex **) malloc (sizeof (Vertex *) * cardinality);
	int * last_index = (int *) malloc (sizeof (int *));
	*last_index = 0;
	fill_vertice (v, last_index, root);
	free (last_index);
	return v;
}

void ROBDD::fill_vertice (Vertex ** vertice, int * last_index, Vertex * v)
{
	if (v == NULL || v->mark)
		return;
	vertice[*last_index] = v;
	v->mark = true;
	(*last_index)++;

	fill_vertice(vertice, last_index, v->get_child (true));
	fill_vertice(vertice, last_index, v->get_child (false));
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
		cout << var->get_element_name () << " & id: " << v->get_id () <<  " addres: " << v << " index: " << v->get_index () << endl;
		cout << "L ";
		print (v->get_child (false));
		cout << "R ";
		print (v->get_child (true));
		return;
	}
	cout << v->get_value () << "      & id: " << v->get_id () <<  " addres: " << v << " index: " << v->get_index () << endl;
	return;
}


void ROBDD::fill_vlist (Vertex * v, list<Vertex *> ** vlists)
{	
	if (v == NULL || v->mark)
		return;
	unsigned int i = v->get_id ();
	cout.flush ();
	vlists[i]->push_back (v);	
	v->mark = true;

	fill_vlist (v->get_child (false), vlists);
	fill_vlist (v->get_child (true), vlists);
	return;
}


void ROBDD::reduce ()
{
	Vertex ** subgraph = (Vertex **) calloc (cardinality + 1, sizeof (Vertex *));
	unsigned int set_card = elm_set->get_set_cardinality ();
	list<Vertex *> ** vlists = (list<Vertex *> **) calloc (set_card + 2, sizeof (list<Vertex *> *));
	for (unsigned int i = 1; i <= set_card + 1; i++) 
		vlists[i] = new list<Vertex *>();
	
	unmark_all_vertex ();
	fill_vlist (root, vlists);

	int next_id = 0;
	for (int i = set_card + 1; i > 0; i--)
	{
		map<Vertex *, pair<int, int> > Q;
		list<Vertex *> * l = vlists[i];
		pair<Vertex *, Vertex *> trash (NULL, NULL);
		for (list<Vertex*>::iterator it = l->begin (); it != l->end (); it++)
		{
			Vertex * u = *it;
			Vertex * u_lo = u->get_child (false);
			Vertex * u_hi = u->get_child (true);
			if (u->get_index () == set_card + 1) 
			{
				pair<int,  int> id_i (-1, u->get_value ());
				Q.insert(make_pair (u, id_i));
			}
			else if (u_hi->get_id () == u_lo->get_id ()) 
			{

				u->set_id (u_lo->get_id ());
				if (u_hi != u_lo)
				{
					if (subgraph[u_hi->get_id ()] != u_hi) 
					{
						trash.first = u_hi;
						cardinality--;
					}
					if (subgraph[u_hi->get_id ()] != u_lo)
					{
						trash.second = u_lo;
						cardinality--;
					}
				}
			}
			else
			{
				pair<int, int> id_i (u_lo->get_id (), u_hi->get_id ());
				Q.insert(make_pair(u, id_i));
			}
		}
		pair<int, int> oldkey (-1, -1);
		for (map<Vertex *, pair<int, int> >::iterator it = Q.begin(); it != Q.end(); it++)
		{
			pair<int, int> id_i = it->second;
			Vertex * u = it->first;
			if (id_i.first == oldkey.first && id_i.second == oldkey.second)
			{
				u->set_id (next_id);
			}
			else
			{
				next_id++;
				u->set_id (next_id);
				subgraph[next_id] = u;
				if (u->get_child (false) != NULL)
				{
					Vertex * actual_lo_child = subgraph[u->get_child (false)->get_id ()];
					if (actual_lo_child != u->get_child (false)) 
					{
						cardinality--;
						delete u->get_child (false);
					}
					u->set_child (actual_lo_child, false);
				}
				if (u->get_child (true) != NULL)
				{
					Vertex * actual_hi_child = subgraph[u->get_child (true)->get_id ()];
					if (actual_hi_child != u->get_child (true))
					{
						cardinality--;
						delete u->get_child (true);
					}
					u->set_child (actual_hi_child, true);
				}
				oldkey = id_i;
			}
		}
		delete trash.first;
		delete trash.second;
	}
	
	Vertex * new_root = subgraph[root->get_id ()];
	if (root != new_root)
	{
		cardinality--;
		delete	root;
	}
	root = new_root;

	for (unsigned int i = 1; i <= set_card + 1; i++)
		delete vlists[i];
	free (vlists);
	free (subgraph);
}


void ROBDD::union_to (Vertex * root2)
{
	map<pair<Vertex *, Vertex*>, Vertex *> * pairs = new map<pair<Vertex *, Vertex*>, Vertex *>();
	root = union_step (root, root2, pairs);
	cout << root->get_child (true);
}

Vertex * ROBDD::union_step (Vertex * v1, Vertex * v2, map<pair<Vertex *, Vertex*>, Vertex *> * pairs)
{
	map<pair<Vertex *, Vertex *>, Vertex *>::iterator it = pairs->find (make_pair (v1, v2));
	if (it != pairs->end ())
	{
		Vertex * u = it->second;
		cout << "ja fiz esse par (" << v1 << ", " << v2 << ")" << "; retornando u: " << u << " " << u->get_value () << " " << u->get_index () <<  endl;
		return u;
	}

	Vertex * u = new Vertex ();
	u->mark = false;
	pair<Vertex *, Vertex *> key (v1, v2);
	cout << "inserindo " << "(<" << v1 << ", " << v2 << ">, " << u << ")" << endl; 
	pairs->insert(make_pair (key, u));
	cout << (*pairs)[key] << endl;

	// Quero levar 0 e -1 em 0, e 1 em 1 => f(x) = (x * x + x)/2
	int value1 = (v1 != NULL) && (v1->get_value () * v1->get_value () + v1->get_value ());
	int value2 = (v2 != NULL) && (v2->get_value () * v2->get_value () + v2->get_value ());
	if ((value1) || (value2) || \
	   ((value1 + value2 == 0) && (v1 != NULL && v1->is_terminal ()) \
	                           && (v2 != NULL && v2->is_terminal ())))
	{
		u->set_value (value1 + value2);
		u->set_index (elm_set->get_set_cardinality () + 1);
		u->set_id (elm_set->get_set_cardinality () + 1);
		u->set_child (NULL, true);
		u->set_child (NULL, false);
	}
	else
	{
		Vertex * vlow1 = NULL;
		Vertex * vhigh1 = NULL;
		Vertex * vlow2 = NULL;
		Vertex * vhigh2 = NULL;
		int index = min(v1->get_index (), v2->get_index ());
		u->set_index (index);
		u->set_var (elm_set->get_element (index - 1));
		if (u->get_index () == v1->get_index ())
		{
			vlow1 = v1->get_child (false);
			vhigh1 = v1->get_child (true);
		}
		else
		{
			vlow1 = v1;
			vhigh1 = v1;
		}
		if (u->get_index () == v2->get_index ())
		{
			vlow2 = v2->get_child (false);
			vhigh2 = v2->get_child (true);
		}	
		else
		{
			vlow2 = v2;
			vhigh2 = v2;
		}
		Vertex * lo_chi = union_step (vlow1, vlow2, pairs);
		cout << "voltei para: v1: " << v1 << " v2: " << v2 << " u: " << u << endl;
		Vertex * hi_chi = union_step (vhigh1, vhigh2, pairs);
		cout << "setting " << u << " childs: " << lo_chi << " & " << hi_chi << endl;
		u->set_child (lo_chi, false);
		u->set_child (hi_chi, true);
	}

	cout << "elms of pairs: " << endl;
	for (map<pair<Vertex*, Vertex *>, Vertex *>::iterator it = pairs->begin (); it != pairs->end (); it++) {
		cout << "(<" << it->first.first << ", " << it->first.second << ">, " << it->second << ")" << endl;
	}

	cout << "retornando u: " << u << " " << u->get_value () << " " << u->get_index () <<  endl;
	cout << "filhos de u: " << u->get_child (false) << " & " << u->get_child (true) << endl;
	return u;
}
