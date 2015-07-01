#ifndef GENETICORDERING_H_
#define GENETICORDERING_H_

#include "ROBDD.h"
#include "Element.h"


class GeneticOrdering
{
	//
	// Data structure for solutions
	//
	struct Node
	{
		Element ** permutation; // the node's variable order
		ROBDD * robdd;
		float selectp; 			// probability of begin selected in selection

	};

	typedef struct Node OrderingNode;


private:

	// List of solutions
	//
	OrderingNode * solutions;
	

	// Creates an initial population filling the solutions array
	//
	void start_population ();

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

	GeneticOrdering (ROBDD *);

	// Gives a good ordering using a Genetic Algorithm Heuristic for 
	Vertex * reorder ();

};

#endif /* GENETICORDERING_H_ */
