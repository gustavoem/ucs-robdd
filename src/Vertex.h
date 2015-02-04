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
	unsigned int id;

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


	bool set_child (Vertex *, bool);


	Vertex * get_hi ();


	int get_value (); 


	unsigned int get_id ();


	void set_id (unsigned int);

};

#endif /* VERTEX_H_ */