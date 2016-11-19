//
// PartitionCost.h -- definition of the class "PartitionCost".
//
//    This file is part of the featsel program
//    Copyright (C) 2016 Gustavo Estrela de Matos
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

#ifndef PARTITION_COST_H_
#define PARTITION_COST_H_


#include "../global.h"
#include "../ElementSubset.h"
#include "../CostFunction.h"
#include "../PartitionSet.h"


class PartitionCost : public CostFunction
{

protected:

    // Stores the information about the partition being evaluated
    //
    PartitionSet * part_set;


    // Stores the orignal cost function
    //
    CostFunction * orig_cost_f;

public:

    // Default constructor.
    //
    PartitionCost (CostFunction *, PartitionSet *);


    // Default destructor.
    //
    virtual ~PartitionCost ();


    // Returns the value of c(X), where X is a subset.
    // It first finds the correspondent subset in the original problem
    // and then calculates its cost.
    //
    float cost (ElementSubset *);

};

#endif /* PARTITION_COST_H_ */
