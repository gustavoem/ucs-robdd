#ifndef ROBDD_H_
#define ROBDD_H_

#include "global.h"
#include "ElementSet.h"
#include "Vertex.h"
#include "ElementSubset.h"
#include "CostFunction.h"

class ROBDD
{

private:
	

	// Stores the number of updates (add_interval) of the robdd
	//
	unsigned int nof_updates;
	

	// Stores the number of consults of the robdd
	//
	unsigned int nof_consults;


	// Time spent updating the ROBDD
	//
	unsigned int time_updating;

	// Time spent consulting the ROBDD
	//
	unsigned int time_consulting;


	// Time spent reducing the ROBDD
	//
	unsigned int time_reducing;

	// The set of elements this ROBDD will represent
	//
	ElementSet * elm_set;


	// The root of the ROBDD
	//
	Vertex * root;	

	// Prints the sub-tree that has the parameter Vertex as root
	//
	void print(Vertex *);


	// Auxiliar function to ROBDD (ElementSet *, ElementSubset*)
	//
	void build (Vertex *, unsigned int, unsigned int, ElementSubset *, Vertex *, Vertex *);


	// Auxiliar function to ROBDD::reduce ()
	//
	void fill_vlist (Vertex *, list<Vertex *> **);


	// Unmarks all the vertices from the robdd
	//
	void unmark_all_vertex ();


	// Unmarks all the vertices from the subtree with root Vertex *
	//
	void unmark_all_vertex (Vertex *);


	// Deletes the subtree with root Vertex *
	//
	void delete_subtree (Vertex **, unsigned int *);


	// Returns a list with all vertex of the ROBDD with root Vertex *
	//
	Vertex ** get_all_vertex (Vertex *, unsigned int);


	// Auxiliar function to get_all_vertex that traverse the robdd assgning
	// pointers of the vertex to the vector vertice
	//
	void fill_vertice (Vertex **, int *, Vertex *);

	// Auxiliar function to add_lower_interval (). This method builds a tree of
	// a ROBDD that has ones for subsets covered by the subset passed by 
	// argument.
	//
	Vertex * build_interval (unsigned int, unsigned int *, ElementSubset *, Vertex *, Vertex *, bool);


public:

	// ROBDD cardinality
	//
	unsigned int cardinality;


	// Builds a ROBDD representing the function "0"
	//
	ROBDD (ElementSet *);


	// this is for testing reduce ()
	//
	ROBDD (ElementSet *, int);


	// Builds an ROBDD where the only path valued "1", is the path representing the subset
	//
	ROBDD (ElementSet *, ElementSubset *);


	// Default destructor.
	//
	virtual ~ROBDD ();	


	// Returns the root vertex
	//
	Vertex * get_root ();


	// Prints the entire ROBDD
	//
	void print ();
	

	// Reduces the OBDD
	//
	void reduce ();


	// Makes the union of this ROBDD and the one passed by argument
	//
	void union_to (Vertex *);


	// Makes the union of the subtrees passed by argument
	//
	Vertex * union_step (Vertex * v1, Vertex * v2, map<pair<Vertex *, Vertex *>,\
						 Vertex *> *, unsigned int *, Vertex *, Vertex *);


	// Adds to the ROBDD all the subsets covered (if bool false) or that covers (if bool
	// true) by ElementSubset *
	//
	void add_interval (ElementSubset *, bool);


	// Returns true if the ElementSubset * path of the robdds leads to a 1
	//
	bool contains (ElementSubset *);


	// Returns a random subset that is evaluated by zero.
	//
	ElementSubset * get_random_zero_evaluated_element ();


	// Returns nof_consults
	//
	unsigned int get_nof_consults ();


	// Returns nof_updates
	//
	unsigned int get_nof_updates ();


	// Returns time elapsed updating the robdd
	//
	int get_time_updating ();

	
	// Returns time elapsed consulting the robdd
	//
	int get_time_consulting ();	


	// Returns time elapsed consulting the robdd
	//
	int get_time_reducing ();	
};

#endif /* ROBDD_H_ */
