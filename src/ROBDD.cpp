#include "ROBDD.h"
#include <set>

ROBDD::ROBDD (ElementSet * set)
{
	nof_updates  = 0;
	nof_consults = 0;
	time_consulting = 0;
	time_updating = 0;
	time_reducing = 0;

	elm_set = set;
	unsigned int n = elm_set->get_set_cardinality ();
	root = new Vertex (false, n + 1);
	cardinality = 1;
	max_size = 1;

	// initial ordering is 0, 1, ..., n-1
	ordering = (unsigned int *) malloc (sizeof (unsigned int) * n);
	for (unsigned int i = 0; i < n; i++)
		ordering[i] = i;

	log_of_intervals = new list <pair <bool, ElementSubset *> >();
}

ROBDD::ROBDD (ElementSet * set, unsigned int * ord)
{
	nof_updates  = 0;
	nof_consults = 0;
	time_consulting = 0;
	time_updating = 0;
	time_reducing = 0;

	log_of_intervals = new list <pair <bool, ElementSubset *> >();
	elm_set = set;
	unsigned int n = elm_set->get_set_cardinality ();
	root = new Vertex (false, n + 1);
	cardinality = 1;
	max_size = 1;

	ordering = (unsigned int *) malloc (sizeof (unsigned int) * n);
	for (unsigned int i = 0; i < n; i++)
		ordering[i] = ord[i];

}

ROBDD::ROBDD (ElementSet * set, int a)
{
	elm_set = set;
	Element * elm = elm_set->get_element (0);
	root = new Vertex (elm, 1);

	ordering = NULL;
	log_of_intervals = NULL;
	
	// teste obdd1
	// elm = elm_set->get_element (1);
	// Vertex * v_lo = new Vertex (elm, 2);
	// Vertex * v_hi = new Vertex (elm, 2);
	// Vertex * zero = new Vertex (false, 3);
	// Vertex * one = new Vertex (true, 3);
	// v_lo->set_child (one, true);
	// v_lo->set_child (zero, false);
	// v_hi->set_child (one, true);
	// v_hi->set_child (zero, false);
	// root->set_child (v_hi, true);
	// root->set_child (v_lo, false);
	// cardinality = 5;

	// test obdd2
	// elm = elm_set->get_element (1);
	// Vertex * v_lo = new Vertex (elm, 2);
	// Vertex * v_hi = new Vertex (elm, 2);
	// Vertex * zero = new Vertex (false, 3);
	// Vertex * one = new Vertex (true, 3);
	// v_lo->set_child (one, true);
	// v_lo->set_child (one, false);
	// v_hi->set_child (one, true);
	// v_hi->set_child (zero, false);
	// root->set_child (v_hi, true);
	// root->set_child (v_lo, false);
	// cardinality = 5;

	// teste obdd3
	// elm = elm_set->get_element (1);
	// Vertex * v_lo = new Vertex (elm, 2);
	// Vertex * v_hi = new Vertex (elm, 2);
	// Vertex * one = new Vertex (true, 3);
	// v_lo->set_child (one, true);
	// v_lo->set_child (one, false);
	// v_hi->set_child (one, true);
	// v_hi->set_child (one, false);
	// root->set_child (v_hi, true);
	// root->set_child (v_lo, false);
	// cardinality = 4;
}	


ROBDD::ROBDD (ElementSet * set, ElementSubset * subset)
{
	nof_updates  = 0;
	nof_consults = 0;
	unsigned int set_card = set->get_set_cardinality ();

	// initial ordering is 0, 1, ..., n-1
	ordering = (unsigned int *) malloc (sizeof(unsigned int) * set_card);
	for (unsigned int i = 0; i < set_card; i++)
		ordering[i] = i;


	elm_set = set;
	Vertex * zero = new Vertex (false, set_card + 1);
	Vertex * one = new Vertex (true, set_card + 1);
	Element * root_elm = elm_set->get_element (ordering[0]);
	root = new Vertex (root_elm, 1);
	cardinality = 3;
	build (root, 1, set_card, subset, zero, one);
	max_size = cardinality;

	log_of_intervals = new list <pair <bool, ElementSubset *> >();
}

