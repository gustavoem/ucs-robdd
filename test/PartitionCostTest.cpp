//
// PartitionCostTest.cpp -- implementation of the namespace "PartitionCostTest".
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

#include "PartitionCostTest.h"

namespace PartitionCostTest
{

    bool it_should_calculate_the_original_cost ()
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
        PartitionNode part (&part_model, &part_subset);

        AbsSum orig_cost_f (&original_set);
        PartitionCost p_model_f (&orig_cost_f, &part);
        ElementSubset X ("", part_model.get_unfixed_elm_set ());
        X.add_element (0);
        X.add_element (2);
        X.add_element (3);
        ElementSubset * orig_X = part.get_original_subset (&X);
        answ = orig_cost_f.cost (orig_X) == p_model_f.cost (&X);
        delete orig_X;
        return answ;
    }

} // end namespace
