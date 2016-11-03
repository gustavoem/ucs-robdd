//
// ElementSubset.h -- definition of the class "ElementSubset".
//
//    This file is part of the featsel program
//    Copyright (C) 2010  Marcelo S. Reis
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef ELEMENTSUBSET_H_
#define ELEMENTSUBSET_H_

#include "ElementSet.h"
#include "global.h"


class ElementSubset
{

private:

    // cardinality of the subset
    unsigned int subset_cardinality;


    // list_of_elements[0..|S|-1], where |S| = set->get_set_cardinality()
    // list_of_elements[i] = true  <=>  element at i position in the set array belongs to subset
    //
    bool * list_of_elements;


    // List of elements of the subset in random order. This list is used
    // in order to obtain the removal of random elements of the subset.
    //
    list<unsigned int> L;


    // Name of the subset (e.g. X, Y, etc.)
    //
    string name;


    // pointer to the set that contains this subset
    //
    ElementSet * set;


public:

    // Value of the subset (default zero)
    //
    float cost;


    // Stores the number of times a restriction subset is checked in UCS2b
    //
    unsigned int j;


    // Counting the frequencies of labels of samples, i.e. the number of occurrences of
    // Y == i, i in {0, ..., k} possible labels, generally k == 1.
    // during a W-operator feature selection
    //
    unsigned int * Y;


    // Default constructor.
    //
    ElementSubset (string, ElementSet *);

    
    // Copy constructor
    //
    ElementSubset (ElementSubset *);


    // Default destructor.
    //
    virtual ~ElementSubset ();


    // Adds the element at 'index' position to the subset.
    // Returns true if the operation is successful and false otherwise.
    //
    bool add_element (unsigned int);


    // Returns true if this subset contains the subset Y, false otherwise.
    //
    bool contains (ElementSubset *);


    // Copy in this object the data of the object * X.
    //
    void copy (ElementSubset *);


    // Returns the cardinality of the set that contains this subset.
    //
    unsigned int get_set_cardinality ();


    // Returns the pointer to the set that contains this subset.
    //
    ElementSet * get_set_that_contains_this_subset ();


    // Returns the cardinality of this subset.
    //
    unsigned int get_subset_cardinality ();


    // Verifies if the element at 'index' position from the subset.
    // Returns true if it is in the subset and false otherwise.
    //
    bool has_element (unsigned int);


    // Sets this subset as the intersection of it and the parameter subset.
    //
    void subset_intersection (ElementSubset *);


    // Returns true if this subset is contained by the subset Y, false otherwise.
    //
    bool is_contained_by (ElementSubset *);


    // Returns true is the subset is an empty set and false if it has elements.
    //
    bool is_empty ();


    // Returns true if this subset is equal to the subset Y, false otherwise.
    //
    bool is_equal (ElementSubset *);


    // Returns a string with the list of elements in the format [010...011],
    // where "1" if the element belongs to the subset, "0" otherwise.
    // This method is useful to print the output of the program.
    //
    string print_subset ();


    // Returns a string with the list of elements in the HEX format, e.g.:
    // If the subset is [11110111], then is returned "F7".
    // This method is useful to get smaller keys for the map containers.
    //
    string print_subset_in_hex ();


    // Removes the element at 'index' position from the subset.
    // Returns true if the operation is successful and false otherwise.
    //
    bool remove_element (unsigned int);


    // Removes an element of index i from the subset and returns the value of i.
    // If the subset is empty, it returns the set cardinality.
    //
    unsigned int remove_random_element ();


    // Sets the subset as its complement subset.
    //
    void set_complement_subset ();  // [0,1,0,0] -> [1,0,1,1]


    // Sets the subset as a complete set.
    //
    void set_complete_subset ();    // list_of_elements = [1,1,...,1]


    // Sets the subset as an empty set.
    //
    void set_empty_subset ();       // list_of_elements = [0,0,...,0]


    // Sets this subset as the union of it and the parameter subset.
    //
    void subset_union (ElementSubset *);

};

#endif /* ELEMENTSUBSET_H_ */
