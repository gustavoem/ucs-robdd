/*
 * PosetForestSearch.h
 *
 *  Created on: Apr 6, 2011
 *      Author: marceloreis
 */

#ifndef POSET_FOREST_SEARCH_H_
#define POSET_FOREST_SEARCH_H_

#include "../global.h"
#include "../Solver.h"
#include "../ElementSubset.h"


class PosetForestSearch : public Solver
{

public:

	typedef struct MyNode
	{
		ElementSubset * vertex,
		              * adjacent;
		unsigned int leftmost;
		float cost;
	} Node;

protected:

	float bound;  // a threshold to keep the list of minima small

	Node * lower_forest_branch (map<string, Node *> *, map<string, Node *> *);

	Node * upper_forest_branch (map<string, Node *> *, map<string, Node *> *);

	void search_upper_children
	     (map<string, Node *> *, Node *, ElementSubset *, ElementSubset *);

	void search_lower_children
	     (map<string, Node *> *, Node *, ElementSubset *, ElementSubset *);

	void search_upper_root (map<string, Node *> *, ElementSubset *);

	void search_lower_root (map<string, Node *> *, ElementSubset *);

	void upper_forest_pruning (map<string, Node *> *, Node *);

	void lower_forest_pruning (map<string, Node *> *, Node *);

public:

	PosetForestSearch ();


	virtual ~PosetForestSearch ();


	// Runs the algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
	//
	void get_minima_list (unsigned int);

};

#endif /* POSET_FOREST_SEARCH_H_ */
