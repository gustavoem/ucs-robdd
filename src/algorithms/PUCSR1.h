#ifndef PUCSR1_H_
#define PUCSR1_H_

#include "../ROBDD.h"
#include "../global.h"
#include "../Solver.h"
#include "../ElementSubset.h"
#include "../Partition.h"
#include "../PartitionNode.h"
#include "PUCSR1ToolBox.h"
// #include "UCSROBDDToolBox6.h"

class PUCSR1 : public Solver
{

private:

    // The collection of restrictions
    //
    // ROBDD * restrictions;


    // The partitions of the poset which can have the minimal element
    //
    ROBDD * cand_part;


    // The element set of the variables that are fixed in each 
    // partition
    //
    Partition * partition;


    // The size of the partition
    //
    unsigned int nof_unfixed_elms;


    // Sets the partition model we are going to use
    //
    void set_partition_model ();


    // A simple random walk between parts. This function receives as
    // argument a part P. From P the function walks in the following way:
    //
    // do {
    //     Choose an adjacent part Q
    //     Apply prunning rules
    //     If P and Q got prunned, return
    //     If Q got prunned, choose another neighbour of P
    //     Otherwise, P = Q
    // } while (P has unvisited neighbours);
    //
    void random_walk (PartitionNode *, Collection *);


public:

    // Default constructor.
    //
    PUCSR1 ();


    // Default destructor.
    //
    virtual ~PUCSR1 ();


    // Runs the PUCSR1 algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
    //
    void find_minima_list (unsigned int);


};

#endif /* PUCSR1_H_ */
