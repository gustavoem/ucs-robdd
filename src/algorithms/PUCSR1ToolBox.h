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


    // Given a PartitionNode P and an index i we return an adjacent 
    // part Q. Parts are defined according to fixed elements that can
    // be selected or not inside the part. If the set of selected
    // elements in one part differs to the set of selected elements in
    // another part by only one element then we call these parts
    // adjacent. 
    //    Given part P we return adjacent part Q such that Q is 
    // adjacent to P and the element that differs from both is the i-th
    // element.
    //
    PartitionNode * adjacent_part (PartitionNode *, unsigned int);


    // Given a part P and part Q, we prune the poset with the folowing 
    // rule.
    //     If P1 is upper adjacent to P2 then:
    //     1) If c (O (P1)) > c (O (P2)) then we can prune every part
    //        that covers P1 (including itself).
    //     2) If c (I (P2)) > c (I (P1)) then we can prune every part
    //        that is covered by P2 (including itself).
    //
    // This function returns:
    //     Q by default
    //     P if Q is restricted by the end of the function
    //     NULL if P and Q are restricted by the end of the function
    PartitionNode * prune_and_walk (PartitionNode *, PartitionNode *,
        CostFunction *, ROBDD *);


    // A simple random walk between parts. This function receives as
    // argument a part P, a robdd R (representing the set of parts)
    // and a Collection. From P the function walks in the following way:
    //
    // do {
    //     Choose an adjacent part Q
    //     Apply prunning rules
    //     If P and Q got prunned, return
    //     If Q got prunned, choose another neighbour of P
    //     Otherwise, P = Q
    // } while (P has unvisited neighbours);
    //
    void random_walk (PartitionNode *, ROBDD *, CostFunction *,
        Collection *, unsigned int);


    // Returns true if the part is restricted
    //
    bool is_restricted (PartitionNode *, ROBDD *);


    // Restricts a part
    //
    void restrict_part (PartitionNode *, ROBDD *);

    
} // end of namespace

#endif /* PUCSR1TOOLBOX_H_ */
