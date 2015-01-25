/*
 * PosetForestSearch.cpp
 *
 *  Created on: Apr 6, 2011
 *      Author: marceloreis
 */

#include "PosetForestSearch.h"

PosetForestSearch::PosetForestSearch ()
{
	list_of_visited_subsets = new Collection ();
	cost_function = NULL;
	bound = FLT_MAX;
}


PosetForestSearch::~PosetForestSearch ()
{
	if (list_of_visited_subsets != NULL)
		delete list_of_visited_subsets;
}


void PosetForestSearch::get_minima_list (unsigned int max_size_of_minima_list)
{
	timeval begin_program, end_program;
	gettimeofday (& begin_program, NULL);

	unsigned int direction;
	map<string, Node *> Forest_A, Forest_B;
	Node * N;

	// the spanning tree T
	N = new Node;
	N->vertex = new ElementSubset ("", set);
	store_visited_subset (N->vertex);
	N->adjacent = new ElementSubset ("", set);
	N->adjacent->set_complete_subset ();
	N->leftmost = 0;  // the first index is zero
	N->cost = FLT_MAX;
	Forest_A.insert (pair<string, Node *> (N->vertex->print_subset (), N));

	// the spanning tree T'
	N = new Node;
	N->vertex = new ElementSubset ("", set);
	N->vertex->set_complete_subset ();
	store_visited_subset (N->vertex);
	N->adjacent = new ElementSubset ("", set);
	N->adjacent->set_complete_subset ();
	N->leftmost = 0;  // the first index is zero
	N->cost = FLT_MAX;
	Forest_B.insert (pair<string, Node *> (N->vertex->print_subset (), N));

	while ( ( (Forest_A.size () > 0) && (Forest_B.size () > 0) ) &&
		    (! cost_function->has_reached_threshold ()) )
	{
		srand ( (unsigned) time (NULL) );
		direction = rand () % 2;

		number_of_iterations++;
		if (Forest_A.size () > max_size_of_the_forest_A)
			max_size_of_the_forest_A = Forest_A.size ();
		if (Forest_B.size () > max_size_of_the_forest_B)
			max_size_of_the_forest_B = Forest_B.size ();

		if (direction == 0)
		{
			N = lower_forest_branch (& Forest_A, & Forest_B);
			if (! cost_function->has_reached_threshold ())
				upper_forest_pruning (& Forest_B, N);
		}
		else
		{
			N = upper_forest_branch (& Forest_A, & Forest_B);
			if (! cost_function->has_reached_threshold ())
				lower_forest_pruning (& Forest_A, N);
		}

		delete N->vertex;
		delete N->adjacent;
		delete N;
	}

	number_of_visited_subsets =  cost_function->get_number_of_calls_of_cost_function ();
	clean_list_of_minima (max_size_of_minima_list);

	gettimeofday (& end_program, NULL);
	elapsed_time_of_the_algorithm = diff_us (end_program, begin_program);

	// For debug purposes: from the correctness of the PFS, both forests must be empty.
	//
	if (! cost_function->has_threshold ())
     {
		if (Forest_A.size () > 0)
			cout << endl << "Error in PFS algorithm: Forest A has " << Forest_A.size ()
		    << " elements, and it should be empty!" << endl;
		if (Forest_B.size () > 0)
			cout << endl << "Error in PFS algorithm: Forest B has " << Forest_B.size ()
		    << " elements, and it should be empty!" << endl;
     }
}


