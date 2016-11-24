//
// PartitionTest.cpp -- implementation of the namespace "PartitionTest".
//
//    This file is part of the featsel program
//    Copyright (C) 2010  Gustavo Estrela de Matos
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

#include "PartitionTest.h"

namespace PartitionTest
{
    bool it_map_subsets_correctly ()
    {
        bool answ;
        unsigned int set_size = 12;
        ElementSet original_set ("", set_size, 100);
        bool * is_fixed = new bool[set_size];
        for (unsigned int i = 0; i < set_size; i++)
            if (i < 5)
                is_fixed[i] = true;
            else
                is_fixed[i] = false;
        PartitionModel part_model (&original_set, is_fixed);
        delete[] is_fixed;
        ElementSet * fixed_set = part_model.get_fixed_elm_set ();
        ElementSubset part_subset ("", fixed_set);
        part_subset.add_element (0);
        part_subset.add_element (2);
        part_subset.add_element (4);
        Partition part (&part_model, &part_subset);

        ElementSubset expected_subset ("", &original_set);
        expected_subset.add_element (0);
        expected_subset.add_element (2);
        expected_subset.add_element (4);
        expected_subset.add_element (6);
        expected_subset.add_element (9);

        ElementSet * unfixed_set = part_model.get_unfixed_elm_set ();
        ElementSubset input_subset ("", unfixed_set);
        input_subset.add_element (6 - 5);
        input_subset.add_element (9 - 5);
        ElementSubset * answ_subset;
        answ_subset = part.get_original_subset (&input_subset);
        if (!answ_subset->is_equal (&expected_subset))
            answ = false;
        else
            answ = true;
        delete answ_subset;
        return answ;
    }

} // end namespace
