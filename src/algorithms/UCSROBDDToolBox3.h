#ifndef UCSROBDDTOOLBOX3_H_
#define UCSROBDDTOOLBOX3_H_

#include "../ROBDD.h"
#include "../CostFunction.h"
#include "../Collection.h"


namespace UCSROBDDToolBox3
{
	//
	// Node data structure
	//
	struct MyNode
	{
		ElementSubset * vertex,      // the subset contained in the node
					  * unverified;  // the unverified elements of vertex
	};

	typedef struct MyNode Node;

	


	// Receives a subset A, a collection of restrictions and add A into the latter.
	//
	void update_lower_restriction(ROBDD *, ElementSubset *);


	// Receives a subset A, a collection of restrictions and add A into the latter.
	//
	void update_upper_restriction(ROBDD *, ElementSubset *);


	// Partial pruning minima exhausting subroutines
	//

	// DFS subroutine
	//
	void DFS (Node *, Collection *, ROBDD *, CostFunction *);


	// Deletes the content of a node; it assumes that all variables are pointers to
	// elements that were actually created.
	//
	void delete_node (Node *);


	// Creates a node, containing the ElementSubset X.
	// It returns a pointer to the new node.
	//
	Node * create_node (ElementSubset * X);


	// Receives the collections of restrictions, a graph, and a node M.
	//
	// Returns:
	// - a node N such that N[vertex] is an unvisited adjacent to the node's element
	// - NULL, if there are no such X (in this case, the value of the integer doesn't care).
	//
	Node * select_an_unvisited_adjacent (ROBDD *, Node *, unsigned int *);


	// Returns true if a given vertex belongs to a node list, and false otherwise.
	//
	bool list_has_vertex (list<Node *> *, ElementSubset *);


} // end of namespace

#endif /* UCSROBDDTOOLBOX3_H_ */
