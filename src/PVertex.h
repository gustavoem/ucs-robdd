#ifndef PVERTEX_H_
#define PVERTEX_H_

#include "global.h"
#include "Element.h"

class PVertex 
{

private:
	
	PVertex * lo;
	PVertex * hi;
	Element * var;
	bool value;
	unsigned int id;
	unsigned int index;
	list<PVertex *> parents;
	
public:

	bool mark;

	// Default PVertex constructor
	//
	PVertex ();

	// Constructor for nonterminal vertices
	//
	PVertex (Element *, unsigned int);


	// Constructor for terminal vertices
	//
	PVertex (bool, unsigned int);


	// Default destructor.
	//
	virtual ~PVertex ();

	// Returns the element of a vertex
	//
	Element * get_var ();

	// Sets the element of a vertex
	//
	void set_var (Element *);

	// Returns the child. True for high (right) and False for low (left)
	//
	PVertex * get_child (bool);


	// Sets the child. True for high (right) and False for low (left)
	//
	void set_child (PVertex *, bool);


	// Returns the value of a vertex
	//
	int get_value (); 


	// Sets the value of a vertex
	//
	void set_value (int);
	
	// Returns the id of a vertex
	//
	unsigned int get_id ();


	// Sets the id of a vertex
	//
	void set_id (unsigned int);

	// Returns the index of a vertex
	//
	unsigned int get_index ();


	// Sets the index of a vertex
	//
	void set_index (unsigned int);	


	// Says if the vertex is terminal
	//
	bool is_terminal();

	// Add a parent to the node
	//
	void add_parent (PVertex *);


	// Return one of the PVertexs parent
	//
	PVertex * get_some_parent ();

};

#endif /* PVERTEX_H_ */