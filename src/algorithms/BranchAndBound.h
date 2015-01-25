/*
 * BranchAndBound.h
 *
 *  Created on: Apr 6, 2011
 *      Author: marceloreis
 */

#ifndef BRANCH_AND_BOUND_H_
#define BRANCH_AND_BOUND_H_

#include "../global.h"
#include "../Solver.h"
#include "../ElementSubset.h"

#define MAX_SUBSET_SIZE 10000

class BranchAndBound : public Solver
{

public:

	BranchAndBound ();


	virtual ~BranchAndBound ();


	// Runs the algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
	//
	void get_minima_list(unsigned int);

};

#endif /* BRANCH_AND_BOUND_H_ */
