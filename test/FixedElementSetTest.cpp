//
// FixedElementSetTest.cpp -- implementation of the namespace "FixedElementSetTest".
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

#include "FixedElementSetTest.h"

namespace FixedElementSetTest
{

    bool it_should_create_a_subproblem_elm_set ()
    {
        ElementSet original_set ("", 10, 100);
        ElementSubset selected ("", &original_set);
        ElementSubset non_selected ("", &original_set);
        selected.add_element (0);
        selected.add_element (3);
        non_selected.add_element (7);
        FixedElementSet fixed_elm_set (&selected, &non_selected);
        ElementSet * elm_set = fixed_elm_set.getUnfixedElementSet ();
        if (elm_set->get_set_cardinality () != 7)
            return false;
        return true;
    }

} // end namespace
