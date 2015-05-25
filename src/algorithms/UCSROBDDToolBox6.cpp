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

		while (!Y->upper_unverified->is_empty () || !Y->lower_unverified->is_empty ())
		{
			X = select_ul_unvisited_adjacent (R, Y, direction);
			visit_adjacent (R, L, &Y, X, direction, c, &upper_greater, &lower_greater);
			direction = 1 - direction;
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
				lower_greater->clear ();
				UCSROBDDToolBox6::update_upper_restriction (R, (*Y)->vertex);
			}
			else 		   // X covers Y
			{
				restrict_visited_adjacents (R, upper_greater, direction);
				upper_greater->clear ();
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
			if (direction)
				update_lower_restriction (R, l->back ());
			else
				update_upper_restriction (R, l->back ());
			l->pop_back ();
		}
	}

	Node * select_ul_unvisited_adjacent (ROBDD * R, Node * Y, unsigned int dir)
	{
		if ((dir == 1 && Y->lower_unverified->is_empty ()) ||
			(dir == 0 && Y->upper_unverified->is_empty ()))
			return NULL;
		ElementSet * set = Y->vertex->get_set_that_contains_this_subset ();
		ElementSubset X ("", set);
		X.copy (Y->vertex);
		unsigned int elm_index;

		if (dir == 0) // we are searching for a upper adjacent element
		{
			do 
			{
				elm_index = Y->upper_unverified->remove_random_element ();
				if (X.add_element (elm_index) && !R->contains (&X))
					return create_node (&X);
				else
					X.remove_element (elm_index);
			} while (elm_index != set->get_set_cardinality ());
		}
		else
		{
			do 
			{
				elm_index = Y->lower_unverified->remove_random_element ();
				if (X.remove_element (elm_index) && !R->contains (&X))
					return create_node (&X);
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
		
		N->upper_unverified = new ElementSubset ("", set);
		N->upper_unverified->copy (X);
		N->upper_unverified->set_complement_subset ();

		N->lower_unverified = new ElementSubset ("", set);
		N->lower_unverified->copy (X);

		return N;
	}


	void delete_node (Node * N)
	{
		delete N->vertex;
		delete N->upper_unverified;
		delete N->lower_unverified;
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


