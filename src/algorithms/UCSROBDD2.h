#ifndef UCS_ROBDD2_H_
#define UCS_ROBDD2_H_

#include "../ROBDD.h"
#include "../global.h"
#include "../Solver.h"
#include "UCSROBDDToolBox2.h"

class UCSROBDD2 : public Solver
{

private:

	// The collection of restrictions
	//
	ROBDD * restrictions;
	//ROBDD * lower_restriction, * upper_restriction;



public:

	// Default constructor.
	//
	UCSROBDD2 ();


	// Default destructor.
	//
	virtual ~UCSROBDD2 ();


	// Runs the UCSROBDD2 algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
	//
	void get_minima_list (unsigned int);

};

#endif /* UCS_ROBDD2_H_ */
