#include "OBDD.h"
#include <set>

OBDD::OBDD (ElementSet * set)
{
	nof_updates  = 0;
	nof_consults = 0;
	time_consulting = 0;
	time_updating = 0;

	elm_set = set;
	root = new PVertex (false, elm_set->get_set_cardinality () + 1);
	zero_node = root;
	cardinality = 1;
}

OBDD::OBDD (ElementSet * set, ElementSubset * subset)
{
	nof_updates  = 0;
	nof_consults = 0;

	unsigned int set_card = set->get_set_cardinality ();
	elm_set = set;
	PVertex * zero = new PVertex (false, set_card + 1);
	zero_node = zero;
	PVertex * one = new PVertex (true, set_card + 1);
	root = new PVertex (elm_set->get_element (0), 1);	
	cardinality = 3;
	build (root, 1, set_card, subset, zero, one);
}


void OBDD::build (PVertex * v, unsigned int elm_index, unsigned int set_card, \
ElementSubset * subset, PVertex * zero, PVertex * one)
{
	bool zeroside;
	zeroside = !subset->has_element (elm_index - 1);
	v->set_child (zero, zeroside);
	zero->add_parent (v);
	
	if (elm_index == set_card) 
	{
		v->set_child (one, !zeroside);
		one->add_parent (v);
		return;
	}

	unsigned int child_id = elm_index + 1;
	PVertex * next_vertice = new PVertex (elm_set->get_element (child_id - 1), child_id);
	v->set_child (next_vertice, !zeroside);
	next_vertice->add_parent (v);
	cardinality++;
	build (next_vertice, child_id, set_card, subset, zero, one);	
}


void OBDD::unmark_all_vertex ()
{
	unmark_all_vertex (root);
}


void OBDD::unmark_all_vertex (PVertex * v)
{
	if (v == NULL)
		return;
	v->mark = false;
	unmark_all_vertex (v->get_child(true));
	unmark_all_vertex (v->get_child(false));
}



OBDD::~OBDD ()
{
	delete_subtree (&root, &cardinality);
}


void OBDD::delete_subtree (PVertex ** v, unsigned int * n)
{
	PVertex ** vertice = get_all_vertex (*v, *n);
	for (unsigned int i = 0; i < *n; i++)
	{
		delete vertice[i];
		vertice [i] = NULL;
	}
	*n = 0;
	*v = NULL;
	free (vertice);
}


PVertex ** OBDD::get_all_vertex (PVertex * root, unsigned int n)
{
	PVertex ** v = (PVertex **) malloc (sizeof (PVertex *) * n + 1);
	int * last_index = (int *) malloc (sizeof (int));
	*last_index = 0;
	unmark_all_vertex (root);
	fill_vertice (v, last_index, root);

	free (last_index);
	return v;
}

void OBDD::fill_vertice (PVertex ** vertice, int * last_index, PVertex * v)
{
	if (v == NULL || v->mark)
		return;

	vertice[*last_index] = v;
	v->mark = true;
	(*last_index)++;

	fill_vertice(vertice, last_index, v->get_child (true));
	fill_vertice(vertice, last_index, v->get_child (false));
}


PVertex * OBDD::get_root()
{
	return root;
}


void OBDD::print ()
{	
	cout << "  ";
	print (root);
}


