#ifndef OBDD_H_
#define OBDD_H_

#include "global.h"
#include "ElementSet.h"
#include "PVertex.h"
#include "ElementSubset.h"
#include "CostFunction.h"

class OBDD
{

private:
	

	// Stores the number of updates (add_interval) of the robdd
	//
	unsigned int nof_updates;
	

	// Stores the number of consults of the robdd
	//
	unsigned int nof_consults;


	// Time spent updating the OBDD
	//
	unsigned int time_updating;

	// Time spent consulting the OBDD
	//
	unsigned int time_consulting;

	// The set of elements this OBDD will represent
	//
	ElementSet * elm_set;


	// The root of the OBDD
	//
	PVertex * root;	

	// The zero-node of the OBDD
	//
	PVertex * zero_node;

	// Prints the sub-tree that has the parameter PVertex as root
	//
	void print(PVertex *);


	// Auxiliar function to OBDD (ElementSet *, ElementSubset*)
	//
	void build (PVertex *, unsigned int, unsigned int, ElementSubset *, PVertex *, PVertex *);


	// Auxiliar function to OBDD::reduce ()
	//
	void fill_vlist (PVertex *, list<PVertex *> **);


	// Unmarks all the vertices from the robdd
	//
	void unmark_all_vertex ();


	// Unmarks all the vertices from the subtree with root PVertex *
	//
	void unmark_all_vertex (PVertex *);


	// Deletes the subtree with root PVertex *
	//
	void delete_subtree (PVertex **, unsigned int *);


	// Returns a list with all vertex of the OBDD with root PVertex *
	//
	PVertex ** get_all_vertex (PVertex *, unsigned int);


	// Auxiliar function to get_all_vertex that traverse the robdd assgning
	// pointers of the vertex to the vector vertice
	//
	void fill_vertice (PVertex **, int *, PVertex *);

	// Auxiliar function to add_lower_interval (). This method builds a tree of
	// a OBDD that has ones for subsets covered by the subset passed by 
	// argument.
	//
	PVertex * build_interval (unsigned int, unsigned int *, ElementSubset *, PVertex *, PVertex *, bool);


public:

	// OBDD cardinality
	//
	unsigned int cardinality;


	// Builds a OBDD representing the function "0"
	//
	OBDD (ElementSet *);


	// this is for testing reduce ()
	//
	OBDD (ElementSet *, int);


	// Builds an OBDD where the only path valued "1", is the path representing the subset
	//
	OBDD (ElementSet *, ElementSubset *);


	// Default destructor.
	//
	virtual ~OBDD ();	


	// Returns the root vertex
	//
	PVertex * get_root ();


	// Prints the entire OBDD
	//
	void print ();
	

	// Reduces the OBDD
	//
	void reduce ();


	// Makes the union of this OBDD and the one passed by argument
	//
	void union_to (PVertex *);


	// Makes the union of the subtrees passed by argument
	//
	PVertex * union_step (PVertex * v1, PVertex * v2, map<pair<PVertex *, PVertex *>,\
						 PVertex *> *, unsigned int *, PVertex *, PVertex *);


	// Adds to the OBDD all the subsets covered (if bool true) or that covers (if bool
	// false) by ElementSubset *
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

};

#endif /* OBDD_H_ */

