#ifndef VERTEX_H_
#define VERTEX_H_

#include "global.h"
#include "Element.h"

class Vertex 
{

private:
	
	Vertex * lo;
	Vertex * hi;
	Element * var;
	bool value;

public:

	// Constructor for nonterminal vertices
	//
	Vertex (Element *);


	// Constructor for terminal vertices
	//
	Vertex (bool);


	// Default destructor.
	//
	virtual ~Vertex ();


	Element * get_var ();


	Vertex * get_lo ();


	bool set_lo(Vertex *);


	Vertex * get_hi ();


	bool set_hi(Vertex *);


	int get_value(); 
	
};

#endif /* VERTEX_H_ */