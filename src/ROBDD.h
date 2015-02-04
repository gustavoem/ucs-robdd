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


	// Identify the vertices of a OBDD with root Vertex *
	//
	void identify (Vertex *, unsigned int *);

	// Auxiliar function to ROBDD::reduce ()
	//
	void fill_vlist (Vertex **, Vertex *);


	//
	//
	void unmark_all_vertex ();


	//
	//
	void unmark_all_vertex (Vertex *);


public:

	// ROBDD cardinality
	//
	unsigned int cardinality;

	// Builds a ROBDD representing the function "0"
	//
	ROBDD (ElementSet *);


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

	
	// Identify the vertices of a OBDD
	//
	void identify ();

	
	// Reduces the OBDD
	//
	void reduce ();
};

#endif /* ROBDD_H_ */
