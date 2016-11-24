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

PartitionModel::PartitionModel (ElementSet * a_set, bool * is_fixed)
{
    this->original_set = new ElementSet (a_set);
    this->fixed_set_size = 0;
    unsigned int set_size = a_set->get_set_cardinality ();
    for (unsigned int i = 0; i < set_size; i++)
        if (is_fixed[i])
            fixed_set_size++;
    this->fixed_elm_map = new unsigned int[fixed_set_size];
    this->unfixed_elm_map = new unsigned int[set_size - fixed_set_size];
    unsigned int j = 0;
    unsigned int k = 0;
    for (unsigned int i = 0; i < set_size; i++)
        if (is_fixed[i])
            fixed_elm_map[j++] = i;
        else
            unfixed_elm_map[k++] = i;
    unsigned int a = fixed_set_size;
    unsigned int b = set_size - a;
    this->fixed_set   = new ElementSet (a_set, fixed_elm_map, a);
    this->unfixed_set = new ElementSet (a_set, unfixed_elm_map, b);
}


PartitionModel::~PartitionModel ()
{
    delete original_set;
    delete[] fixed_elm_map;
    delete[] unfixed_elm_map;
    delete fixed_set;
    delete unfixed_set;
}


// ElementSubset * PartitionModel::get_orig_subset (ElementSubset * subset)
// {
//     ElementSubset * orig_subset = new ElementSubset ("", original_set);
//     orig_subset->copy (selected_elements);
//     for (unsigned int i = 0; i < fixed_set_size; i++)
//         if (subset->has_element (i))
//             orig_subset->add_element (element_map[i]);
//     return orig_subset;
// }


ElementSet * PartitionModel::get_unfixed_elm_set ()
{
    return unfixed_set;
}


ElementSet * PartitionModel::get_fixed_elm_set ()
{
    return fixed_set;
}