//
// ElementSet.cpp -- implementation of the class "ElementSet".
//
//    This file is part of the featsel program
//    Copyright (C) 2016  Gustavo E. Matos
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

#include "FixedElementsSet.h"


using namespace std;

FixedElementsSet::FixedElementsSet (ElementSubset * sel_elms, 
    ElementSubset * non_sel_elms)
{
    this->set = sel_elms->get_set_that_contains_this_subset ();
    unsigned int set_size = set-get_cardinality ();
    this->selected_elements = new bool[set_size];
    this->non_selected_elements = new bool[set_size];
    
    for (unsigned int i = 0; i < set_size; i++) 
    {
        if (sel_elms->has_element (i))   
            selected_elements[i] = true;
        else
            selected_elements[i] = false;
        if (non_sel_elms->has_element (i))
            non_selected_elements[i] = true;
        else
            non_selected_elements[i] = false;
    }
}


FixedElementsSet::~FixedElementsSet ()
{
    delete[] selected_elements;
    delete[] non_selected_elements;
}


ElementSubset * getCorrespondentSubset (ElementSubset * subset)
{
    ElementSubset * X = new 
        ElementSubset (subset->get_set_that_contains_this_subset ());
    subset->copy (X);
    
}