//
// MeanAbsSum.h -- definition of the class "MeanAbsSum".
//
//    This file is part of the featsel program
//    Copyright (C) 2010  Marcelo S. Reis
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef MEAN_ABS_SUM_H_
#define MEAN_ABS_SUM_H_


#include "../global.h"
#include "../ElementSet.h"
#include "../ElementSubset.h"
#include "../CostFunction.h"

class MeanAbsSum : public CostFunction
{

protected:

	// t is the average of all values
	//
	int t;


public:

	// Default constructor.
	//
	MeanAbsSum (ElementSet *);


	// Default destructor.
	//
	virtual ~MeanAbsSum ();


	// Returns the value of c(X), where X is a subset.
	//
	float cost (ElementSubset *);

};

#endif /* MEAN_ABS_SUM_H_ */
