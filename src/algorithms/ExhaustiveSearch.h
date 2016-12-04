//
// ExhaustiveSearch.h -- definition of the class "ExhaustiveSearch".
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

#ifndef EXHAUSTIVESEARCH_H_
#define EXHAUSTIVESEARCH_H_

#include "../global.h"
#include "../Solver.h"
#include "../ElementSubset.h"


class ExhaustiveSearch : public Solver{

public:

	// Default constructor.
	//
	ExhaustiveSearch ();

	// Default destructor.
	//
	virtual ~ExhaustiveSearch ();


	// Runs the UCurve algorithm, getting up to 'max_size_of_minima_list' minimum subsets.
	//
	void find_minima_list (unsigned int);

};

#endif /* EXHAUSTIVESEARCH_H_ */
