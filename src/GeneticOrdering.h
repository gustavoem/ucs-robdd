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


	// A copy of the ROBDD log
	//
	list <pair <bool, ElementSubset *> > robdd_log;

	// Population size
	//
	unsigned int population_size;


	// Size of the solutions
	//
	unsigned int solution_size;


	// Selects the elements that fits best the environment and do crossing over
	// between the actual population and these elements.
	//
	void selection ();


	// Mutate solutions
	//
	void mutate_solutions ();


	// Calculates the normalized fitness of all elements from a population. The 
	// normalized fitness of a solution s is the probability of choosing s randomly
	//
	void normalize_fitness ();


	// Look at all the current solutions and update best_solution and
	// best_solution_index
	//
	void set_best_solution ();


	// Calculates, for every solution, the probability of choosing this solution
	// or any previous in OrderingNode ** solutions.
	//
	void accumulate_fitness ();


	//	Recalculate fitness of all solutions
	//
	void recalculate_fitness ();
	

	unsigned int best_solution_index;


	unsigned int best_solution;


public:

	GeneticOrdering (ROBDD *);

	virtual ~GeneticOrdering ();

	// Gives a good ordering using a Genetic Algorithm Heuristic for 
	//
	unsigned int * reorder ();
	
};

#endif /* GENETICORDERING_H_ */
