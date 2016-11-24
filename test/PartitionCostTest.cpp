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
        ElementSet original_set ("", 10, 100);
        ElementSubset selected ("", &original_set);
        ElementSubset non_selected ("", &original_set);
        selected.add_element (0);
        selected.add_element (2);
        non_selected.add_element (1);
        PartitionModel p_model (&selected, &non_selected);
        AbsSum orig_cost_f (&original_set);
        PartitionCost p_model_f (&orig_cost_f, &p_model);
        ElementSubset X ("", p_model.get_unfixed_elm_set ());
        X.add_element (0);
        X.add_element (2);
        X.add_element (6);
        ElementSubset * orig_X = p_model.get_orig_subset (&X);
        answ = orig_cost_f.cost (orig_X) == p_model_f.cost (&X);
        delete orig_X;
        return answ;
    }

} // end namespace
