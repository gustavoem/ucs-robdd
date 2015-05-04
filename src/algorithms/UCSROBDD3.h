#ifndef UCS_ROBDD3_H_
#define UCS_ROBDD3_H_

#include "../ROBDD.h"
#include "../global.h"
#include "../Solver.h"
#include "UCSROBDDToolBox3.h"

class UCSROBDD3 : public Solver
{

private:

	// The collection of restrictions
	//
	ROBDD * restrictions;
	//ROBDD * lower_restriction, * upper_restriction;



public:

	// Default constructor.
	//
	UCSROBDD3 ();


	// Default destructor.
	//
	virtual ~UCSROBDD3 ();


	// Runs the UCSROBDD3 algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
	//
	void get_minima_list (unsigned int);

};

#endif /* UCS_ROBDD3_H_ */
