#ifndef ROBDD_H_
#define ROBDD_H_

#include "global.h"
#include "ElementSet.h"
#include "Vertex.h"
#include "ElementSubset.h"

class ROBDD
{

private:
	
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

	// Returns a list with all vertex of the ROBDD
	//
	Vertex ** get_all_vertex ();

	// Auxiliar function to get_all_vertex that traverse the robdd assgning
	// pointers of the vertex to the vector vertice
	//
	void fill_vertice (Vertex **, int *, Vertex *);

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
	Vertex * union_step (Vertex * v1, Vertex * v2, map<pair<Vertex *, Vertex *>, Vertex *> *);
};

#endif /* ROBDD_H_ */
