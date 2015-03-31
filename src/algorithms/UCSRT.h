#ifndef UCSRT_H_
#define UCSRT_H_

#include "../ROBDD.h"
#include "../global.h"
#include "../Solver.h"
#include "../Collection.h"
#include "UCSRTToolBox.h"

class UCSRT : public Solver
{

private:

	// The collection of restrictions
	//
	ROBDD * restrictions;

	Collection * lower_restriction, * upper_restriction;
	



public:

	// Default constructor.
	//
	UCSRT ();


	// Default destructor.
	//
	virtual ~UCSRT ();


	// Runs the UCSRT algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
	//
	void get_minima_list (unsigned int);

};

#endif /* UCSRT_H_ */
