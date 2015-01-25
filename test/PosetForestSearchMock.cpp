//
// PosetForestSearchMock.cpp -- implementation of the mock class "PosetForestSearchMock".
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

#include "PosetForestSearchMock.h"

void PosetForestSearchMock::get_minima_list (unsigned int max_size_of_minima_list)
{
	return;
}


PosetForestSearch::Node * PosetForestSearchMock::lower_forest_branch_mock
       (map<string, Node *> * Forest_A, map<string, Node *> * Forest_B)
{
	return lower_forest_branch (Forest_A, Forest_B);
}


PosetForestSearch::Node * PosetForestSearchMock::upper_forest_branch_mock
       (map<string, Node *> * Forest_A, map<string, Node *> * Forest_B)
{
	return upper_forest_branch (Forest_A, Forest_B);
}


void PosetForestSearchMock::search_upper_children_mock
     (map<string, Node *> * Forest_A, Node * N, ElementSubset * M, ElementSubset * Y)
{
	search_upper_children (Forest_A, N, M, Y);
}


void PosetForestSearchMock::search_lower_children_mock
	(map<string, Node *> * Forest_B, Node * N, ElementSubset * M, ElementSubset * Y)
{
	search_lower_children (Forest_B, N, M, Y);
}

void PosetForestSearchMock::search_upper_root_mock
     (map<string, Node *> * Forest_B, ElementSubset * M)
{
	search_upper_root (Forest_B, M);
}


void PosetForestSearchMock::search_lower_root_mock
	(map<string, Node *> * Forest_A, ElementSubset * M)
{
	search_lower_root (Forest_A, M);
}


void PosetForestSearchMock::upper_forest_pruning_mock
	(map<string, Node *> * Forest_B, Node * N)
{
	upper_forest_pruning (Forest_B, N);
}


void PosetForestSearchMock::lower_forest_pruning_mock
	(map<string, Node *> * Forest_A, Node * N)
{
	lower_forest_pruning (Forest_A, N);
}

