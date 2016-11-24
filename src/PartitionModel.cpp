//
// PartitionModel.cpp -- implementation of the class "PartitionModel".
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

#include "PartitionModel.h"

using namespace std;

PartitionModel::PartitionModel (ElementSubset * sel_elms, 
    ElementSubset * non_sel_elms)
{
    this->original_set = sel_elms->get_set_that_contains_this_subset ();
    unsigned int set_size = original_set->get_set_cardinality ();
    this->selected_elements     = new ElementSubset (sel_elms);
    this->non_selected_elements = new ElementSubset (non_sel_elms);
    unsigned int a = selected_elements->get_subset_cardinality ();
    unsigned int b = non_selected_elements->get_subset_cardinality ();
    this->fixed_set_size = set_size - (a + b);
    this->element_map = new unsigned int[fixed_set_size];
    unsigned int j = 0;
    for (unsigned int i = 0; i < set_size; i++)
        if (!sel_elms->has_element (i) &&
            !non_sel_elms->has_element (i))
            element_map[j++] = i;
    this->unfixed_set = new ElementSet (original_set, element_map, 
        fixed_set_size);
}


PartitionModel::~PartitionModel ()
{
    delete unfixed_set;
    delete selected_elements;
    delete non_selected_elements;
    delete[] element_map;
}


ElementSubset * PartitionModel::get_orig_subset (ElementSubset * subset)
{
    ElementSubset * orig_subset = new ElementSubset ("", original_set);
    orig_subset->copy (selected_elements);
    for (unsigned int i = 0; i < fixed_set_size; i++)
        if (subset->has_element (i))
            orig_subset->add_element (element_map[i]);
    return orig_subset;
}


ElementSet * PartitionModel::get_unfixed_elm_set ()
{
    return unfixed_set;
}