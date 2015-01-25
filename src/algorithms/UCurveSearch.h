//
// UCurveSearch.h -- definition of the class "UCurveSearch" (UCS).
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

#ifndef U_CURVE_SEARCH_H_
#define U_CURVE_SEARCH_H_

#include "../global.h"
#include "../Solver.h"
#include "../ElementSubset.h"
#include "UCurveToolBox.h"


class UCurveSearch : public Solver
{

private:

	// The collection of restrictions
	//
	Collection * lower_restriction, * upper_restriction;


public:

	// Default constructor.
	//
	UCurveSearch();


	// Default destructor.
	//
	virtual ~UCurveSearch();


	// Runs the UCurve algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
	//
	void get_minima_list(unsigned int);

};

#endif /* U_CURVE_SEARCH_H_ */
