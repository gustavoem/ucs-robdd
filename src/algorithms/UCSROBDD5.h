#ifndef UCS_ROBDD5_H_
#define UCS_ROBDD5_H_

#include "../ROBDD.h"
#include "../global.h"
#include "../Solver.h"
#include "UCSROBDDToolBox5.h"

class UCSROBDD5 : public Solver
{

private:

	// The collection of restrictions
	//
	ROBDD * restrictions;
	//ROBDD * lower_restriction, * upper_restriction;



public:

	// Default constructor.
	//
	UCSROBDD5 ();


	// Default destructor.
	//
	virtual ~UCSROBDD5 ();


	// Runs the UCSROBDD5 algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
	//
	void get_minima_list (unsigned int);

};

#endif /* UCS_ROBDD5_H_ */
