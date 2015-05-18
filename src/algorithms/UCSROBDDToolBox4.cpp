#include "UCSROBDDToolBox4.h"


namespace UCSROBDDToolBox4
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
		unsigned int i;
		Node * Y, * X = NULL;
		Y = M;
		L->add_subset (Y->vertex);
		do
		{
			X = select_an_unvisited_adjacent (R, Y, &i);
			cout.flush();
			if (X != NULL)
			{
				int direction;
				if (X->vertex->contains (Y->vertex))
					direction = 0;
				else
					direction = 1;

				X->vertex->cost = c->cost (X->vertex);

				if (X->vertex->cost < Y->vertex->cost)
				{
					L->add_subset (X->vertex);
					if (direction)
					{
						UCSROBDDToolBox4::update_upper_restriction (R, Y->vertex);
					}
					else
					{
						UCSROBDDToolBox4::update_lower_restriction (R, Y->vertex);
					}
					delete Y;
					Y = X;
					i = 0;
				}
				else
					i++;
			}
		} while (X != NULL);
		UCSROBDDToolBox4::update_upper_restriction (R, Y->vertex);
		UCSROBDDToolBox4::update_lower_restriction (R, Y->vertex);
		delete Y;
	} 

	Node * select_an_unvisited_adjacent (ROBDD * R, Node * Y, unsigned int * i)
	{
		ElementSet * set = Y->vertex->get_set_that_contains_this_subset ();
		ElementSubset X ("", set);
		
		while (! Y->unverified->is_empty () && *i < set->get_set_cardinality ())
		{
			Y->unverified->remove_element (*i);
			X.copy (Y->vertex);
			if (Y->vertex->has_element (*i))
				X.remove_element (*i); // top-down and X is lower adjacent to Y
			else
				X.add_element (*i);    // bottom-up and X is upper adjacent to Y

			if (!R->contains (&X))
				return create_node (&X);
			else
				(*i)++;

		} // while Y has adjacent elements to Y->vertex to explore

					   // if there are no more adjacent elements to Y->vertex to explore,
		return NULL;   // then Y has no more unvisited adjacent and NULL is returned.
	}


	UCSROBDDToolBox4::Node * create_node (ElementSubset * X)
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


