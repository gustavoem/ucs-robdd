#include "UCSROBDDToolBox.h"


namespace UCSROBDDToolBox
{
	ElementSubset * get_minimal_subset (ROBDD * R, ElementSet * a_set)
	{
		ElementSubset * A, B ("", a_set);
		unsigned int i;

		B.set_complete_subset ();
		if (R->contains (&B))
			return NULL;
		else
		{
			A = new ElementSubset ("", a_set);
			A->set_complete_subset ();
			while (! B.is_empty ())
			{
				i = B.remove_random_element ();
				A->remove_element (i);
				if (R->contains (A))
					A->add_element (i);
			}
			return A;
		}
	}


	ElementSubset * get_maximal_subset (ROBDD * R, ElementSet * a_set)
	{
		return NULL;
	}


	void update_lower_restriction (ROBDD * R, ElementSubset * A)
	{
		return;
	}


	void update_upper_restriction (ROBDD * R, ElementSubset * A)
	{
		return;
	}


	void DFS (Node * M, Collection * L, Collection * R, CostFunction * c,
			  unsigned int * max_graph_size)
	{
		return;
	}


	Node * select_an_unvisited_adjacent (map<string, Node *> * Graph, Collection * R, Node * Y, unsigned int * i)
	{
		return NULL; 
	}

	void prune_lower_elements (map<string, Node *> * Graph, list<Node *> * Stack, Node * A)
	{
		map<string, Node *>::iterator it;

		for (it = Graph->begin (); it != Graph->end (); it++)
			if ((A->vertex->contains (it->second->vertex)) &&
				(! A->vertex->is_equal (it->second->vertex)))
			{
				// remove the node from the stack
				Stack->remove (it->second);
				// delete the removed node
				delete_node (it->second);
				// remove the node from the graph
				Graph->erase (it);
			}
	}


	void prune_upper_elements (map<string, Node *> * Graph, list<Node *> * Stack, Node * A)
	{
		map<string, Node *>::iterator it;

		for (it = Graph->begin (); it != Graph->end (); it++)
			if ((A->vertex->is_contained_by (it->second->vertex)) &&
				(! A->vertex->is_equal (it->second->vertex)))
			{
				// remove the node from the stack
				Stack->remove (it->second);
				// delete the removed node
				delete_node (it->second);
				// remove the node from the graph
				Graph->erase (it);
			}
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


