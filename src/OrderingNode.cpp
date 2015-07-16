#include "OrderingNode.h"

OrderingNode::OrderingNode (ElementSet * elm_set, list <pair <bool, ElementSubset *> > * l)
{
	this->size = elm_set->get_set_cardinality ();
	permutation = (unsigned int *) malloc (size * sizeof (unsigned int));
	
	for (unsigned int i = 0; i < size; i++)
		permutation[i] = i;

	random_shuffle (&permutation[0], &permutation[size]);
	// shuffle_individual ();

	/*cout << "(ON) Valores da permutação: ";
	for (unsigned int i = 0; i < elm_set->get_set_cardinality (); i++)
		cout << permutation[i] << " ";
	cout << endl;
	cout.flush ();*/
	garobdd = new GAROBDD (elm_set, l, this->permutation);
	robdd_size = garobdd->get_cardinality ();
}

OrderingNode::~OrderingNode ()
{
	delete garobdd;
	free (permutation);
}


void OrderingNode::recalculate_fitness ()
{
	list <pair <bool, ElementSubset *> > * l = garobdd->get_log ();
	ElementSet * elm_set = garobdd->get_element_set ();
	GAROBDD * old_garobdd = garobdd;
	garobdd = new GAROBDD (elm_set, l, permutation);
	delete old_garobdd;
}


void OrderingNode::shuffle_individual ()
{
	cout << "fazendo shuffle: " << endl;
	for (unsigned int n = size; n > 0; n--)
	{
		// here sol[n - 1, ..., solution_size - 1] is a random shuffle
		unsigned int j = ((unsigned int) rand () % size);   // random number between 0 and n - 1
		unsigned int i = ((unsigned int) rand () % size);   // random number between 0 and n - 1
		cout << "i: " << i << ", j: " << j << endl;
		unsigned int aux = permutation[j];
		permutation[j] = permutation[i];
		permutation[i] = aux;
	}
	cout << "\nindivíduo gerado: " << endl;
	for (unsigned int i = 0; i < size; i++)
		cout << permutation[i] << " ";
}


void OrderingNode::recombine_to (unsigned int * perm2)
{
	cout << "Original: " << endl;
	for (unsigned int i = 0; i < size; i++)
		cout << permutation[i] << " ";
	cout << endl;

	cout << "Combinando com: " << endl;
	for (unsigned int i = 0; i < size; i++)
		cout << perm2[i] << " ";
	cout << endl;


	bool * indexed = (bool *) malloc (size * sizeof (bool));
	for (unsigned int i = 0; i < size; i++)
		indexed[i] = 0;
	unsigned int p1_i = 0;
	unsigned int p2_i = 0;
	unsigned int candidate = permutation[0];
	for (unsigned int i = 0; i < size; i++)
	{
		while (indexed[candidate])
		{
			if (i % 2)
				candidate = permutation[p1_i++];
			else
				candidate = perm2[p2_i++];
		}
		indexed[candidate] = 1;
		permutation[i] = candidate;
	}
	cout << "Crossover: " << endl;
	for (unsigned int i = 0; i < size; i++)
		cout << permutation[i] << " ";
	cout << endl;
	cout.flush ();
}


void OrderingNode::mut ()
{
	unsigned int j = ((unsigned int) rand () % size);
	unsigned int i = ((unsigned int) rand () % size);
	unsigned int aux = permutation[j];
	permutation[j] = permutation[i];
	permutation[i] = aux;
}


void OrderingNode::mut_twice ()
{
	mut ();
	mut ();
}


void OrderingNode::neighbour_mut ()
{
	unsigned int i = ((unsigned int) rand () % (size - 1));
	unsigned int aux = permutation[i];
	permutation[i] = permutation[i + 1];
	permutation[i + 1] = aux;
}


void OrderingNode::print_solution ()
{
	cout << "\nsolução: ";
	for (unsigned int i = 0; i < size; i++)
		cout << permutation[i] << " ";
	cout << " ROBDD size: " << garobdd->get_cardinality ();
}


double OrderingNode::get_normalized_fitness ()
{
	return normalized_fitness;
}


void OrderingNode::set_normalized_fitness (double x)
{
	normalized_fitness = x;
}


double OrderingNode::get_accumulated_fitness ()
{
	return accumulated_fitness;
}


void OrderingNode::set_accumulated_fitness (double x)
{
	accumulated_fitness = x;
}


unsigned int * OrderingNode::get_ordering ()
{
	return permutation;
}


unsigned int OrderingNode::get_robdd_size ()
{
	return robdd_size;
}


GAROBDD * OrderingNode::get_robdd ()
{
	return garobdd;
}