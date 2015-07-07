#ifndef ELEMENTSET_H_
#define ELEMENTSET_H_

#include "Element.h"

class ElementSet
{

private:

	// list_of_elements[0..number_of_elements-1]
	//
	Element * * list_of_elements;

	// indexes of elements in list_of_elements
	//
	map<Element *, unsigned int> element_indexes;

	// true if it has a hidden extra elements (used, for instance, in W-operator
	// feature selection) and false otherwise.
	//
	bool has_extra_element;

	// Name of this set.
	//
	string name;

	// Number of elements contained by this set.
	//
	unsigned int number_of_elements;

	// container map; it is implemented as a self-balancing binary search tree
	// (namely a Red-black tree).
	//
	// This map is used to store a cost function explicitly defined, that is,
	// for each X \subseteq S, it is stored the value of c(X).
	//
	map<string, float> explicit_cost;


	// Put values to element_indexes
	//
	void set_elm_indexes ();

public:

	// Default constructor: an empty set with a given name.
	//
	ElementSet (string);


	// Constructor: a set with elements extracted from a XML file.
	//
	ElementSet (string, string);


	// Constructor: a set with elements extracted from a DAT file with n elements.
	//
	ElementSet (string, unsigned int);


	// Constructor: a set with n random-valued elements with integers between [0, range].
	//
	ElementSet (string, unsigned int, unsigned int);


	// Default destructor.
	//
	virtual ~ElementSet ();


	// Returns a pointer to the element at the "index" position. If there is no
	// element at such position, it returns NULL.
	//
	Element * get_element (unsigned int);


	// Given an Element * Y, returns an unsigned integer x such that list_of_elements[x]
	// is the same as Y.
	//
	unsigned int get_element_index (Element *);


	// Returns the cardinality of this set (i.e., the number of elements).
	//
	unsigned int get_set_cardinality ();


	// Receives a string corresponding to a subset and returns its cost,
	// explicitly declared through the input file.
	//
	float get_explicit_cost (string);


	// Returns the name of this set.
	//
	string get_set_name ();


	// Permute the elements of the set. Useful to obtain different running
	// times in solvers such as SFFS and BranchAndBound.
	//
	void permute_set ();


	// Prints in the STDOUT all the elements of this set and their values.
	//
	void print_list_of_elements ();

};

#endif /* ELEMENTSET_H_ */
