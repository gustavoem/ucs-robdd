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


	// Used to set the number of reorderings
	//
	unsigned int intended_nof_reorderings;



public:

	// Default constructor.
	//
	UCSROBDD7 (unsigned int);


	// Default destructor.
	//
	virtual ~UCSROBDD7 ();


	// Runs the UCSROBDD7 algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
	//
	void get_minima_list (unsigned int);

};

#endif /* UCS_ROBDD7_H_ */
