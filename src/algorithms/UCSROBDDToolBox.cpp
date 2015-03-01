//
// UCurveToolBox.cpp -- implementation of the namespace "UCurveToolBox".
//
//    This file is part of the featsel program
//    Copyright (C) 2010  Marcelo S. Reis
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "UCSROBDDToolBox.h"


namespace UCurveToolBox
{
	ElementSubset * get_minimal_subset (ROBDD * R, ElementSet * a_set)
	{
		return NULL;
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
		return NULL;
	}


	Node * select_an_unvisited_adjacent
	 (map<string, Node *> * Graph, Collection * R, Node * Y, unsigned int * i)
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


	UCurveToolBox::Node * create_node (ElementSubset * X)
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


