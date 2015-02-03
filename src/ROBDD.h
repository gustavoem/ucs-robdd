#ifndef ROBDD_H_
#define ROBDD_H_

#include "global.h"
#include "ElementSet.h"
#include "Vertex.h"

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


public:

	// Default constructor.
	//
	ROBDD (ElementSet *);


	// Default destructor.
	//
	virtual ~ROBDD ();	


	// Returns the root vertex
	//
	Vertex * get_root ();

	// Prints the entire ROBDD
	//
	void print ();

};

#endif /* ROBDD_H_ */