void ROBDD::build (Vertex * v, unsigned int ord_index, unsigned int set_card, \
ElementSubset * subset, Vertex * zero, Vertex * one)
{
	bool zeroside;
	zeroside = !subset->has_element (ordering[ord_index - 1]);
	v->set_child (zero, zeroside);
	
	if (ord_index == set_card) 
	{
		v->set_child (one, !zeroside);
		return;
	}

	unsigned int child_index = ordering[ord_index] + 1;
	Vertex * next_vertice = new Vertex (elm_set->get_element (child_index - 1), ++ord_index);
	v->set_child (next_vertice, !zeroside);
	cardinality++;
	build (next_vertice, ord_index, set_card, subset, zero, one);	
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
	delete_subtree (&root, &cardinality);
	if (ordering != NULL)
		free (ordering);
	if (log_of_intervals != NULL)
	{
		for (list <pair <bool, ElementSubset *> >::iterator it = log_of_intervals->begin (); 
			it != log_of_intervals->end (); it++)
			delete it->second;
		delete log_of_intervals;
		log_of_intervals = NULL;
	}
}


void ROBDD::delete_subtree (Vertex ** v, unsigned int * n)
{
	Vertex ** vertice = get_all_vertex (*v, *n);
	for (unsigned int i = 0; i < *n; i++)
	{
		delete vertice[i];	
		vertice [i] = NULL;
	}
	*n = 0;
	*v = NULL;
	free (vertice);
}


Vertex ** ROBDD::get_all_vertex (Vertex * root, unsigned int n)
{
	Vertex ** v = (Vertex **) malloc (sizeof (Vertex *) * n + 1);
	int * last_index = (int *) malloc (sizeof (int));
	*last_index = 0;
	unmark_all_vertex (root);
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

	fill_vertice (vertice, last_index, v->get_child (true));
	fill_vertice (vertice, last_index, v->get_child (false));
}


void ROBDD::change_ordering (unsigned int * ord)
{
	nof_reorderings++;
	timeval start, end;
	gettimeofday (& start, NULL);


	list <pair <bool, ElementSubset *> > robdd_log (this->get_log ());
	delete_subtree (&root, &cardinality);
	list <pair <bool, ElementSubset *> > * old_log = log_of_intervals;
	unsigned int n = elm_set->get_set_cardinality ();
	log_of_intervals = new list <pair <bool, ElementSubset *> >();
	root = new Vertex (false, n + 1);
	cardinality = 1;
	for (unsigned int i = 0; i < n; i++)
		ordering[i] = ord[i];

	nof_updates = 0;

	for (list <pair <bool, ElementSubset *> >::iterator it = robdd_log.begin (); 
		it != robdd_log.end (); it++)
		this->add_interval (it->second, it->first);

	for (list <pair <bool, ElementSubset *> >::iterator it = old_log->begin (); 
		it != old_log->end (); it++)
		delete it->second;
	delete old_log;

	gettimeofday (& end, NULL);
	time_reordering += (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));
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


void ROBDD::fill_vlist (Vertex * v, list<Vertex *> ** vlists)
{	
	if (v == NULL || v->mark)
		return;
	unsigned int i = v->get_index ();
	vlists[i]->push_back (v);	
	v->mark = true;

	fill_vlist (v->get_child (false), vlists);
	fill_vlist (v->get_child (true), vlists);
	return;
}


