//
// PUCSR1ToolBoxTest.cpp -- implementation of the namespace 
// "PUCSR1ToolBoxTest".
//
//    This file is part of the featsel program
//    Copyright (C) 2016  Gustavo Estrela de Matos
//
//    This program is free software: you can redistribute it and/or 
//    modify it under the terms of the GNU General Public License as
//    published by the Free Software Foundation, either version 3 of the
//    License, or (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see 
//    <http://www.gnu.org/licenses/>.
//

#include "PUCSR1ToolBoxTest.h"

using namespace PUCSR1ToolBox;
namespace PUCSR1ToolBoxTest 
{
    bool it_should_get_a_partition_set ()
    {
        bool answ;
        ElementSet original_set ("", 10, 100);
        unsigned int map[7];
        for (unsigned int i = 0; i < 7; i++)
            map[i] = i; // we are fixing the first 7 elements
        ElementSet fixed_set (&original_set, map, 7);
        ElementSubset partition ("", &fixed_set);
        partition.add_element (0);
        partition.add_element (3);
        partition.add_element (5);
        PartitionSet * part_set;
        part_set = get_part_set (&partition, &original_set);
        ElementSubset expected_subset ("", &original_set);
        expected_subset.add_element (8);
        expected_subset.add_element (9);
        expected_subset.add_element (0);
        expected_subset.add_element (3);
        expected_subset.add_element (5);
        ElementSubset input_subset ("", &fixed_set);
        input_subset.add_element (8 - 7);
        input_subset.add_element (9 - 7);
        ElementSubset * out_subset;
        out_subset = part_set->get_orig_subset (&input_subset);
        if (out_subset->is_equal (&expected_subset))
            answ = true;
        else
            answ = false;
        delete part_set;
        delete out_subset;
        return answ;
    }
}