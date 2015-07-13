#ifndef GENETICORDERING_H_
#define GENETICORDERING_H_

#include "Element.h"
#include "global.h"
#include "OrderingNode.h"
#include "ROBDD.h"

class GeneticOrdering
{

private:

	// List of solutions
	//
	OrderingNode ** solutions;

	// Original ROBDD
	//
	ROBDD * R;

	// Population size
	//
	unsigned int population_size;


	// Size of the solutions
	//
	unsigned int solution_size;


	// Selects the elements that fits best the environment
	//
	void selection ();

	// Makes crossovers in solutions
	//
	void recombine_solutions ();

	// Mutate solutions
	//
	void mutate_solutions ();


	// Calculates the normalized fitness of all elements from a population
	//
	void normalize_fitness ();

	// Calculates the accumulate probability of choosing any element with fitness greater
	// or equal to normalized_fitness
	//
	void accumulate_fitness ();


public:

	GeneticOrdering (ROBDD *, unsigned int, unsigned int);

	// Gives a good ordering using a Genetic Algorithm Heuristic for 
	ROBDD * reorder ();

	
};

#endif /* GENETICORDERING_H_ */