void OBDD::print (PVertex * v) 
{
	if (v == NULL)
		return;

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


void OBDD::fill_vlist (PVertex * v, list<PVertex *> ** vlists)
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


void OBDD::reduce ()
{ 
	PVertex ** subgraph = (PVertex **) calloc (cardinality + 1, sizeof (PVertex *));
	unsigned int set_card = elm_set->get_set_cardinality ();
	list<PVertex *> ** vlists = (list<PVertex *> **) calloc (set_card + 2, sizeof (list<PVertex *> *));
	for (unsigned int i = 1; i <= set_card + 1; i++) 
		vlists[i] = new list<PVertex *>();
	
	set<PVertex *> trash_can;
	set<PVertex *>::iterator trash_it = trash_can.begin ();
	
	unmark_all_vertex ();
	fill_vlist (root, vlists);

	int next_id = 0;
	for (int i = set_card + 1; i > 0; i--)
	{
		map<PVertex *, pair<int, int> > Q;
		list<PVertex *> * l = vlists[i];
		for (list<PVertex*>::iterator it = l->begin (); it != l->end (); it++)
		{
			PVertex * u = *it;
			PVertex * u_lo = u->get_child (false);
			PVertex * u_hi = u->get_child (true);
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
						trash_can.insert (trash_it, u_hi);
					if (subgraph[u_hi->get_id ()] != u_lo)
						trash_can.insert (trash_it, u_lo);
				}
			}
			else
			{
				pair<int, int> id_i (u_lo->get_id (), u_hi->get_id ());
				Q.insert(make_pair(u, id_i));
			}
		}
		pair<int, int> oldkey (-1, -1);
		for (map<PVertex *, pair<int, int> >::iterator it = Q.begin(); it != Q.end(); it++)
		{
			pair<int, int> id_i = it->second;
			PVertex * u = it->first;
			if (id_i.first == oldkey.first && id_i.second == oldkey.second)
			{
				u->set_id (next_id);
			}
			else
			{
				PVertex * u_lo = u->get_child (false);
				PVertex * u_hi = u->get_child (true);
				next_id++;
				u->set_id (next_id);
				subgraph[next_id] = u;
				if (u_lo != NULL)
				{
					PVertex * actual_lo_child = subgraph[u_lo->get_id ()];
					if (actual_lo_child != u_lo) 
						trash_can.insert (trash_it, u_lo);
					u->set_child (actual_lo_child, false);
					actual_lo_child->add_parent (u);
				}
				if (u_hi != NULL)
				{
					PVertex * actual_hi_child = subgraph[u_hi->get_id ()];
					if (actual_hi_child != u_hi)
						trash_can.insert (trash_it, u_hi);
					u->set_child (actual_hi_child, true);
					actual_hi_child->add_parent (u);
				}
				oldkey = id_i;
			}
		}
	}
	
	for (trash_it = trash_can.begin (); trash_it != trash_can.end (); )
	{
		PVertex * x = *trash_it;
		trash_it++;
		delete x;
	}
	
	PVertex * new_root = subgraph[root->get_id ()];
	if (root != new_root)
		delete	root;
	
	root = new_root;
	cardinality = root->get_id ();
	
	if (cardinality == 1) /* trivial tree*/
		zero_node = NULL;

	for (unsigned int i = 1; i <= set_card + 1; i++)
		delete vlists[i];
	free (vlists);
	free (subgraph);	
}


void OBDD::union_to (PVertex * root2)
{
	unsigned int set_card = elm_set->get_set_cardinality ();
	map<pair<PVertex *, PVertex*>, PVertex *> pairs;
	unsigned int new_cardinality = 0;
	PVertex * one = new PVertex (true, set_card + 1);
	one->mark = false;
	PVertex * zero = new PVertex (false, set_card + 1);
	zero->mark = false;
	PVertex * new_root = union_step (root, root2, &pairs, &new_cardinality, \
									one, zero);

	zero_node = zero;
	if (one->mark)
		new_cardinality++;
	else
		delete one;
	
	if (zero->mark)
		new_cardinality++;
	else
	{
		zero_node = NULL;
		delete zero;
	}

	delete_subtree (&root, &cardinality);
	cardinality = new_cardinality;
	root = new_root;
	//reduce ();
}