PosetForestSearch::Node * PosetForestSearch::lower_forest_branch
     (map<string, Node *> * Forest_A, map<string, Node *> * Forest_B)
{
	map<string, Node *>::iterator it;
	Node * R, * M, * N;
	unsigned int i, m;

    // TODO: actual random selection of a tree
	srand ( (unsigned) time (NULL) );
	i = rand () % 2;
	if (i == 0)
		it = Forest_A->begin ();
	else
	{
		it = Forest_A->end ();
		it--;
	}

	R = it->second;         // selects a tree from the forest
	Forest_A->erase (it);

	if (R->cost == FLT_MAX)
	{
		it = Forest_B->find (R->vertex->print_subset ());
		if (it == Forest_B->end () )
		{
			R->cost = cost_function->cost (R->vertex);
			R->vertex->cost = R->cost;
			store_minimum_subset (R->vertex);
		}
		else if (it->second->cost == FLT_MAX)
		{
			R->cost = cost_function->cost (R->vertex);
			R->vertex->cost = R->cost;
			store_minimum_subset (R->vertex);
			it->second->cost = R->cost;
		}
		else  // it->second->cost != FLT_MAX
			R->cost = it->second->cost;
	}

	M = R;
	N = R;

	// Walk on the tree whose root is R[vertex]
	//
	while ((! N->adjacent->is_empty () ) && (N->cost <= M->cost) )
	{
		Forest_A->insert (pair<string, Node *> (N->vertex->print_subset (), N));
		M = N;
		m = M->adjacent->remove_random_element ();
		N = new Node;
		N->vertex = new ElementSubset ("", set);
		N->vertex->copy (M->vertex);
		N->vertex->add_element (m);

		store_visited_subset (N->vertex);

		N->leftmost = m + 1;  // the index starts with zero
		N->adjacent = new ElementSubset ("", set);
		for (i = N->leftmost; i < set->get_set_cardinality (); i++)
			N->adjacent->add_element (i);

		it = Forest_B->find (N->vertex->print_subset ());
		if ( (it == Forest_B->end ()) )
			N->cost = cost_function->cost (N->vertex);
		else if (it->second->cost == FLT_MAX)
		{
			N->cost = cost_function->cost (N->vertex);
			it->second->cost = N->cost;
		}
		else
			N->cost = it->second->cost;

		if (N->cost <= M->cost)
		{
			N->vertex->cost = N->cost;
			store_minimum_subset (N->vertex);
		}

		// if the algorithm is working under heuristic mode 1 or 2
		// and has reached threshold, then the search is stopped.
		//
		if (cost_function->has_reached_threshold ())
			return N;
	}

	return N;
}


PosetForestSearch::Node * PosetForestSearch::upper_forest_branch
     (map<string, Node *> * Forest_A, map<string, Node *> * Forest_B)
{
	map<string, Node *>::iterator it;
	Node * R, * M, * N;
	unsigned int i, m;

    // TODO: actual random selection of a tree
	srand ( (unsigned) time (NULL) );
	i = rand () % 2;
	if (i == 0)
		it = Forest_B->begin ();
	else
	{
		it = Forest_B->end ();
		it--;
	}

	R = it->second;         // selects a tree from the forest
	Forest_B->erase (it);

	if (R->cost == FLT_MAX)
	{
		it = Forest_A->find (R->vertex->print_subset ());
		if (it == Forest_A->end () )
		{
			R->cost = cost_function->cost (R->vertex);
			R->vertex->cost = R->cost;
			store_minimum_subset (R->vertex);
		}
		else if (it->second->cost == FLT_MAX)
		{
			R->cost = cost_function->cost (R->vertex);
			R->vertex->cost = R->cost;
			store_minimum_subset (R->vertex);
			it->second->cost = R->cost;
		}
		else  // it->second->cost != FLT_MAX
			R->cost = it->second->cost;
	}

	M = R;
	N = R;

	// Walk on the tree whose root is R[vertex]
	//
	while ((! N->adjacent->is_empty ()) && (N->cost <= M->cost))
	{
		Forest_B->insert (pair<string, Node *> (N->vertex->print_subset (), N));
		M = N;
		m = M->adjacent->remove_random_element ();
		N = new Node;
		N->vertex = new ElementSubset ("", set);
		N->vertex->copy (M->vertex);
		N->vertex->remove_element (m);

		store_visited_subset (N->vertex);

		N->leftmost = m + 1;  // the index starts with zero
		N->adjacent = new ElementSubset ("", set);
		for (i = N->leftmost; i < set->get_set_cardinality (); i++)
			N->adjacent->add_element (i);

		it = Forest_A->find (N->vertex->print_subset ());
		if ( (it == Forest_A->end ()) )
			N->cost = cost_function->cost (N->vertex);
		else if (it->second->cost == FLT_MAX)
		{
			N->cost = cost_function->cost (N->vertex);
			it->second->cost = N->cost;
		}
		else
			N->cost = it->second->cost;

		if (N->cost <= M->cost)
		{
			N->vertex->cost = N->cost;
			store_minimum_subset (N->vertex);
		}

		// if the algorithm is working under heuristic mode 1 or 2
		// and has reached threshold, then the search is stopped.
		//
		if (cost_function->has_reached_threshold ())
			return N;
	}

	return N;
}


void PosetForestSearch::search_upper_root
     (map<string, Node *> * Forest_B, ElementSubset * M)
{
	map<string, Node *>::iterator it;
	Node * N;
	unsigned int i;
	int m, k = set->get_set_cardinality () - 1;

	while ((k >= 0) && (M->has_element ((unsigned int) k)) )
		k--;

	while (k >= 0)
	{
		M->add_element (k);
		it = Forest_B->find (M->print_subset ());
		if (it != Forest_B->end ())
		{
			it->second->adjacent->remove_element (k);
			k = -1;
		}
		else
		{
			N = new Node;
			N->vertex = new ElementSubset ("", set);
			N->vertex->copy (M);
			store_visited_subset (N->vertex);

			m = k;
			while ((k >= 0) && (M->has_element ((unsigned int) k)) )
				k--;
			N->leftmost = k + 1;  // the index starts with zero

			N->adjacent = new ElementSubset ("", set);
			for (i = N->leftmost; i < set->get_set_cardinality (); i++)
				N->adjacent->add_element (i);
			N->adjacent->remove_element ((unsigned int) m);

			N->cost = FLT_MAX; // infinity

			Forest_B->insert (pair<string, Node *> (N->vertex->print_subset (), N));

			// if the algorithm is working under heuristic mode 1 or 2
			// and has reached threshold, then the search is stopped.
			//
			if (cost_function->has_reached_threshold ())
				return;

		} // else

	} // while
}


