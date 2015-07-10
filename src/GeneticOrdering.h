#ifndef GENETICORDERING_H_
#define GENETICORDERING_H_

#include "ROBDD.h"
#include "Element.h"

class ROBDD; /* this was made to solve cyclic dependency of robdd and GeneticOrdering*/

class GeneticOrdering
{
	//
	// Data structure for solutions
	//
	struct Node
	{
		unsigned int * permutation; // the node's variable order
		ROBDD * robdd;
		float selectp; 			// probability of begin selected in selection

	};

	typedef struct Node OrderingNode;


private:

	// List of solutions
	//
	OrderingNode * solutions;

	// Original ROBDD
	//
	ROBDD * R;

	// Population size
	//
	unsigned int population_size;


	// Size of the solutions
	//
	unsigned int solution_size;


	// Creates a single random solution
	//
	unsigned int * random_indivudual ();


	// Selects the elements that fits best the environment
	//
	void selection ();

	// Makes crossovers in solutions
	//
	void recombine ();

	// Mutate solutions
	//
	void mutate ();

	// Creates the ROBDD using the solution 
	//
	void build_robdd (OrderingNode *);


public:

	GeneticOrdering (ROBDD *, unsigned int, unsigned int);

	// Gives a good ordering using a Genetic Algorithm Heuristic for 
	Vertex * reorder ();

};

#endif /* GENETICORDERING_H_ */
