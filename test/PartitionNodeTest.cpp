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

#include "PartitionNodeTest.h"

namespace PartitionNodeTest
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
        Partition part (&original_set, is_fixed);
        delete[] is_fixed;
        ElementSet * fixed_set = part.get_fixed_elm_set ();
        ElementSubset part_subset ("", fixed_set);
        part_subset.add_element (0);
        part_subset.add_element (2);
        part_subset.add_element (4);
        PartitionNode P (&part, &part_subset);

        ElementSubset expected_subset ("", &original_set);
        expected_subset.add_element (0);
        expected_subset.add_element (2);
        expected_subset.add_element (4);
        expected_subset.add_element (6);
        expected_subset.add_element (9);

        ElementSet * unfixed_set = part.get_unfixed_elm_set ();
        ElementSubset input_subset ("", unfixed_set);
        input_subset.add_element (6 - 5);
        input_subset.add_element (9 - 5);
        ElementSubset * answ_subset;
        answ_subset = P.get_original_subset (&input_subset);
        if (!answ_subset->is_equal (&expected_subset))
            answ = false;
        else
            answ = true;
        delete answ_subset;
        return answ;
    }

    bool it_should_check_upper_adjacent_partitions ()
    {
        bool answ = true;
        ElementSet original_set ("", 10, 100);
        bool fixed[10];
        for (unsigned int i = 0; i < 10; i++)
            fixed[i] = i < 5; // we are fixing the first 5 elements
        
        Partition * part = new Partition (&original_set, fixed);
        ElementSet * fixed_set = part->get_fixed_elm_set ();
        ElementSubset p_subset ("", fixed_set);
        ElementSubset q1_subset ("", fixed_set);
        ElementSubset q2_subset ("", fixed_set);
        p_subset.add_element (1);
        p_subset.add_element (3);
        q1_subset.add_element (1);
        q1_subset.add_element (3);
        q1_subset.add_element (4);
        q2_subset.add_element (2);
        PartitionNode * P = new PartitionNode (part, &p_subset);
        PartitionNode * Q1 = new PartitionNode (part, &q1_subset);
        PartitionNode * Q2 = new PartitionNode (part, &q2_subset);
        if (!Q1->is_upper_adjacent (P))
            answ = false;
        if (Q2->is_upper_adjacent (P))
            answ = false;
        delete P;
        delete Q1;
        delete Q2;
        delete part;
        return answ;
    }


    bool it_should_return_the_minimal_element ()
    {
        bool answ = true;
        ElementSet original_set ("", 10, 100);
        bool fixed[10];
        for (unsigned int i = 0; i < 10; i++)
            fixed[i] = i < 5; // we are fixing the first 5 elements
        
        Partition * part;
        part = new Partition (&original_set, fixed);
        ElementSet * fixed_set = part->get_fixed_elm_set ();
        ElementSubset p_subset ("", fixed_set);
        p_subset.add_element (0);
        p_subset.add_element (2);
        p_subset.add_element (3);
        PartitionNode P (part, &p_subset);
        ElementSubset expected_minimal ("", &original_set);
        expected_minimal.add_element (0);
        expected_minimal.add_element (2);
        expected_minimal.add_element (3);
        ElementSubset * answ_minimal = P.get_minimal_element ();
        if (!answ_minimal->is_equal (&expected_minimal))
            answ = false;
        delete part;
        delete answ_minimal;
        return answ;
    }


    bool it_should_return_the_maximal_element ()
    {
        bool answ = true;
        ElementSet original_set ("", 10, 100);
        bool fixed[10];
        for (unsigned int i = 0; i < 10; i++)
            fixed[i] = i < 5; // we are fixing the first 5 elements
        
        Partition * part;
        part = new Partition (&original_set, fixed);
        ElementSet * fixed_set = part->get_fixed_elm_set ();
        ElementSubset p_subset ("", fixed_set);
        p_subset.add_element (0);
        p_subset.add_element (2);
        p_subset.add_element (3);
        PartitionNode P (part, &p_subset);
        ElementSubset expected_maximal ("", &original_set);
        expected_maximal.add_element (0);
        expected_maximal.add_element (2);
        expected_maximal.add_element (3);
        expected_maximal.add_element (5);
        expected_maximal.add_element (6);
        expected_maximal.add_element (7);
        expected_maximal.add_element (8);
        expected_maximal.add_element (9);
        ElementSubset * answ_maximal = P.get_maximal_element ();
        if (!answ_maximal->is_equal (&expected_maximal))
            answ = false;
        delete part;
        delete answ_maximal;
        return answ;
    }
} // end namespace
