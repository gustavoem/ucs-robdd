#ifndef UCS_ROBDD6_H_
#define UCS_ROBDD6_H_

#include "../ROBDD.h"
#include "../global.h"
#include "../Solver.h"
#include "UCSROBDDToolBox6.h"

class UCSROBDD6 : public Solver
{

private:

	// The collection of restrictions
	//
	ROBDD * restrictions;
	//ROBDD * lower_restriction, * upper_restriction;



public:

	// Default constructor.
	//
	UCSROBDD6 ();


	// Default destructor.
	//
	virtual ~UCSROBDD6 ();


	// Runs the UCSROBDD6 algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
	//
	void get_minima_list (unsigned int);

};

#endif /* UCS_ROBDD6_H_ */