void ROBDD::reduce ()
{ 
	timeval start, end;
	gettimeofday (& start, NULL);

	Vertex ** subgraph = (Vertex **) calloc (cardinality + 1, sizeof (Vertex *));
	unsigned int set_card = elm_set->get_set_cardinality ();
	list<Vertex *> ** vlists = (list<Vertex *> **) calloc (set_card + 2, sizeof (list<Vertex *> *));
	for (unsigned int i = 1; i <= set_card + 1; i++) 
		vlists[i] = new list<Vertex *>();
	
	set<Vertex *> trash_can;
	set<Vertex *>::iterator trash_it = trash_can.begin ();
	
	unmark_all_vertex ();
	fill_vlist (root, vlists);

	int next_id = 0;
	for (int i = set_card + 1; i > 0; i--)
	{
		map<Vertex *, pair<int, int> > Q;
		list<Vertex *> * l = vlists[i];
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
				Vertex * u_lo = u->get_child (false);
				Vertex * u_hi = u->get_child (true);
				next_id++;
				u->set_id (next_id);
				subgraph[next_id] = u;
				if (u_lo != NULL)
				{
					Vertex * actual_lo_child = subgraph[u_lo->get_id ()];
					if (actual_lo_child != u_lo) 
						trash_can.insert (trash_it, u_lo);
					u->set_child (actual_lo_child, false);
				}
				if (u_hi != NULL)
				{
					Vertex * actual_hi_child = subgraph[u_hi->get_id ()];
					if (actual_hi_child != u_hi)
						trash_can.insert (trash_it, u_hi);
					u->set_child (actual_hi_child, true);
				}
				oldkey = id_i;
			}
		}
	}
	
	for (trash_it = trash_can.begin (); trash_it != trash_can.end (); )
	{
		Vertex * x = *trash_it;
		trash_it++;
		delete x;
	}
	
	Vertex * new_root = subgraph[root->get_id ()];
	if (root != new_root)
		delete	root;
	
	root = new_root;
	cardinality = root->get_id ();

	for (unsigned int i = 1; i <= set_card + 1; i++)
		delete vlists[i];
	free (vlists);
	free (subgraph);	

	gettimeofday (& end, NULL);
	time_reducing += (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));
}


void ROBDD::union_to (Vertex * root2)
{
	unsigned int set_card = elm_set->get_set_cardinality ();
	map<pair<Vertex *, Vertex*>, Vertex *> pairs;
	unsigned int new_cardinality = 0;
	Vertex * one = new Vertex (true, set_card + 1);
	one->mark = false;
	Vertex * zero = new Vertex (false, set_card + 1);
	zero->mark = false;
	Vertex * new_root = union_step (root, root2, &pairs, &new_cardinality, \
									one, zero);

	if (one->mark)
		new_cardinality++;
	else
		delete one;
	
	if (zero->mark)
		new_cardinality++;
	else
		delete zero;

	delete_subtree (&root, &cardinality);
	cardinality = new_cardinality;
	root = new_root;
	reduce ();
}

Vertex * ROBDD::union_step (Vertex * v1, Vertex * v2, map<pair<Vertex *, Vertex*>,\
							Vertex *> * pairs, unsigned int * new_cardinality, \
							Vertex * one, Vertex * zero)
{
	pair<Vertex *, Vertex *> key (v1, v2);
	map<pair<Vertex *, Vertex *>, Vertex *>::iterator it = pairs->find (key);
	Vertex * u;
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
		u = new Vertex ();
		(*new_cardinality)++;
		u->mark = false;
		pairs->insert(make_pair (key, u));
		
		Vertex * vlow1 = NULL;
		Vertex * vhigh1 = NULL;
		Vertex * vlow2 = NULL;
		Vertex * vhigh2 = NULL;
		int index = min(v1->get_index (), v2->get_index ());
		u->set_index (index);
		u->set_id (index);
		u->set_var (elm_set->get_element (ordering[index - 1]));
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
		Vertex * lo_chi = union_step (vlow1, vlow2, pairs, new_cardinality, one, zero);
		Vertex * hi_chi = union_step (vhigh1, vhigh2, pairs, new_cardinality, one, zero);
		u->set_child (lo_chi, false);
		u->set_child (hi_chi, true);
	}
	return u;
}

