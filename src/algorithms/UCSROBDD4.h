#ifndef UCS_ROBDD4_H_
#define UCS_ROBDD4_H_

#include "../ROBDD.h"
#include "../global.h"
#include "../Solver.h"
#include "UCSROBDDToolBox4.h"

class UCSROBDD4 : public Solver
{

private:

	// The collection of restrictions
	//
	ROBDD * restrictions;
	//ROBDD * lower_restriction, * upper_restriction;



public:

	// Default constructor.
	//
	UCSROBDD4 ();


	// Default destructor.
	//
	virtual ~UCSROBDD4 ();


	// Runs the UCSROBDD4 algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
	//
	void get_minima_list (unsigned int);

};

#endif /* UCS_ROBDD4_H_ */
