#include "GeneticOrdering.h"

GeneticOrdering::GeneticOrdering (ROBDD * robdd, unsigned int pop_size, 
	unsigned int solution_size)
{
	population_size = pop_size;
	this->solution_size = solution_size;
	R = robdd;
	solutions = (OrderingNode *) malloc (population_size * sizeof (OrderingNode));
	
	for (unsigned int i = 0; i < population_size; i++)
	{
		OrderingNode x;
		solutions[i].permutation = x;
	}

	normalize_fitness ();

	// std::vector<OrderingNode> v (solutions, solutions + population_size);
	// sort (v.begin (), v.end ());

	cout << "população inicial:\n";
	for (unsigned int i = 0; i < population_size; i++)
	{
		cout << "\nsolução " << i << ":\n";
		for (unsigned int x = 0; x < solution_size; x++)
			cout << solutions[i].permutation[x] << " ";
		cout << "normalized_fitness: " << solutions[i].normalized_fitness;
	}
	cout.flush ();
}


/*unsigned int * GeneticOrdering::random_indivudual ()
{
	unsigned int * sol = (unsigned int *) malloc (solution_size * sizeof (unsigned int));
	
	for (unsigned int i = 0; i < solution_size; i++)
		sol[i] = i;

	shuffle_individual (sol);
	return sol;
}*/


/*void GeneticOrdering::shuffle_individual (unsigned int * sol)
{
	for (unsigned int n = solution_size; n > 0; n--)
	{
		// here sol[n - 1, ..., solution_size - 1] is a random shuffle
		unsigned int j = ((unsigned int) rand () % n);   // random number between 0 and n - 1
		unsigned int aux = sol[j];
		sol[j] = sol[n - 1];
		sol[n - 1] = aux;
	}
}*/


void GeneticOrdering::selection ()
{
	return;
}


/*void GeneticOrdering::normalize_fitness ()
{
	// fitness funciton: f(R) = 1 / cardinality (R);
	double total_fitness = 0;
	cout << population_size;
	for (unsigned int i = 0; i < population_size; i++)
	{
		build_robdd (&solutions[i]);
		double fr = 1.0 / solutions[i].robdd->get_cardinality ();
		solutions[i].normalized_fitness = fr;
		total_fitness += fr;
	}

	for (unsigned int i = 0; i < population_size; i++)
		solutions[i].normalized_fitness /= total_fitness;
}*/


void GeneticOrdering::accumulate_fitness ()
{
	double accumulate = 0;
	for (unsigned int i = 0; i < population_size; i++)
	{
		accumulate += solutions[i].normalized_fitness;
		solutions[i].accumulate_fitness = accumulate;
	}
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
	list <pair <bool, ElementSubset *> > log_of_intervals = R->get_log ();

	node->robdd = new ROBDD (R->get_element_set (), node->permutation);
	for (list <pair <bool, ElementSubset *> >::iterator it = log_of_intervals.begin (); 
		it != log_of_intervals.end (); it++)
		node->robdd->add_interval (it->second, it->first);
}



Vertex * GeneticOrdering::reorder ()
{
	return NULL;
}