//
// Partition.h -- definition of the class "Partition".
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

#ifndef PARTITION_H_
#define PARTITION_H_

#include "ElementSet.h"
#include "ElementSubset.h"
#include "PartitionModel.h"

// This class is used to fix elements of an ElementSet and also define
// a subposet of the poset defined by power set of ElementSet
//
class Partition
{

private:

    // All the fixed elements that are selected. This is defined over
    // the ElementSet that contains only the fixed elements
    //
    ElementSubset * selected_elements;
    

    // Stores the minimal element of the partition. This is the same
    // as the ElementSubset selected_elements but defined over the 
    // original ElementSet
    //
    ElementSubset * minimal_subset;


    // A pointer to the partition model this partition is using
    //
    PartitionModel * part_model;


    // Find the minimal subset of this partition
    // 
    void find_minimal_subset ();

public:

    // Default constructor. Receives the elementsubset that represents
    // the lowest element of this fraction of the poset
    //  
    Partition (PartitionModel *, ElementSubset *);


    // Default destructor.
    //
    virtual ~Partition ();


    // From an elementsubset defined in this partition returns the
    // elementsubset correspondent in the original poset
    //
    ElementSubset * get_original_subset (ElementSubset *);


    // Returns the original subset from which this partition is in
    //
    ElementSet * get_original_set ();

};

#endif /* PARTITION_H_ */
