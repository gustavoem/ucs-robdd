#ifndef ORDERING_NODE_H_
#define ORDERING_NODE_H_

#include "ROBDD.h"

class ROBDD; /* this was made to solve cyclic dependency of robdd and GeneticOrdering*/

class OrderingNode
{

		ROBDD * robdd;
		double normalized_fitness; 			// probability of begin selected in selection
		double accumulate_fitness;          // probability of choosing any element with 
											// 	fitness greater or equal to 
											// 	normalized_fitness


private:

	// The node's variable order
	//
	unsigned int * permutation; 


	// Size of the solutions
	//
	unsigned int solution_size;


	// Creates a single random solution
	//
	unsigned int * randomize ();


	// Makes crossovers in solutions
	//
	void recombine_to (OrderingNode *);

	// Mutate solutions
	//
	void mutate ();

	// Creates the ROBDD using the solution 
	//
	void build_robdd (OrderingNode *);


	// Shuffle solution_size elements from an individual
	//
	void shuffle_individual (unsigned int *);


public:

	OrderingNode ();
	
};

#endif /* ORDERING_H__NODE */
