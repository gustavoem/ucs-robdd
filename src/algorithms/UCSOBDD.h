#ifndef UCS_OBDD_H_
#define UCS_OBDD_H_

#include "../OBDD.h"
#include "../global.h"
#include "../Solver.h"
#include "UCSOBDDToolBox.h"

class UCSOBDD : public Solver
{

private:

	// The obdd of restrictions
	//
	OBDD * restrictions;



public:

	// Default constructor.
	//
	UCSOBDD ();


	// Default destructor.
	//
	virtual ~UCSOBDD ();


	// Runs the UCSOBDD algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
	//
	void get_minima_list (unsigned int);

};

#endif /* UCS_OBDD_H_ */
