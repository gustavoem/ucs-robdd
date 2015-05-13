#ifndef UCS_ROBDD_H_
#define UCS_ROBDD_H_

#include "../ROBDD.h"
#include "../global.h"
#include "../Solver.h"
#include "UCSROBDDToolBox.h"

class UCSROBDD : public Solver
{

private:

	// The robdds of restrictions
	//
	ROBDD * lower_restriction, * upper_restriction;



public:

	// Default constructor.
	//
	UCSROBDD ();


	// Default destructor.
	//
	virtual ~UCSROBDD ();


	// Runs the UCSROBDD algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
	//
	void get_minima_list (unsigned int);

};

#endif /* UCS_ROBDD_H_ */