// orientation = true for upper
void ROBDD::add_interval (ElementSubset * subset, bool orientation)
{
	nof_updates++;
	timeval start, end;
	gettimeofday (& start, NULL);

	ElementSubset * sub = new ElementSubset ("	", elm_set);
	/*cout << "(RO) ElementSubset do log: " << sub << endl;*/
	sub->copy (subset);

	pair <bool, ElementSubset *> par (orientation, sub);
	log_of_intervals->push_front (par);
	// cout << "(RO) log_of_intervals: de " << &log_of_intervals->front () << " até " << &log_of_intervals->back ()<< endl;
	int set_card = elm_set->get_set_cardinality ();
	Vertex * zero = new Vertex (false, set_card + 1);
	zero->mark = false;
	Vertex * one = new Vertex (true, set_card + 1);
	one->mark = false;
	unsigned int card2 = 0;
	// cout << "(RO) Vou construir o intervalo" << subset->print_subset () <<" com ordem: ";
	// for (unsigned int i = 0; i < elm_set->get_set_cardinality (); i++)
	//  		cout << ordering[i] << " ";
	// cout << endl;
	Vertex * root2 = build_interval (0, &card2, subset, zero, one, orientation);
	union_to (root2);

	if (!one->mark)
		delete one;
	if (!zero->mark)
		delete zero;
	delete_subtree (&root2, &card2);

	if (cardinality > max_size)
		max_size = cardinality;

	gettimeofday (& end, NULL);
	time_updating += (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));
}


Vertex * ROBDD::build_interval (unsigned int index, unsigned int * card, 
	ElementSubset * subset, Vertex * zero, Vertex * one, bool orientation)
{
	if (index == elm_set->get_set_cardinality ())
	{
		(*card)++;
		one->mark = true;
		return one;
	}
	
	if ((orientation == false && subset->has_element (ordering[index])) ||
		(orientation == true && !subset->has_element (ordering[index])))
		return build_interval (index + 1, card, subset, zero, one, orientation);
	
	Vertex * v = new Vertex (elm_set->get_element (ordering[index]), index + 1);
	(*card)++;
	v->set_child (zero, !orientation);
	if (!zero->mark)
	{
		zero->mark = true;
		(*card)++;
	}
	v->set_child (build_interval (index + 1, card, subset, zero, one, orientation), orientation);
	return v;
}


bool ROBDD::contains (ElementSubset * subset)
{
	nof_consults++;
	timeval start, end;
	gettimeofday (& start, NULL);
	
	Vertex * v = root;

	while (!v->is_terminal ()) 
	{
		if (subset->has_element (ordering[v->get_index () - 1]))
			v = v->get_child (true);
		else
			v = v->get_child (false);
	}
	
	gettimeofday (& end, NULL);
	time_consulting += (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));

	return v->get_value ();
}


ElementSubset * ROBDD::get_random_zero_evaluated_element ()
{
	Vertex * v = root;
	if (v->is_terminal () && v->get_value ())
		return NULL;

	ElementSubset * subset = new ElementSubset ("", elm_set);
	while (!v->is_terminal ())
	{
		Vertex * next_v;
		if (v->get_child (true)->is_terminal () && v->get_child (true)->get_value ())
			next_v = v->get_child (false);
		else if (v->get_child (false)->is_terminal () && v->get_child (false)->get_value ())
			next_v = v->get_child (true);
		else
			next_v = v->get_child ((int) rand() % 2);

		if (next_v == v->get_child (true))
			subset->add_element (ordering[v->get_index () - 1]);
		v = next_v;
	}
	return subset;
}


list< pair<bool, ElementSubset *> > ROBDD::get_log ()
{
	return *log_of_intervals;
}


ElementSet * ROBDD::get_element_set ()
{
	return elm_set;
}


unsigned int ROBDD::get_cardinality ()
{
	return cardinality;
}


unsigned int ROBDD::get_nof_consults () 
{
	return nof_consults;
}


unsigned int ROBDD::get_nof_updates () 
{
	return nof_updates;
}


int ROBDD::get_time_consulting ()
{
	return time_consulting;
}


int ROBDD::get_time_updating ()
{
	return time_updating;
}


int ROBDD::get_time_reducing ()
{
	return time_reducing;
}


unsigned int ROBDD::get_nof_reorderings ()
{
	return nof_reorderings;
}


int ROBDD::get_time_reordering ()
{
	return time_reordering;
}

unsigned int ROBDD::get_max_size ()
{
	return max_size;
}