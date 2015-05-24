#include "UCSROBDDToolBox6.h"


namespace UCSROBDDToolBox6
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
		unsigned int direction = 0;
		Node * Y, * X = NULL;
		Y = M;
		L->add_subset (Y->vertex);
		list<ElementSubset *> upper_greater;
		list<ElementSubset *> lower_greater;
		
		X = select_ul_unvisited_adjacent (R, Y, 0);

		while (X != NULL)
		{
			visit_adjacent (R, L, &Y, X, direction, c, &upper_greater, &lower_greater);
			direction = 1 - direction;
			
			X = select_ul_unvisited_adjacent (R, Y, direction);
			if (X == NULL)
			{
				direction = 1 - direction;
				X = select_ul_unvisited_adjacent (R, Y, direction);
			}
		}

		UCSROBDDToolBox6::update_upper_restriction (R, Y->vertex);
		UCSROBDDToolBox6::update_lower_restriction (R, Y->vertex);
		delete Y;
	} 

	void visit_adjacent (ROBDD * R, Collection * L, Node ** Y, Node * X, 
						 unsigned int direction, CostFunction *c,
						 list<ElementSubset *> * upper_greater, 
						 list<ElementSubset *> * lower_greater)
	{
		if (X == NULL || (*Y) == NULL)
			return;
		
		X->vertex->cost = c->cost (X->vertex);
		
		if (X->vertex->cost < (*Y)->vertex->cost)
		{
			L->add_subset (X->vertex);
			if (direction) // Y covers X
			{ 
				restrict_visited_adjacents (R, lower_greater, direction);
				upper_greater->clear ();
				UCSROBDDToolBox6::update_upper_restriction (R, (*Y)->vertex);
			}
			else 		   // X covers Y
			{
				restrict_visited_adjacents (R, upper_greater, direction);
				lower_greater->clear ();
				UCSROBDDToolBox6::update_lower_restriction (R, (*Y)->vertex);
			}

			delete (*Y);
			(*Y) = X;
		}
		else
		{
			if (X->vertex->cost > (*Y)->vertex->cost)
			{
				if (direction) // Y covers X
					lower_greater->push_back (X->vertex);
				else
					upper_greater->push_back (X->vertex);
			}
			delete X;
		}
	}

	void restrict_visited_adjacents (ROBDD * R, list<ElementSubset *> * l, unsigned int direction)
	{
		while (!l->empty ())
		{
			R->add_interval (l->back (), direction);
			l->pop_back ();
		}
	}

	Node * select_ul_unvisited_adjacent (ROBDD * R, Node * Y, unsigned int dir)
	{
		ElementSet * set = Y->vertex->get_set_that_contains_this_subset ();
		ElementSubset X ("", set);
		X.copy (Y->vertex);

		unsigned int elm_index;
		
		ElementSubset upper_set ("", set);
		upper_set.copy (Y->vertex);
		upper_set.set_complement_subset ();

		ElementSubset lower_set ("", set);
		lower_set.copy (Y->vertex);

		if (dir == 0) // we are searching for a upper adjacent element
		{
			upper_set.subset_intersection (Y->unverified);
			do 
			{
				elm_index = upper_set.remove_random_element ();
				Y->unverified->remove_element (elm_index);
				if (X.add_element (elm_index) && !R->contains (&X)) 
				{
					return create_node (&X);
				}
				else
					X.remove_element (elm_index);
			} while (elm_index != set->get_set_cardinality ());

		}
		else
		{
			lower_set.subset_intersection (Y->unverified);
			do 
			{
				elm_index = lower_set.remove_random_element ();
				Y->unverified->remove_element (elm_index);
				if (X.remove_element (elm_index) && !R->contains (&X))
				{
					return create_node (&X);
				}
				else
					X.add_element (elm_index);
			} while (elm_index != set->get_set_cardinality ());

		}
		return NULL;
	}


	UCSROBDDToolBox6::Node * create_node (ElementSubset * X)
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


