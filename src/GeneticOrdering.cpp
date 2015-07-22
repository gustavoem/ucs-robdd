#include "GeneticOrdering.h"

GeneticOrdering::GeneticOrdering (ROBDD * robdd)
{
	/* Parameter setting as seen in ...*/
	solution_size = robdd->get_element_set ()->get_set_cardinality ();
	if (solution_size > 40)
		population_size = 120;
	else
		population_size = solution_size * 3;

	R = robdd;
	solutions = (OrderingNode **) malloc (population_size * sizeof (OrderingNode *));
	robdd_log = robdd->get_log ();
	srand (time(0));
	for (unsigned int i = 0; i < population_size; i++) {
		srand (i);
		solutions[i] = new OrderingNode (robdd->get_element_set (), &robdd_log);
		/*cout << "(GO) Instanciei uma solução em: " << &solutions[i] << " que aponta para: " \
		<< solutions[i] << endl;
		cout << "(GO) Endereço da solução: " << solutions[i] << endl;
		for (unsigned int x = 0; x < solution_size; x++)
		 	cout << solutions[i]->get_ordering ()[x] << " ";
		cout << endl;*/
	}

	// sort solutions by normalized fitness (?)
	normalize_fitness ();
	accumulate_fitness ();
	set_best_solution ();
}


GeneticOrdering::~GeneticOrdering ()
{
	cout << "~GeneticOrdering\n";
	cout.flush();
	for (unsigned int i = 0; i < population_size; i++)
		delete solutions[i];
	free (solutions);
}

void GeneticOrdering::selection ()
{
	OrderingNode ** new_gen = 
		(OrderingNode **) malloc (population_size * sizeof (OrderingNode *));
	unsigned int ** selected_perm = 
		(unsigned int **) malloc (population_size * sizeof (unsigned int *));
	double * random_sorts = 
		(double *) malloc (population_size * sizeof (double));
	
	for (unsigned int i = 0; i < population_size; i++)
		random_sorts[i] = ((double) rand () / (RAND_MAX));
	sort (&random_sorts[0], &random_sorts[population_size]);

	// cout << "\nsorted guys:\n";
	// for (unsigned int i = 0; i < population_size; i++)
	// 	cout << random_sorts[i] << " ";

	unsigned int k = 0;
	for (unsigned int i = 0; i < population_size; i++) {
		while (solutions[k]->get_accumulated_fitness () < random_sorts[i])
			k++;
		selected_perm[i] = solutions[k]->get_ordering ();
	}

	// cout << "elementos selecionados: " << endl;
	// for (unsigned int i = 0; i < population_size; i++) {
	// 	for (unsigned int j = 0; j < solution_size; j++)
	// 		cout << selected_perm[i][j] << " ";
	// 	cout << endl;
	// }

	for (unsigned int i = 0; i < population_size; i++)
		solutions[i]->recombine_to (selected_perm[i]);
	free (new_gen);
	free (selected_perm);
	free (random_sorts);
}	




void GeneticOrdering::mutate_solutions ()
{
	bool decision = ((double) rand () / (RAND_MAX));
	if (decision < 0.15)
	{
		unsigned int i = ((unsigned int) rand () % population_size);
		solutions[i]->mut ();
	}

	decision = ((double) rand () / (RAND_MAX));
	if (decision < 0.15)
	{
		unsigned int i = ((unsigned int) rand () % population_size);
		solutions[i]->mut_twice ();
	}

	decision = ((double) rand () / (RAND_MAX));
	if (decision < 0.15)
	{
		unsigned int i = ((unsigned int) rand () % population_size);
		solutions[i]->neighbour_mut ();
	}
}


void GeneticOrdering::normalize_fitness ()
{
	// fitness funciton: f(R) = 1 / cardinality (R);
	double total_fitness = 0;
	for (unsigned int i = 0; i < population_size; i++)
	{
		// solutions[i]->get_robdd ()->print ();
		// cout << "\nCardinalidade: " << solutions[i]->get_robdd ()->get_cardinality () << endl;
		total_fitness += solutions[i]->get_robdd_size ();
	}

	for (unsigned int i = 0; i < population_size; i++) {
		OrderingNode * node = solutions[i];
		unsigned int rsize = node->get_robdd_size ();
		node->set_normalized_fitness (rsize / total_fitness);
	}
}


void GeneticOrdering::set_best_solution ()
{
	unsigned int best_index = 0;
	unsigned int best_size = solutions[0]->get_robdd_size ();

	for (unsigned int i = 1; i < population_size; i++)
	{
		unsigned int isize = solutions[i]->get_robdd_size ();
		if (isize < best_size)
		{
			best_size = isize;
			best_index = i;
		}
	}

	best_solution_index = best_index;
	best_solution = best_size;
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


void GeneticOrdering::recalculate_fitness ()
{
	for (unsigned int i = 0; i < population_size; i++)
	{
		solutions[i]->recalculate_fitness ();
	}
}


ROBDD * GeneticOrdering::reorder ()
{
	set_best_solution ();
	unsigned int old_best_size;
	OrderingNode * best_node = new OrderingNode (R->get_element_set (), &robdd_log);
	do
	{
		cout.flush ();
		best_node->copy (&*solutions[best_solution_index]);
		old_best_size = best_solution;
		selection ();
		mutate_solutions ();
		recalculate_fitness ();
		set_best_solution ();
	}while (best_solution < old_best_size);

	ROBDD * better_R = new ROBDD (R->get_element_set (), best_node->get_ordering ());
	for (list <pair <bool, ElementSubset *> >::iterator it = robdd_log.begin (); 
		it != robdd_log.end (); it++)
		better_R->add_interval (it->second, it->first);
	delete best_node;
	return better_R;
}