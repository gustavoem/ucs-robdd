//
// PartitionModel.h -- definition of the class "PartitionModel".
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

#ifndef PARTITION_MODEL_H_
#define PARTITION_MODEL_H_

#include "ElementSet.h"
#include "ElementSubset.h"
#include <map>

// This class is used to fix elements of an ElementSet and also define
// a subposet of the poset defined by power set of ElementSet
//
class PartitionModel
{

private:

    // Pointer to the set that contains the elements that are fixed or 
    // not, i.e the original set
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
    unsigned int fixed_set_size;


public:

    // Default constructor. Receives the elementsubset that represents
    // the lowest element of this fraction of the poset
    //
    PartitionModel (ElementSubset * sel_elms, 
            ElementSubset * non_sel_elms);


    // Default destructor.
    //
    virtual ~PartitionModel ();


    // From an element subset defined over the subposet returns the
    // elementsubset correspondent in the original poset
    //
    ElementSubset * get_orig_subset (ElementSubset *);


    // Returns a pointer to the element set that contains the elements
    // of the original set and are not fixed
    //
    ElementSet * get_unfixed_elm_set ();

};

#endif /* FIXED_ELEMENTSSUBSET_H_ */
