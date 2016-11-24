#ifndef PUCSR1_H_
#define PUCSR1_H_

#include "../ROBDD.h"
#include "../global.h"
#include "../Solver.h"
#include "../ElementSubset.h"
#include "../FixedElementSet.h"
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
    PartitionModel * part_model;


    // The size of the partition
    //
    unsigned int nof_unfixed_elms;


public:

    // Default constructor.
    //
    PUCSR1 ();


    // Default destructor.
    //
    virtual ~PUCSR1 ();


    // Runs the PUCSR1 algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
    //
    void get_minima_list (unsigned int);

};

#endif /* PUCSR1_H_ */
