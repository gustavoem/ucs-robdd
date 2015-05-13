#include "UCSROBDDToolBox.h"


namespace UCSROBDDToolBox
{
	ElementSubset * get_minimal_subset (ROBDD * RL, ElementSet * a_set)
	{
		ElementSubset * A, B ("", a_set);
		unsigned int i;

		B.set_complete_subset ();
		if (RL->contains (&B))
			return NULL;
		else
		{
			A = new ElementSubset ("", a_set);
			A->set_complete_subset ();
			while (! B.is_empty ())
			{
				i = B.remove_random_element ();
				A->remove_element (i);
				if (RL->contains (A))
					A->add_element (i);
			}
			return A;
		}
	}


	ElementSubset * get_maximal_subset (ROBDD * RU, ElementSet * a_set)
	{
		ElementSubset * A, B ("", a_set);
		unsigned int i;

		B.set_empty_subset ();
		if (RU->contains (&B))
			return NULL;
		else
		{
			A = new ElementSubset ("", a_set);
			A->set_empty_subset ();
			B.set_complete_subset ();
			while (! B.is_empty ())
			{
				i = B.remove_random_element ();
				A->add_element (i);
				if (RU->contains (A))
					A->remove_element (i);
			}
			return A;
		}
	}


	void update_lower_restriction (ROBDD * R, ElementSubset * A)
	{
		R->add_interval (A, false);
	}


	void update_upper_restriction (ROBDD * R, ElementSubset * A)
	{
		R->add_interval (A, true);
	}


	void DFS (Node * M, Collection * L, ROBDD * RL, ROBDD * RU, CostFunction * c,
			  unsigned int * max_graph_size)
	{
		unsigned int direction, i;
		Node * Y, * X = NULL;
		list<Node *> Stack;
		map<string, Node *>Graph;
		map<string, Node *>::iterator it;

		Stack.push_back (M);
		Graph.insert (pair<string, Node *> (M->vertex->print_subset (), M));
		L->add_subset (M->vertex);

		while (Stack.size () > 0)
		{
			Y = Stack.back ();

			do
			{
				X = select_an_unvisited_adjacent (&Graph, RL, RU, Y, &i);

				if (X == NULL)  // i.e., if Y has no unvisited adjacent element
				{
					Stack.remove (Y);   // Y can't be directly popped because some
                                        // nodes might have be inserted over it.
				}
				else
				{
					Stack.push_back (X);

					// insert X into the graph
					Graph.insert (pair<string, UCSROBDDToolBox::Node *> (X->vertex->print_subset (), X));

					if (X->vertex->contains (Y->vertex))
						direction = 0;
					else
						direction = 1;

					if (*max_graph_size < Graph.size ()) // stores the maximum size the graph
						*max_graph_size = Graph.size (); // has achieved so far.

					X->vertex->cost = c->cost (X->vertex); // computes and stores c(X)

					// If the DFS criterion is attained, then X->element is stored
					//
					if (X->vertex->cost <= Y->vertex->cost)
					{
						L->add_subset (X->vertex);
					}

					// if the algorithm is working under heuristic mode 1 or 2
					// and has reached threshold, then the search is stopped.
					//
					if (c->has_reached_threshold ())
						return;

					// Pruning that applies Propositions 3.1 and 3.2
					//
					if (X->vertex->cost > Y->vertex->cost)
					{
						if (direction == 0)  // Proposition 3.2
						{
							UCSROBDDToolBox::update_upper_restriction (RU, X->vertex);
							X->upper_flag->set_empty_subset ();
							Y->upper_flag->remove_element (i);
							UCSROBDDToolBox::prune_upper_elements (&Graph, &Stack, X);
						}
						else  // Proposition 3.1
						{
							UCSROBDDToolBox::update_lower_restriction (RL, X->vertex);
							X->lower_flag->set_empty_subset ();
							Y->lower_flag->remove_element (i);
							UCSROBDDToolBox::prune_lower_elements (&Graph, &Stack, X);
						}
					}
					else if (X->vertex->cost < Y->vertex->cost)
					{
						if (direction == 0)  // Proposition 3.1
						{
							UCSROBDDToolBox::update_lower_restriction (RL, Y->vertex);
							Y->lower_flag->set_empty_subset ();
							X->lower_flag->remove_element (i);
							UCSROBDDToolBox::prune_lower_elements (&Graph, &Stack, Y);
						}
						else  // Proposition 3.2
						{
							UCSROBDDToolBox::update_upper_restriction (RU, Y->vertex);
							Y->upper_flag->set_empty_subset ();
							X->upper_flag->remove_element (i);
							UCSROBDDToolBox::prune_upper_elements (&Graph, &Stack, Y);
						}
					}

				} // if X != NULL, therefore X is an unvisited adjacent

			}
			while ((X != NULL) && (Y->vertex->cost < X->vertex->cost));

			// Pruning that applies Proposition 3.3
			//
			if ((Y->lower_flag->is_empty ()) && (! RL->contains (Y->vertex)) )
			{
				UCSROBDDToolBox::update_lower_restriction (RL, Y->vertex);
				UCSROBDDToolBox::prune_lower_elements (&Graph, &Stack, Y);
			}

			// Pruning that applies Proposition 3.4
			//
			if ((Y->upper_flag->is_empty ()) && (! RU->contains (Y->vertex)) )
			{
				UCSROBDDToolBox::update_upper_restriction (RU, Y->vertex);
				UCSROBDDToolBox::prune_upper_elements (&Graph, &Stack, Y);
			}

			// If the node is dead then it is removed from the graph
			//
			if ((Y->upper_flag->is_empty ()) && (Y->lower_flag->is_empty ()))
			{
				Stack.remove (Y);
				Graph.erase (Y->vertex->print_subset ());
				delete_node (Y);
			}

		} // while (! Stack.size () > 0)

		// "Remove graph" subroutine
		//
		for (it = Graph.begin (); it != Graph.end (); it++)
		{
			if (it->second->upper_flag->is_empty ())
				UCSROBDDToolBox::update_lower_restriction (RL, it->second->vertex);
			else if (it->second->lower_flag->is_empty ())
				UCSROBDDToolBox::update_upper_restriction (RU, it->second->vertex);
			// delete the removed node
			delete_node (it->second);
			// remove the node from the graph
			Graph.erase (it);
		}
	}


