#ifndef GAROBDD_H_
#define GAROBDD_H_

#include "ROBDD.h"

class GAROBDD : public ROBDD
{

public:

	GAROBDD (ElementSet *, list <pair <bool, ElementSubset *> > *, unsigned int *);

	virtual ~GAROBDD ();
	
};

#endif /* GAROBDD_H_ */
