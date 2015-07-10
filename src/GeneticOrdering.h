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
		double normalized_fitness; 			// probability of begin selected in selection
		double accumulate_fitness;          // probability of choosing any element with 
											// 	fitness greater or equal to 
											// 	normalized_fitness

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


	// Calculates the normalized fitness of all elements from a population
	//
	void normalize_fitness ();

	// Shuffle solution_size elements from an individual
	//
	void shuffle_individual (unsigned int *);


	// Shuffle population_size elements from a population
	//
	void shuffle_population (OrderingNode *);


public:

	GeneticOrdering (ROBDD *, unsigned int, unsigned int);

	// Gives a good ordering using a Genetic Algorithm Heuristic for 
	Vertex * reorder ();

};

#endif /* GENETICORDERING_H_ */