void PosetForestSearch::search_lower_root
     (map<string, Node *> * Forest_A, ElementSubset * M)
{
	map<string, Node *>::iterator it;
	Node * N;
	unsigned int i;
	int m, k = set->get_set_cardinality () - 1;

	while ((k >= 0) && (! M->has_element ((unsigned int) k)) )
		k--;

	while (k >= 0)
	{
		M->remove_element (k);
		it = Forest_A->find (M->print_subset ());
		if (it != Forest_A->end ())
		{
			it->second->adjacent->remove_element (k);
			k = -1;
		}
		else
		{
			N = new Node;
			N->vertex = new ElementSubset ("", set);
			N->vertex->copy (M);
			store_visited_subset (N->vertex);

			m = k;
			while ((k >= 0) && (! M->has_element ((unsigned int) k)) )
				k--;
			N->leftmost = k + 1;  // the index starts with zero

			N->adjacent = new ElementSubset ("", set);
			for (i = N->leftmost; i < set->get_set_cardinality (); i++)
				N->adjacent->add_element (i);
			N->adjacent->remove_element ((unsigned int) m);

			N->cost = FLT_MAX; // infinity

			Forest_A->insert (pair<string, Node *> (N->vertex->print_subset (), N));

			// if the algorithm is working under heuristic mode 1 or 2
			// and has reached threshold, then the search is stopped.
			//
			if (cost_function->has_reached_threshold ())
				return;

		} // else

	} // while
}


void PosetForestSearch::search_lower_children
	(map<string, Node *> * Forest_B,
	 Node * N, ElementSubset * M, ElementSubset * Y)
{
	map<string, Node *>::iterator it;
	int i;
	Node * B;
	unsigned int j;

	i = set->get_set_cardinality () - 1;  // i = n
	while ((i >= 0) && (M->has_element (i)) )
	{
		M->remove_element (i); // A = M - {s_i}

		if (M->contains (Y)) // if B contains Y
		{
			it = Forest_B->find (M->print_subset ());
			if (it != Forest_B->end ())
			{
				delete it->second->vertex;
				delete it->second->adjacent;
				delete it->second;
				Forest_B->erase (it);
			}
		}
		else
		{
			if (((N == NULL) || (N->adjacent->has_element (i)) ) )
			{
				B = new Node;
				B->vertex = new ElementSubset ("", set);
				B->vertex->copy (M);
				store_visited_subset (B->vertex);

				B->leftmost = i + 1;  // the index starts with zero
				B->adjacent = new ElementSubset ("", set);
				for (j = B->leftmost; j < set->get_set_cardinality (); j++)
					B->adjacent->add_element (j);

				B->cost = FLT_MAX; // infinity

				Forest_B->insert(pair<string, Node *> (B->vertex->print_subset (), B));

				// if the algorithm is working under heuristic mode 1 or 2
				// and has reached threshold, then the search is stopped.
				//
				if (cost_function->has_reached_threshold ())
					return;

			} // if ((it == Forest_A->end ()) &&

		} // else

		M->add_element (i);
		i--;

	} // while (i..
}


void PosetForestSearch::search_upper_children
     (map<string, Node *> * Forest_A,
      Node * N, ElementSubset * M, ElementSubset * Y)
{
	map<string, Node *>::iterator it;
	int i;
	Node * A;
	unsigned int j;

	i = set->get_set_cardinality () - 1;  // i = n
	while ((i >= 0) && (! M->has_element (i)) )
	{
		M->add_element (i); // A = M \cup {s_i}

		if (M->is_contained_by (Y) ) // if A is contained in Y
		{
			it = Forest_A->find (M->print_subset ());
			if (it != Forest_A->end ())
			{
				delete it->second->vertex;
				delete it->second->adjacent;
				delete it->second;
				Forest_A->erase (it);
			}
		}
		else
		{
			if (( (N == NULL) || (N->adjacent->has_element (i)) ) )
			{
				A = new Node;
				A->vertex = new ElementSubset ("", set);
				A->vertex->copy (M);
				store_visited_subset (A->vertex);

				A->leftmost = i + 1;  // the index starts with zero
				A->adjacent = new ElementSubset ("", set);
				for (j = A->leftmost; j < set->get_set_cardinality (); j++)
					A->adjacent->add_element (j);

				A->cost = FLT_MAX; // infinity

				Forest_A->insert(pair<string, Node *> (A->vertex->print_subset (), A));

				// if the algorithm is working under heuristic mode 1 or 2
				// and has reached threshold, then the search is stopped.
				//
				if (cost_function->has_reached_threshold ())
					return;

			} // if ((it == Forest_A->end ()) &&

		} // else

		M->remove_element (i);
		i--;

	} // while
}


