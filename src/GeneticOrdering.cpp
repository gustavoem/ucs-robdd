#include "GeneticOrdering.h"

GeneticOrdering::GeneticOrdering (ROBDD * robdd, unsigned int pop_size, 
	unsigned int solution_size)
{
	population_size = pop_size;
	this->solution_size = solution_size;
	R = robdd;
	solutions = (OrderingNode **) malloc (population_size * sizeof (OrderingNode *));
	cout << "\n-------\n(GO) Ponteiros para soluções: de" << (&solutions[0]) << " até " << &solutions[population_size - 1] << endl;
	list <pair <bool, ElementSubset *> > l (robdd->get_log ());
	
	for (unsigned int i = 0; i < population_size; i++) {
		srand (time(0));
		solutions[i] = new OrderingNode (robdd->get_element_set (), &l);
		cout << "(GO) Instanciei uma solução em: " << &solutions[i] << " que aponta para: " \
		<< solutions[i] << endl;
		cout << "(GO) Endereço da solução: " << solutions[i] << endl;
		for (unsigned int x = 0; x < solution_size; x++)
		{
		 	cout << solutions[i]->get_ordering ()[x] << " ";
		}

		cout << endl;
	}

	// sort solutions by normalized fitness (?)
	normalize_fitness ();
	accumulate_fitness ();

	cout << "população inicial:\n";
	for (unsigned int i = 0; i < population_size; i++)
	{
		cout << "\nsolução " << i << ":\n";
		unsigned int * permutation = solutions[i]->get_ordering ();
		for (unsigned int x = 0; x < solution_size; x++)
			cout << permutation[x] << " ";
		cout << "normalized_fitness: " << solutions[i]->get_normalized_fitness ();
		cout << " accumulated_fitness: " << solutions[i]->get_accumulated_fitness ();
	}
	cout.flush ();

	selection ();
}


void GeneticOrdering::selection ()
{
	OrderingNode ** new_gen = 
		(OrderingNode **) malloc (population_size * sizeof (OrderingNode *));
	unsigned int ** selected_perm = 
		(unsigned int **) malloc (population_size * sizeof (unsigned int *));
	vector<double> random_sorts (population_size, 0.0);
	
	for (unsigned int i = 0; i < population_size; i++)
		random_sorts[i] = ((double) rand () / (RAND_MAX));

	sort (random_sorts.begin (), random_sorts.end ());

	cout << "\nsorted guys:\n";
	for (unsigned int i = 0; i < population_size; i++)
		cout << random_sorts[i] << " ";
}	


void GeneticOrdering::normalize_fitness ()
{
	// fitness funciton: f(R) = 1 / cardinality (R);
	double total_fitness = 0;
	// for (unsigned int i = 0; i < population_size; i++)
	// {
	// 	solutions[i]->get_robdd ()->print ();
	// 	cout << "\nCardinalidade: " << solutions[i]->get_robdd ()->get_cardinality () << endl;
	// 	total_fitness += solutions[i]->get_robdd ()->get_cardinality ();
	// }

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