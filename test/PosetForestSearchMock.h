//
// PosetForestSearchMock.h -- definition of the mock class "PosetForestSearchMock".
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

// A class to create mock objects, in order to test the abstract class "Solver"

#ifndef SOLVER_MOCK_H_
#define SOLVER_MOCK_H_

#include "../src/global.h"
#include "../src/algorithms/PosetForestSearch.h"

class PosetForestSearchMock : public PosetForestSearch
{

public:

	void get_minima_list (unsigned int);

	PosetForestSearch::Node * lower_forest_branch_mock (map<string, Node *> *, map<string, Node *> *);

	PosetForestSearch::Node * upper_forest_branch_mock (map<string, Node *> *, map<string, Node *> *);

	void search_upper_children_mock
	     (map<string, Node *> *, Node *, ElementSubset *, ElementSubset *);

	void search_lower_children_mock
	     (map<string, Node *> *, Node *, ElementSubset *, ElementSubset *);

	void search_upper_root_mock (map<string, Node *> *, ElementSubset *);

	void search_lower_root_mock (map<string, Node *> *, ElementSubset *);

	void upper_forest_pruning_mock (map<string, Node *> *, Node *);

	void lower_forest_pruning_mock (map<string, Node *> *, Node *);

};

#endif /* SOLVER_MOCK_H_ */
