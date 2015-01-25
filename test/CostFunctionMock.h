//
// CostFunctionMock.h -- definition of the mock class "CostFunctionMock".
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

// A class to create mock objects, in order to test protected functions
// of class "MeanMutualInformation"

#ifndef COSTFUNCTIONMOCK_H_
#define COSTFUNCTIONMOCK_H_



#include "../src/global.h"
#include "../src/functions/MeanConditionalEntropy.h"
#include "../src/ElementSubset.h"
#include "../src/ElementSet.h"

class CostFunctionMock : public MeanConditionalEntropy
{

public:

	// Default constructor.
	//
	CostFunctionMock (ElementSet *);

	// Default destructor.
	//
	virtual ~CostFunctionMock ();

	// Methods for testing of the W-operator feature selection operations.
	//
	string print_W_operator_samples_frequencies (ElementSubset *);

	string print_label_frequencies (ElementSubset *);

	string print_conditional_entropy (ElementSubset *);

	// Tests the storage of the elapsed time of the required time
	// of all calls of the cost function
	//
	void add_elapsed_time (int microseconds);

	// Override to avoid the ambiguity due the multiple inheritance
	//
	int override_get_the_elapsed_time_of_the_calls_of_this_cost_function ();
};

#endif /* COSTFUNCTIONMOCK_H_ */