void PosetForestSearch::upper_forest_pruning
     (map<string, Node *> * Forest_B, Node * N)
{
	map<string, Node *>::iterator it;
	Node * _M;
	ElementSubset M ("", set);
	int k;

	M.copy (N->vertex);
	k = set->get_set_cardinality () - 1;  // k = n - 1

	while ( (! N->adjacent->is_empty () )  &&
			(k >= (int) N->leftmost)
		  )
	{
		it  = Forest_B->find (M.print_subset ());
		if (it != Forest_B->end ())
		{
			_M = it->second;
			Forest_B->erase (it);
		}
		else
			_M = NULL;

		search_lower_children (Forest_B, _M, & M, N->vertex);

		// if the algorithm is working under heuristic mode 1 or 2
		// and has reached threshold, then the search is stopped.
		//
		if (cost_function->has_reached_threshold ())
			return;

		if (_M != NULL)
		{
			delete _M->vertex;
			delete _M->adjacent;
			delete _M;
		}

		M.add_element (k);
		k--;
	}

	it  = Forest_B->find (M.print_subset ());
	if (it != Forest_B->end ())
	{
		search_lower_children (Forest_B, it->second, & M, N->vertex);

		// if the algorithm is working under heuristic mode 1 or 2
		// and has reached threshold, then the search is stopped.
		//
		if (cost_function->has_reached_threshold ())
			return;
		delete it->second->vertex;
		delete it->second->adjacent;
		delete it->second;
		Forest_B->erase (it);
	}
	else
	{
		search_lower_children (Forest_B, NULL, & M, N->vertex);

		// if the algorithm is working under heuristic mode 1 or 2
		// and has reached threshold, then the search is stopped.
		//
		if (cost_function->has_reached_threshold ())
			return;

		search_upper_root (Forest_B, & M); // warning: this function modifies "M" !!!

		// if the algorithm is working under heuristic mode 1 or 2
		// and has reached threshold, then the search is stopped.
		//
		if (cost_function->has_reached_threshold ())
			return;
	}
}


void PosetForestSearch::lower_forest_pruning
     (map<string, Node *> * Forest_A, Node * N)
{
	map<string, Node *>::iterator it;
	Node * _M;
	ElementSubset M ("", set);
	int k;

	M.copy (N->vertex);
	k = set->get_set_cardinality () - 1;  // k = n - 1

	while ((! N->adjacent->is_empty ()) && (k >= (int) N->leftmost) )
	{
		it  = Forest_A->find (M.print_subset ());
		if (it != Forest_A->end ())
		{
			_M = it->second;
			Forest_A->erase (it);
		}
		else
			_M = NULL;

		search_upper_children (Forest_A, _M, & M, N->vertex);

		// if the algorithm is working under heuristic mode 1 or 2
		// and has reached threshold, then the search is stopped.
		//
		if (cost_function->has_reached_threshold ())
			return;

		if (_M != NULL)
		{
			delete _M->vertex;
			delete _M->adjacent;
			delete _M;
		}

		M.remove_element (k);
		k--;
	}

	it  = Forest_A->find (M.print_subset ());
	if (it != Forest_A->end ())
	{
		search_upper_children (Forest_A, it->second, & M, N->vertex);

		// if the algorithm is working under heuristic mode 1 or 2
		// and has reached threshold, then the search is stopped.
		//
		if (cost_function->has_reached_threshold ())
			return;

		delete it->second->vertex;
		delete it->second->adjacent;
		delete it->second;
		Forest_A->erase (it);
	}
	else
	{
		search_upper_children (Forest_A, NULL, & M, N->vertex);

		// if the algorithm is working under heuristic mode 1 or 2
		// and has reached threshold, then the search is stopped.
		//
		if (cost_function->has_reached_threshold ())
			return;

		search_lower_root (Forest_A, & M); // warning: this function modifies "M" !!!

		// if the algorithm is working under heuristic mode 1 or 2
		// and has reached threshold, then the search is stopped.
		//
		if (cost_function->has_reached_threshold ())
			return;
	}
}


