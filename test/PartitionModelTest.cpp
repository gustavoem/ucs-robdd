//
// PartitionModelTest.cpp -- implementation of the namespace "PartitionModelTest".
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

#include "PartitionModelTest.h"

namespace PartitionModelTest
{

    bool it_should_create_the_fixed_elm_set ()
    {
        unsigned int set_size = 12;
        unsigned int nof_fixed = 0;
        ElementSet original_set ("", set_size, 100);
        bool * is_fixed = new bool[set_size];
        for (unsigned int i = 0; i < set_size; i++)
            if (i % 3)
            {
                is_fixed[i] = true;
                nof_fixed++;
            }
            else
                is_fixed[i] = false;
        PartitionModel part_model (&original_set, is_fixed);
        delete[] is_fixed;
        ElementSet * fixed_elm_set;
        fixed_elm_set = part_model.get_fixed_elm_set ();
        unsigned int fixed_set_size = fixed_elm_set->get_set_cardinality ();
        if (nof_fixed != fixed_set_size)
            return false;
        return true;
    }


    bool it_should_create_the_unfixed_elm_set ()
    {
        unsigned int set_size = 12;
        unsigned int nof_unfixed = 0;
        ElementSet original_set ("", set_size, 100);
        bool * is_fixed = new bool[set_size];
        for (unsigned int i = 0; i < set_size; i++)
            if (i % 3)
                is_fixed[i] = true;
            else
            {
                is_fixed[i] = false;
                nof_unfixed++;
            }
        PartitionModel part_model (&original_set, is_fixed);
        delete[] is_fixed;
        ElementSet * unfixed_elm_set;
        unfixed_elm_set = part_model.get_unfixed_elm_set ();
        unsigned int unfixed_set_size = unfixed_elm_set->get_set_cardinality ();
        if (nof_unfixed != unfixed_set_size)
            return false;
        return true;
    }


    // bool it_should_be_able_to_map_element_subsets ()
    // {
    //     bool answ;
    //     ElementSet original_set ("", 10, 100);
    //     ElementSubset selected ("", &original_set);
    //     ElementSubset non_selected ("", &original_set);
    //     ElementSubset expected_subset ("", &original_set);
    //     selected.add_element (0);
    //     selected.add_element (3);
    //     non_selected.add_element (7);
    //     PartitionModel part_model (&selected, &non_selected);
    //     ElementSet * new_set = part_model.get_unfixed_elm_set ();
    //     ElementSubset input_subset ("", new_set);
    //     input_subset.add_element (3);
    //     input_subset.add_element (4);
    //     expected_subset.add_element (0);
    //     expected_subset.add_element (3);
    //     expected_subset.add_element (5);
    //     expected_subset.add_element (6);
    //     ElementSubset * answ_subset = 
    //         part_model.get_orig_subset (&input_subset);
    //     if (!answ_subset->is_equal (&expected_subset))
    //         answ = false;
    //     else
    //         answ = true;
    //     delete answ_subset;
    //     return answ;
    // }

} // end namespace
