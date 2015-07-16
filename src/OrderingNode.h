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

	unsigned int robdd_size;
	
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


	// Shuffle solution_size elements from an individual
	//
	void shuffle_individual ();



public:

	OrderingNode (ElementSet *, list <pair <bool, ElementSubset *> > *);


	virtual ~OrderingNode ();


	// Makes crossovers in solutions
	//
	void recombine_to (unsigned int *);


	void recalculate_fitness ();


	// Performs a MUT, an exchange of two randomly chosen variables in the permutation
	//
	void mut ();


	// Performs 2 MUT
	//
	void mut_twice ();


	// Performs the exchange of the i-th and i + 1 th variables, with i chosen randomly
	//
	void neighbour_mut ();


	unsigned int * get_ordering ();


	GAROBDD * get_robdd ();

	// Returns the cardinality of the robdd associated to that solution
	//
	unsigned int get_robdd_size ();


	double get_normalized_fitness ();


	void set_normalized_fitness (double);


	double get_accumulated_fitness ();


	void set_accumulated_fitness (double);


	void print_solution ();
	
};

#endif /* ORDERINGNODE_H_ */
