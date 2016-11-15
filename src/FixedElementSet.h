//
// ElementSubset.h -- definition of the class "ElementSubset".
//
//    This file is part of the featsel program
//    Copyright (C) 2016  Gustavo E. Matos
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

#ifndef FIXED_ELEMENTSSET_H_
#define FIXED_ELEMENTSSET_H_

#include "ElementSet.h"
#include "ElementSubset.h"
#include <map>

// This class is used to fix elements of an ElementSet and also define
// a subposet of the poset defined by power set of ElementSet
//
class FixedElementSet
{

private:

    // Pointer to the set that contains the elements that are fixed or 
    // not
    //
    ElementSet * original_set;


    // Pointer to the set that cointais the elements that are not fixed
    //
    ElementSet * unfixed_set;


    // List of fixed elements that are selected
    //
    ElementSubset * selected_elements;


    // List of fixed elements that are not selected
    //
    ElementSubset * non_selected_elements;


    // Used to map elements from the subproblem set to the original 
    // elemnt set
    //
    unsigned int * element_map;


    // Stores the size of the element set without the fixed elements
    //
    unsigned int size;


public:

    // Default constructor. Receives the elementsubset that represents
    // the lowest element of this fraction of the poset
    //
    FixedElementSet (ElementSubset * sel_elms, 
            ElementSubset * non_sel_elms);


    // Default destructor.
    //
    virtual ~FixedElementSet ();


    // From an element subset defined over the subposet returns the
    // elementsubset correspondent in the original poset
    //
    ElementSubset * getCorrespondentSubset (ElementSubset *);


    // Returns a pointer to the element set that contains the elements
    // of the original set and are not fixed
    //
    ElementSet * getUnfixedElementSet ();

};

#endif /* FIXED_ELEMENTSSUBSET_H_ */
