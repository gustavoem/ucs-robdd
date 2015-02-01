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

public:

	// Default constructor.
	//
	Vertex (Element *);


	// Default destructor.
	//
	virtual ~Vertex ();


	Element * get_var ();


	Vertex * get_lo ();


	bool set_lo(Vertex *);


	Vertex * get_hi ();


	bool set_hi(Vertex *);
};

#endif /* VERTEX_H_ */