#ifndef UCSROBDDTOOLBOX5_H_
#define UCSROBDDTOOLBOX5_H_

#include "../ROBDD.h"
#include "../CostFunction.h"
#include "../Collection.h"


namespace UCSROBDDToolBox5
{
	//
	// Node data structure
	//
	struct MyNode
	{
		ElementSubset * vertex,      // the subset contained in the node
					  * upper_unverified, // upper adjacent unverified subsets
					  * lower_unverified; // lower adjacent unverified subsets
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


	// Visits a node X from node Y
	// If cost(X) > cost (Y) nothing happens.
	// Otherwise, X is added to the collection L and if direction == 1 (Y covers X) we
	// add the interval [Y, S] to restrictions; if direction == 0 we add the interval
	// [0, Y] to restrictions.
	// 
	void visit_adjacent (ROBDD *, Collection *, Node **, Node *, unsigned int direction,
						CostFunction *);


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
	// - a node N such that N[vertex] = X is an unvisited adjacent to the node's element
	// - if direction = 0 returns a upper adjacent; if direction = 1 returns a lower
	// adjacent
	// - NULL, if there are no such X (in this case, the value of the integer doesn't care).
	//
	Node * select_ul_unvisited_adjacent (ROBDD *, Node *, unsigned int);


	// Returns true if a given vertex belongs to a node list, and false otherwise.
	//
	bool list_has_vertex (list<Node *> *, ElementSubset *);


} // end of namespace

#endif /* UCSROBDDTOOLBOX5_H_ */
