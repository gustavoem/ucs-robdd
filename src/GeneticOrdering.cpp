#include "GeneticOrdering.h"


GeneticOrdering::GeneticOrdering (ROBDD * R, unsigned int pop_size, 
	unsigned int solution_size)
{
	population_size = pop_size;
	this->solution_size = solution_size;
	solutions = (OrderingNode *) malloc (population_size * sizeof (OrderingNode));
	
	for (unsigned int i = 0; i < population_size; i++)
	{
		solutions[i].permutation = random_indivudual ();
	}

	/*cout << "população inicial:\n";
	for (unsigned int i = 0; i < population_size; i++)
	{
		cout << "\nsolução " << i << ":\n";
		for (unsigned int x = 0; x < solution_size; x++)
			cout << solutions[i].permutation[x] << " ";
	}
	cout.flush ();*/
}


unsigned int * GeneticOrdering::random_indivudual ()
{
	unsigned int * sol = (unsigned int *) malloc (solution_size * sizeof (unsigned int));
	unsigned int n = solution_size;
	for (unsigned int i = 0; i < solution_size; i++)
		sol[i] = i + 1;

	for (n = solution_size; n > 0; n--)
	{
		/*here sol[n - 1, ..., solution_size - 1] is a random shuffle*/
		unsigned int j = ((unsigned int) rand () % n);   // random number between 0 and n - 1
		unsigned int aux = sol[j];
		sol[j] = sol[n - 1];
		sol[n - 1] = aux;
	}

	return sol;
}


void GeneticOrdering::selection ()
{
	return;
}


void GeneticOrdering::recombine ()
{
	return;
}


void GeneticOrdering::mutate ()
{
	return;	
}


void GeneticOrdering::build_robdd (OrderingNode * node)
{
	return;
}


Vertex * GeneticOrdering::reorder ()
{
	return NULL;
}