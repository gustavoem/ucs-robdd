#include "GeneticOrdering.h"

GeneticOrdering::GeneticOrdering (ROBDD * robdd, unsigned int pop_size, 
	unsigned int solution_size)
{
	population_size = pop_size;
	this->solution_size = solution_size;
	R = robdd;
	solutions = (OrderingNode **) malloc (population_size * sizeof (OrderingNode *));
	
	for (unsigned int i = 0; i < population_size; i++)
		solutions[i] = new OrderingNode (robdd->get_element_set (), robdd->get_log ());

	// sort solutions by normalized fitness (?)
	normalize_fitness ();

	cout << "população inicial:\n";
	for (unsigned int i = 0; i < population_size; i++)
	{
		cout << "\nsolução " << i << ":\n";
		unsigned int * permutation = solutions[i]->get_ordering ();
		for (unsigned int x = 0; x < solution_size; x++)
			cout << permutation[x] << " ";
		cout << "normalized_fitness: " << solutions[i]->get_normalized_fitness ();
	}
	cout.flush ();
}


void GeneticOrdering::selection ()
{
	return;
}


void GeneticOrdering::normalize_fitness ()
{
	// fitness funciton: f(R) = 1 / cardinality (R);
	double total_fitness = 0;
	for (unsigned int i = 0; i < population_size; i++)
		total_fitness += solutions[i]->get_robdd ()->get_cardinality ();

	for (unsigned int i = 0; i < population_size; i++) {
		OrderingNode * node = solutions[i];
		unsigned int rsize = node->get_robdd ()->get_cardinality ();
		node->set_normalized_fitness (rsize / total_fitness);
	}
}


void GeneticOrdering::accumulate_fitness ()
{
	double accumulate = 0;
	for (unsigned int i = 0; i < population_size; i++)
	{
		accumulate += solutions[i]->get_normalized_fitness ();
		solutions[i]->set_accumulated_fitness (accumulate);
	}
}