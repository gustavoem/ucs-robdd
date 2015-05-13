#include "UCSROBDDToolBox3.h"


namespace UCSROBDDToolBox3
{

	void update_lower_restriction (ROBDD * R, ElementSubset * A)
	{
		R->add_interval (A, false);
	}


	void update_upper_restriction (ROBDD * R, ElementSubset * A)
	{
		R->add_interval (A, true);
	}


	void DFS (Node * M, Collection * L, ROBDD * R, CostFunction * c)
	{
		unsigned int direction, i;
		Node * Y, * X = NULL;

    	Y = M;
    	L->add_subset (Y->vertex);
    	X = UCSROBDDToolBox3::select_an_unvisited_adjacent (R, Y, &i);

		while (X != NULL)
	 	{
	 		//cout << "X: " << X->vertex->print_subset () << " Y: " << Y->vertex->print_subset () << endl;
			if (X->vertex->contains (Y->vertex))
				direction = 0;
			else
				direction = 1;

			X->vertex->cost = c->cost (X->vertex); // computes and stores c(X)

			// If the DFS criterion is attained, then X->element is stored
			//
			if (X->vertex->cost <= Y->vertex->cost)
			{
				//cout << "adding subset: " << X->vertex->print_subset () << endl;
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
					UCSROBDDToolBox3::update_upper_restriction (R, X->vertex);
					delete X;
				}
				else  // Proposition 3.1
				{
					UCSROBDDToolBox3::update_lower_restriction (R, X->vertex);
					delete X;
					}
			}
			else if (X->vertex->cost < Y->vertex->cost)
			{
				if (direction == 0)  // Proposition 3.1
				{
					UCSROBDDToolBox3::update_lower_restriction (R, Y->vertex);
					delete Y;
					Y = X;
				}
				else  // Proposition 3.2
				{
					UCSROBDDToolBox3::update_upper_restriction (R, Y->vertex);
					delete Y;
					Y = X;
				}
			}
			else
			{
				// c(X) == c(Y)
				Node * Z;
				ElementSubset ZSUB ("", X->vertex->get_set_that_contains_this_subset ());
				Node * A;
				Node * B;

				if (direction == 0) 
				{
					// X contains Y
					A = Y;
					B = X;
				}
				else
				{
					A = X;
					B = Y;
				}

				ZSUB.copy (A->vertex);
				Z = create_node (&ZSUB);

				if (Z->vertex->remove_random_element () != Z->vertex->get_set_cardinality ())
				{
					if (Z->vertex->cost > A->vertex->cost) 
					{
						UCSROBDDToolBox3::update_lower_restriction (R, A->vertex);
						delete Z;
						delete A;
						Y = B;
					}
					else
					{
						UCSROBDDToolBox3::update_upper_restriction (R, A->vertex);
						delete A;
						delete B;
						Y = Z;
					}
				}
				else
				{
					// A is the empty set
					UCSROBDDToolBox3::update_lower_restriction (R, A->vertex);
					delete Z;
					delete A;
					Y = B;
				}
			}
			X = UCSROBDDToolBox3::select_an_unvisited_adjacent (R, Y, &i);
		} // if X != NULL, therefore X is an unvisited adjacent
	    
	    // Temos que verificar se podemos fazer esta poda sem remover caras errados do espaço de busca!
	    //
	    UCSROBDDToolBox3::update_upper_restriction (R, Y->vertex);
	    UCSROBDDToolBox3::update_lower_restriction (R, Y->vertex);
	    delete Y;
	} 

	Node * select_an_unvisited_adjacent (ROBDD * R, Node * Y, unsigned int * i)
	{
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
				X.remove_element (*i); // top-down and X is lower adjacent to Y
			else
				X.add_element (*i);    // bottom-up and X is upper adjacent to Y

			if (!R->contains (&X))
      			return create_node (&X);

		} // while Y has adjacent elements to Y->vertex to explore

		               // if there are no more adjacent elements to Y->vertex to explore,
		return NULL;   // then Y has no more unvisited adjacent and NULL is returned.
	}


	UCSROBDDToolBox3::Node * create_node (ElementSubset * X)
	{
		Node * N = new Node;
		ElementSet * set = X->get_set_that_contains_this_subset ();
		N->vertex = new ElementSubset ("", set);
		N->vertex->copy (X);
		N->unverified = new ElementSubset ("", set);
		N->unverified->set_complete_subset ();
		return N;
	}


	void delete_node (Node * N)
	{
		delete N->vertex;
		delete N->unverified;
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


