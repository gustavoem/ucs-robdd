#ifndef UCS_ROBDD7_H_
#define UCS_ROBDD7_H_

#include "../ROBDD.h"
#include "../global.h"
#include "../Solver.h"
#include "UCSROBDDToolBox7.h"

class UCSROBDD7 : public Solver
{

private:

	// The collection of restrictions
	//
	ROBDD * restrictions;
	//ROBDD * lower_restriction, * upper_restriction;



public:

	// Default constructor.
	//
	UCSROBDD7 ();


	// Default destructor.
	//
	virtual ~UCSROBDD7 ();


	// Stores the number of reorder operations applied to the restrictions
	//
	unsigned int number_of_restrictions_reorders;


	// Stores the elapsed time (in microseconds) reodering restrictions
	//
	int elapsed_time_reordering_restrictions;


	// Runs the UCSROBDD7 algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
	//
	void get_minima_list (unsigned int);

};

#endif /* UCS_ROBDD7_H_ */
