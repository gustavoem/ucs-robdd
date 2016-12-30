//
// Partition.cpp -- implementation of the class "Partition".
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

#include "PartitionNode.h"

PartitionNode::PartitionNode (Partition * partition, ElementSubset * X)
{
    this->selected_elements = new ElementSubset (X);
    this->partition = partition;
    find_minimal_subset ();
}


PartitionNode::PartitionNode (PartitionNode * Q) 
{
    this->selected_elements = new ElementSubset (Q->selected_elements);
    this->minimal_subset = new ElementSubset (Q->minimal_subset);
    this->partition = Q->partition;
}

PartitionNode::~PartitionNode ()
{
    delete selected_elements;
    delete minimal_subset;
}

void PartitionNode::find_minimal_subset ()
{
    ElementSet * fixed_set = partition->get_fixed_elm_set ();
    ElementSet * orig_set = partition->get_original_set ();
    minimal_subset = new ElementSubset ("", orig_set);
    unsigned int fixed_elm_set_size = fixed_set->get_set_cardinality ();
    unsigned int * fixed_map = partition->get_fixed_elm_map ();
    for (unsigned int i = 0; i < fixed_elm_set_size; i++)
    {
        if (selected_elements->has_element (i))
            minimal_subset->add_element (fixed_map[i]);
    }
}


ElementSubset * PartitionNode::get_original_subset (ElementSubset * X)
{
    ElementSet * orig_set = partition->get_original_set ();
    ElementSubset * orig_subset = new ElementSubset ("", orig_set);
    orig_subset->copy (minimal_subset);
    ElementSet * unfixed_set = partition->get_unfixed_elm_set ();
    unsigned int unfixed_set_size = unfixed_set->get_set_cardinality ();
    unsigned int * unfixed_map = partition->get_unfixed_elm_map ();
    for (unsigned int i = 0; i < unfixed_set_size; i++)
        if (X->has_element (i))
            orig_subset->add_element (unfixed_map[i]);
    return orig_subset;
}


ElementSet * PartitionNode::get_original_set ()
{
    return partition->get_original_set ();
}


ElementSubset * PartitionNode::get_selected_elements ()
{
    return new ElementSubset (selected_elements);
}


Partition * PartitionNode::get_partition ()
{
    return partition;
}


unsigned int PartitionNode::get_number_of_fixed_elms ()
{
    ElementSet * fixed_set = partition->get_fixed_elm_set ();
    unsigned int n = fixed_set->get_set_cardinality ();
    return n;
}


bool PartitionNode::is_upper_adjacent (PartitionNode * Q)
{
    bool answ = true;
    ElementSubset * intersect = new ElementSubset (selected_elements);
    intersect->subset_intersection (Q->selected_elements);
    if (intersect->get_subset_cardinality () != 
        Q->selected_elements->get_subset_cardinality ())
        answ = false;
    delete intersect;
    return answ;
}


ElementSubset * PartitionNode::get_least_subset ()
{
    return new ElementSubset (minimal_subset);
}


ElementSubset * PartitionNode::get_greatest_subset ()
{
    ElementSet * unfixed_set;
    ElementSubset * maximal;
    unsigned int n, * unfixed_map;

    unfixed_set = partition->get_unfixed_elm_set ();
    n = unfixed_set->get_set_cardinality ();
    unfixed_map = partition->get_unfixed_elm_map ();
    maximal = new ElementSubset (minimal_subset);
    for (unsigned int i = 0; i < n; i++)
        maximal->add_element (unfixed_map[i]);
    return maximal;
}