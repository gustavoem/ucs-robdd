#ifndef UCSROBDDTOOLBOX_H_
#define UCSROBDDTOOLBOX_H_

#include "../ROBDD.h"
#include "../CostFunction.h"
#include "../Collection.h"


namespace UCSROBDDToolBox
{
	//
	// Node data structure
	//
	struct MyNode
	{
		ElementSubset * vertex,      // the subset contained in the node
					  * unverified,  // the unverified elements of vertex
					  * upper_flag,  // "upper" and "lower" restriction flags
					  * lower_flag;
	};

	typedef struct MyNode Node;


	// Returns a maximal subset, say X, with the following properties:
	// - X does not contain a subset from this collection;
	// - there is no subset Y | Y contains X and Y does not contain a subset from this collection.
	//
	ElementSubset * get_maximal_subset (ROBDD *, ElementSet *);


	// Returns a minimal subset, say X, with the following properties:
	// - X is not contained by a subset from this collection;
	// - there is no subset Y | Y is contained by X and Y is not contained by a subset
	//   from this collection.
	//
	ElementSubset * get_minimal_subset (ROBDD *, ElementSet *);


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
	void DFS (Node *, Collection *, ROBDD *, ROBDD*, CostFunction *, unsigned int *);


	// Prunes the elements of the minima exhausting graph that were lower removed from
	// the search space by the ElementSubset from the Node A.
	//
	void prune_lower_elements (map<string, Node *> *, list<Node *> *, Node *);


	// Prunes the elements of the minima exhausting graph that were upper removed from
	// the search space by the ElementSubset from the Node A.
	//
	void prune_upper_elements (map<string, Node *> *, list<Node *> *, Node *);


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
	Node * select_an_unvisited_adjacent (map<string, Node *> *, ROBDD *, ROBDD *, Node *, unsigned int *);


	// Returns true if a given vertex belongs to a node list, and false otherwise.
	//
	bool list_has_vertex (list<Node *> *, ElementSubset *);


} // end of namespace

#endif /* UCSROBDDTOOLBOX_H_ */
