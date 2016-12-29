#ifndef PUCSR1TOOLBOX_H_
#define PUCSR1TOOLBOX_H_

#include "../ROBDD.h"
#include "../CostFunction.h"
#include "../Collection.h"
#include "../ElementSubset.h"
#include "../Partition.h"
#include "../functions/PartitionCost.h"
#include "../PartitionNode.h"
#include "../Solver.h"
#include "../algorithms/ExhaustiveSearch.h"

namespace PUCSR1ToolBox
{  

    // Adds the elements from a list of elementsubset to a collection. 
    // This function is used to transfer the list of minima of a 
    // partition to the list of minima of the original problem
    //
    void update_minima_list (Collection *, PartitionNode *, 
        list<ElementSubset *> *);


    // Finds the minimum of a partition and adds the list of minima of
    // this partition to the collection L.
    //
    void part_minimum (PartitionNode *, Collection *, 
        CostFunction *, unsigned int);


    // Given a Partition P and an index i we return an adjacent 
    // partition Q. Partitions are defined according to fixed elements
    // that can be selected or not inside the partition. If the set of
    // selected elements in one partition differs to the set of 
    // selected elements in another partition by only one element then
    // we call these partitions adjacent. Given P partition we return
    // adjacent partition Q that differs from P on the selected 
    // elements only on the i-th element.
    //
    PartitionNode * adjacent_partition (PartitionNode *, unsigned int);


    // Given a partition P and partition Q perform one step of the walk
    // that we described below in "random_walk".
    // If P1 is upper adjacent partition to P2 then:
    // 1) If minimal element of P1 has cost greater than minimal 
    // element of P2 we can prune every partition that covers the
    // minimal element of P1 (including P1 itself).
    // 2) If maximal element of P2 has cost greater than maximal elemnt
    // of P1 then we can prune every partition that is covered by the
    // maximal element of P2 (including P2 itself).
    // 
    // By the end we return the partition that will be used in the next
    // step of the walk. If both partitions P1 and P2 got prunned then
    // we return NULL.
    PartitionNode * prune_and_walk (PartitionNode *, PartitionNode *,
        CostFunction *, ROBDD *);


    // A simple random walk between partitions
    // This method receives as argument a partition, a robdd R 
    // (representing the set of partitions) and a Collection. It sets a
    // partition node P as the argument partition and walks on the set 
    // of partitions in the following way:
    //
    // do {
    //     find the minimum element in the partition P and update L
    //     choose an adjacent partition Q
    //     if Q is upper adjacent to P
    //         if cost (maximal (P)) > cost (maximal (Q))
    //             restrict every partition covered by maximal (P)
    //             change P to Q
    //         if cost (minimal (Q)) > cost (minimal (P))
    //             restrict every partition the covers minimal (Q)
    //         otherwise
    //             choose any other neighbour of P
    //             # or find the minimum of this partition ?
    //     if Q is lower adjacent to P
    //         if cost (minimal (P) > minimal (Q))
    //             restrict every partition that covers minimal (P)
    //             change P to Q
    //         if cost (maximal (Q)) > cost (maximal (P))
    //             restrict every partition covered by maximal (Q)
    //         otherwise
    //             choose another neighbour of P
    // } while (P has unvisited neighbours);
    //
    void random_walk (PartitionNode *, ROBDD *, CostFunction *,
        Collection *, unsigned int);


    // Returns true if the partition is restricted
    //
    bool is_restricted (PartitionNode *, ROBDD *);


    // Restricts a partition
    //
    void restrict_partition (PartitionNode *, ROBDD *);

    
} // end of namespace

#endif /* PUCSR1TOOLBOX_H_ */
