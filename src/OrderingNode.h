#ifndef ORDERINGNODE_H_
#define ORDERINGNODE_H_

#include "ElementSet.h"
#include "ElementSubset.h"
#include "GAROBDD.h"


class OrderingNode
{

private:


	// The ROBDD with the corresponding variable Ordering
	//
	GAROBDD * garobdd;

	
	// Probability of begin selected in selection
	//
	double normalized_fitness;

	
	// Probability of choosing any element with fitness greater or equal to 
	// normalized_fitness
	//
	double accumulated_fitness;          


	// The node's variable order
	//
	unsigned int * permutation; 


	// Size of the solutions
	//
	unsigned int size;


	// Creates a single random solution
	//
	unsigned int * randomize ();


	// Makes crossovers in solutions
	//
	void recombine_to (OrderingNode *);


	// Mutate solutions
	//
	void mutate ();


	// Shuffle solution_size elements from an individual
	//
	void shuffle_individual ();


public:

	OrderingNode (ElementSet *, list <pair <bool, ElementSubset *> > *);


	unsigned int * get_ordering ();


	GAROBDD * get_robdd ();


	double get_normalized_fitness ();


	void set_normalized_fitness (double);


	double get_accumulated_fitness ();


	void set_accumulated_fitness (double);


	void print_solution ();
	
};

#endif /* ORDERINGNODE_H_ */
