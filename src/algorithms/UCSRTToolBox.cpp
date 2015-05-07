#include "UCSRTToolBox.h"


namespace UCSRTToolBox
{
	


	void update_lower_restriction (ROBDD * R, Collection * RL, ElementSubset * A)
	{
		cout << "Adicionado intervalo [0, " << A->print_subset () << "\b]" << endl;
		R->add_interval (A, false);
		if (! RL->lower_covers (A)){
			RL->remove_lower_covered_subsets (A);
			RL->add_subset (A);
		}
	}


	void update_upper_restriction (ROBDD * R, Collection * RU, ElementSubset * A)
	{
		cout << "Adicionado intervalo [" << A->print_subset () << ", S]" << endl;
		R->add_interval (A, true);
		if (!RU->upper_covers (A))
		{
			RU->remove_upper_covered_subsets (A);
			RU->add_subset (A);
		}
	}


	void DFS (Node * M, Collection * L, ROBDD * R, Collection * RL, Collection * RU, 
		CostFunction * c, unsigned int * max_graph_size)
	{
		unsigned int direction, i;
		Node * Y, * X = NULL;
		list<Node *> Stack;
		map<string, Node *> Graph;
		map<string, Node *>::iterator it;

		Stack.push_back (M);
		Graph.insert (pair<string, Node *> (M->vertex->print_subset (), M));
		L->add_subset (M->vertex);

		while (Stack.size () > 0)
		{
			Y = Stack.back ();

			do
			{
				X = select_an_unvisited_adjacent (&Graph, R, RL, RU, Y, &i);

				if (X == NULL)  // i.e., if Y has no unvisited adjacent element
				{
					Stack.remove (Y);   // Y can't be directly popped because some
                                        // nodes might have be inserted over it.
				}
				else
				{
					if (R->contains (X->vertex) && (!RL->lower_covers (X->vertex)) && (!RU->upper_covers (X->vertex)))
					{
						cout << "* Exitem elementos (" << X->vertex->print_subset() << ") da robdd que nao estao na colleciton" << endl;
						cout.flush ();
						exit (1);
					}
					if ((RL->lower_covers (X->vertex) || RU->upper_covers (X->vertex)) && (!R->contains (X->vertex)))
					{
						cout << "* Existem elementos de collection (" << X->vertex->print_subset() << ") que nao estao na robdd" << endl;
						cout.flush ();
						exit (1);
					}

					Stack.push_back (X);

					// insert X into the graph
					Graph.insert (pair<string, UCSRTToolBox::Node *> (X->vertex->print_subset (), X));

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
							UCSRTToolBox::update_upper_restriction (R, RU, X->vertex);
							X->upper_flag->set_empty_subset ();
							Y->upper_flag->remove_element (i);
							UCSRTToolBox::prune_upper_elements (&Graph, &Stack, X);
						}
						else  // Proposition 3.1
						{
							UCSRTToolBox::update_lower_restriction (R, RL, X->vertex);
							X->lower_flag->set_empty_subset ();
							Y->lower_flag->remove_element (i);
							UCSRTToolBox::prune_lower_elements (&Graph, &Stack, X);
						}
					}
					else if (X->vertex->cost < Y->vertex->cost)
					{
						if (direction == 0)  // Proposition 3.1
						{
							UCSRTToolBox::update_lower_restriction (R, RL, Y->vertex);
							Y->lower_flag->set_empty_subset ();
							X->lower_flag->remove_element (i);
							UCSRTToolBox::prune_lower_elements (&Graph, &Stack, Y);
						}
						else  // Proposition 3.2
						{
							UCSRTToolBox::update_upper_restriction (R, RU, Y->vertex);
							Y->upper_flag->set_empty_subset ();
							X->upper_flag->remove_element (i);
							UCSRTToolBox::prune_upper_elements (&Graph, &Stack, Y);
						}
					}

				} // if X != NULL, therefore X is an unvisited adjacent

			}
			while ((X != NULL) && (Y->vertex->cost < X->vertex->cost));

			// Pruning that applies Proposition 3.3
			//
			if ((Y->lower_flag->is_empty ()) && (! R->contains (Y->vertex)) )
			{
				UCSRTToolBox::update_lower_restriction (R, RL, Y->vertex);
				UCSRTToolBox::prune_lower_elements (&Graph, &Stack, Y);
			}

			// Pruning that applies Proposition 3.4
			//
			if ((Y->upper_flag->is_empty ()) && (! R->contains (Y->vertex)) )
			{
				UCSRTToolBox::update_upper_restriction (R, RU, Y->vertex);
				UCSRTToolBox::prune_upper_elements (&Graph, &Stack, Y);
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
		for (it = Graph.begin (); it != Graph.end (); )
		{
			if (it->second->upper_flag->is_empty ())
				UCSRTToolBox::update_lower_restriction (R, RL, it->second->vertex);
			else if (it->second->lower_flag->is_empty ())
				UCSRTToolBox::update_upper_restriction (R, RU, it->second->vertex);
			// delete the removed node
			delete_node (it->second);
			// remove the node from the graph
			Graph.erase (it++);
		}
	}


	Node * select_an_unvisited_adjacent (map<string, Node *> * Graph, ROBDD * R,
	 Collection * RL, Collection * RU, Node * Y, unsigned int * i)
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
		    	(! R->contains (&X)))
			{
				// if X belongs to the search space AND it is not contained
				// in a node of the graph, then X is an unvisited adjacent to
				// Y, therefore a node N such that N[vertex] = X is returned.
				N = create_node (&X);
				return N;
			}


			if ((R->contains (&X)) && (!RL->lower_covers (&X)) && (!RU->upper_covers (&X)))
			{
				cout << "Exitem elementos da robdd que nao estao na colleciton" << endl;
				cout.flush ();
				exit (1);
			}
			if ((RL->lower_covers (&X) || RU->upper_covers (&X)) && (!R->contains (&X)))
			{
				cout << "Existem elementos de collection que nao estao na robdd" << endl;
				cout.flush ();
				exit (1);
			}

			if ((direction == 1) && (RL->lower_covers (&X)) ) // X is lower adjacent to Y[vertex]
				Y->lower_flag->remove_element (*i);

			if ((direction == 0) && (RU->upper_covers (&X)) ) // X is upper adjacent to Y[vertex]
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


	UCSRTToolBox::Node * create_node (ElementSubset * X)
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