	Node * select_an_unvisited_adjacent
	 (map<string, Node *> * Graph, ROBDD * RL, ROBDD * RU, Node * Y, unsigned int * i)
	{
		unsigned int direction;
		Node * N;
		ElementSet * set = Y->vertex->get_set_that_contains_this_subset ();
		ElementSubset X ("", set);

		while (! Y->unverified->is_empty ())
		{
			// here we can put any criterion to the selection of adjacent elements
			// (for instance, preference for subsets of lower cardinality)
			*i = Y->unverified->remove_random_element ();

			// selection of an element that is either upper or lower adjacent to A->vertex
			X.copy (Y->vertex);
			if (Y->vertex->has_element (*i))
			{
				direction = 1;           // top-down and X is lower adjacent to Y
				X.remove_element (*i);
			}
			else
			{
				direction = 0;          // bottom-up and X is upper adjacent to Y
				X.add_element (*i);
			}

		    if ((Graph->find (X.print_subset ()) == Graph->end () ) &&
		    	(! RL->contains (&X)) && (! RU->contains (&X)) )
			{
				// if X belongs to the search space AND it is not contained
				// in a node of the graph, then X is an unvisited adjacent to
				// Y, therefore a node N such that N[vertex] = X is returned.
				N = create_node (&X);
				return N;
			}

			if ((direction == 1) && (RL->contains (&X)) ) // X is lower adjacent to Y[vertex]
				Y->lower_flag->remove_element (*i);

			if ((direction == 0) && (RU->contains (&X)) ) // X is upper adjacent to Y[vertex]
				Y->upper_flag->remove_element (*i);

		} // while Y has adjacent elements to Y->vertex to explore

		               // if there are no more adjacent elements to Y->vertex to explore,
		return NULL;   // then Y has no more unvisited adjacent and NULL is returned.
	}

	void prune_lower_elements (map<string, Node *> * Graph, list<Node *> * Stack, Node * A)
	{
		map<string, Node *>::iterator it;

		for (it = Graph->begin (); it != Graph->end ();)
			if ((A->vertex->contains (it->second->vertex)) &&
				(! A->vertex->is_equal (it->second->vertex)))
			{
				// remove the node from the stack
				Stack->remove (it->second);
				// delete the removed node
				delete_node (it->second);
				// remove the node from the graph
				Graph->erase (it++);
			}
			else
				it++;
	}


	void prune_upper_elements (map<string, Node *> * Graph, list<Node *> * Stack, Node * A)
	{
	 	map<string, Node *>::iterator it;

		for (it = Graph->begin (); it != Graph->end ();)
			if ((A->vertex->is_contained_by (it->second->vertex)) &&
				(! A->vertex->is_equal (it->second->vertex)))
			{
				// remove the node from the stack
				Stack->remove (it->second);
				// delete the removed node
				delete_node (it->second);
				// remove the node from the graph
				Graph->erase (it++);
			}
			else
				it++;
	}


	UCSROBDDToolBox::Node * create_node (ElementSubset * X)
	{
		Node * N = new Node;
		ElementSet * set = X->get_set_that_contains_this_subset ();
		N->vertex = new ElementSubset ("", set);
		N->vertex->copy (X);
		N->unverified = new ElementSubset ("", set);
		N->unverified->set_complete_subset ();
		N->lower_flag = new ElementSubset ("", set);
		N->lower_flag->copy (X);
		N->upper_flag = new ElementSubset ("", set);
		N->upper_flag->copy (X);
		N->upper_flag->set_complement_subset ();
		return N;
	}


	void delete_node (Node * N)
	{
		delete N->vertex;
		delete N->unverified;
		delete N->lower_flag;
		delete N->upper_flag;
		delete N;
	}


	bool list_has_vertex (list<Node *> * List, ElementSubset * X)
	{
		list<Node *>::iterator it;
		for (it = List->begin (); it != List->end (); it++)
			if ((*it)->vertex->is_equal (X))
				return true;
		return false;
	}


} // end of namespace


