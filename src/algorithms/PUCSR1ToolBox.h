#ifndef PUCSR1TOOLBOX_H_
#define PUCSR1TOOLBOX_H_

#include "../ROBDD.h"
#include "../CostFunction.h"
#include "../Collection.h"
#include "../ElementSubset.h"

namespace PUCSR1ToolBox
{

    // Creates the PartitionSet object according to the partition 
    // determined in the parameter.
    //
    // OBS: we assume here that the fixed elements are the first
    // elements, therefore if the i-th element of the set of fixed
    // elements is selected (or not) the i-th element of the original
    // element set is selected (or not)
    //
    PartitionSet * get_partition (ElementSubset *);


} // end of namespace

#endif /* PUCSR1TOOLBOX_H_ */
