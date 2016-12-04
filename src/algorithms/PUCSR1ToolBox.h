#ifndef PUCSR1TOOLBOX_H_
#define PUCSR1TOOLBOX_H_

#include "../ROBDD.h"
#include "../CostFunction.h"
#include "../Collection.h"
#include "../ElementSubset.h"
#include "../PartitionModel.h"
#include "../Partition.h"

namespace PUCSR1ToolBox
{  

    // Finds the minimum of a partition and adds the list of minima of
    // this partition to the collection L.
    //
    void find_minimum (Partition *, Collection *);


    // A simple random walk between partitions
    // This method receives as argument a partition, a robdd R 
    // (representing the set of partitions) and a Collection. It sets a
    // partition P as the argument partition and walks on the set of 
    // partitions in the following way:
    //
    // do {
    //     find the minimum element in the partition P and update L
    //     choose an adjacent partition Q
    //     if Q is upper adjacent to X
    //         if cost (maximal (X)) > cost (maximal (Y))
    //             restrict every partition covered by maximal (X)
    //             change P to Q
    //         if cost (minimal (Y)) > cost (minimal (X))
    //             restrict every partition the covers minimal (Y)
    //         otherwise
    //             choose any other neighbour of X
    //             # or find the minimum of this partition ?
    //     if Q is lower adjacent to X
    //         if cost (minimal (X) > minimal (Y))
    //             restrict every partition that covers minimal (X)
    //             change P to Q
    //         if cost (maximal (Y)) > cost (maximal (X))
    //             restrict every partition covered by maximal (Y)
    //         otherwise
    //             choose another neighbour of X
    // } while (X has unvisited neighbours);
    //
    //
    void random_walk (Partition *, ROBDD *, CostFunction *, 
        Collection *);

} // end of namespace

#endif /* PUCSR1TOOLBOX_H_ */