PVertex * OBDD::union_step (PVertex * v1, PVertex * v2, map<pair<PVertex *, PVertex*>,\
							PVertex *> * pairs, unsigned int * new_cardinality, \
							PVertex * one, PVertex * zero)
{
	pair<PVertex *, PVertex *> key (v1, v2);
	map<pair<PVertex *, PVertex *>, PVertex *>::iterator it = pairs->find (key);
	PVertex * u;
	if (it != pairs->end ())
	{
		u = it->second;
		return u;
	}

	// Quero levar 0 e -1 em 0, e 1 em 1 => f(x) = (x * x + x)/2
	int value1 = (v1 != NULL) && (v1->get_value () * v1->get_value () + v1->get_value ());
	int value2 = (v2 != NULL) && (v2->get_value () * v2->get_value () + v2->get_value ());
	if ((value1) || (value2) || \
	   ((value1 + value2 == 0) && (v1 != NULL && v1->is_terminal ()) \
	                           && (v2 != NULL && v2->is_terminal ())))
	{
		if (value1 + value2 == 0)
		{
			u = zero;
			u->mark = true;
		}
		else
		{
			u = one;
			u->mark = true;
		}
		pairs->insert(make_pair (key, u));
	}
	else
	{
		u = new PVertex ();
		(*new_cardinality)++;
		u->mark = false;
		pairs->insert(make_pair (key, u));
		
		PVertex * vlow1 = NULL;
		PVertex * vhigh1 = NULL;
		PVertex * vlow2 = NULL;
		PVertex * vhigh2 = NULL;
		int index = min(v1->get_index (), v2->get_index ());
		u->set_index (index);
		u->set_id (index);
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
		PVertex * lo_chi = union_step (vlow1, vlow2, pairs, new_cardinality, one, zero);
		PVertex * hi_chi = union_step (vhigh1, vhigh2, pairs, new_cardinality, one, zero);
		u->set_child (lo_chi, false);
		u->set_child (hi_chi, true);
		lo_chi->add_parent (u);
		hi_chi->add_parent (u);
	}
	return u;
}

// orientation = true for upper
void OBDD::add_interval (ElementSubset * subset, bool orientation)
{
	nof_updates++;
	timeval start, end;
	gettimeofday (& start, NULL);

	int set_card = elm_set->get_set_cardinality ();
	PVertex * zero = new PVertex (false, set_card + 1);
	zero->mark = false;
	zero_node = zero;
	PVertex * one = new PVertex (true, set_card + 1);
	one->mark = false;
	unsigned int card2 = 0;
	PVertex * root2 = build_interval (0, &card2, subset, zero, one, orientation);
	union_to (root2);

	if (!one->mark)
		delete one;
	if (!zero->mark)
	{
		zero_node = NULL;
		delete zero;
	}

	delete_subtree (&root2, &card2);

	gettimeofday (& end, NULL);
	time_updating += (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));
}


PVertex * OBDD::build_interval (unsigned int index, unsigned int * card, ElementSubset * subset, PVertex * zero, PVertex * one, bool orientation)
{
	if (index == elm_set->get_set_cardinality ())
	{
		(*card)++;
		one->mark = true;
		return one;
	}
	
	if ((orientation == false && subset->has_element (index)) ||
		(orientation == true && !subset->has_element (index)))
		return build_interval (index + 1, card, subset, zero, one, orientation);
	
	PVertex * v = new PVertex (elm_set->get_element (index), index + 1);
	(*card)++;
	v->set_child (zero, !orientation);
	zero->add_parent (v);
	if (!zero->mark)
	{
		zero->mark = true;
		(*card)++;
	}
	PVertex * child = build_interval (index + 1, card, subset, zero, one, orientation);
	v->set_child (child, orientation);
	child->add_parent (v);
	return v;
}


bool OBDD::contains (ElementSubset * subset)
{
	nof_consults++;
	timeval start, end;
	gettimeofday (& start, NULL);
	
	PVertex * v = root;
	unsigned int index = root->get_index ();
	while (!v->is_terminal ()) 
	{
		if (subset->has_element (index - 1))
			v = v->get_child (true);
		else
			v = v->get_child (false);
		index = v->get_index ();
	}
	
	gettimeofday (& end, NULL);
	time_consulting += (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));

	return v->get_value ();
}


ElementSubset * OBDD::get_random_zero_evaluated_element ()
{
	PVertex * v = zero_node;
	if (v == NULL)
		return NULL;

	ElementSubset * subset = new ElementSubset ("", elm_set);
	while (v != root)
	{
		PVertex * parent = v->get_some_parent ();
		if (v == parent->get_child (true))
			subset->add_element (v->get_index () - 1);

		v = parent;
	}
	return subset;
}


unsigned int OBDD::get_nof_consults () 
{
	return nof_consults;
}


unsigned int OBDD::get_nof_updates () 
{
	return nof_updates;
}

int OBDD::get_time_consulting ()
{
	return time_consulting;
}


int OBDD::get_time_updating ()
{
	return time_updating;
}