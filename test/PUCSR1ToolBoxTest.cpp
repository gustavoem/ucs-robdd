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
//    but WITHOUT ANY WARRANTY; without even txhe implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see 
//    <http://www.gnu.org/licenses/>.
//

#include "PUCSR1ToolBoxTest.h"

// using namespace PUCSR1ToolBox;
namespace PUCSR1ToolBoxTest {

    bool it_should_find_the_partition_minimum ()
    {
        bool answ = true;
        ElementSet original_set ("", 5, 50);
        bool fixed[5];
        for (unsigned int i = 0; i < 5; i++)
            fixed[i] = i < 2; // we are fixing the first 6 elements
        
        PartitionModel * part_model;
        part_model = new PartitionModel (&original_set, fixed);
        ElementSet * fixed_set = part_model->get_unfixed_elm_set ();
        ElementSubset p_subset ("", fixed_set);
        p_subset.add_element (1);
        Partition * P = new Partition (part_model, &p_subset);
        Collection * L = new Collection ();
        CostFunction * c = new AbsSum (&original_set);
        PUCSR1ToolBox::partition_minimum (P, L, c, 5);
        ElementSubset p_maximal ("", &original_set);
        p_maximal.add_element (1);
        p_maximal.add_element (2);
        p_maximal.add_element (3);
        p_maximal.add_element (4);
        ElementSubset p_minimal ("", &original_set);
        p_minimal.add_element (1);
        
        while (L->size () > 0)
        {
            ElementSubset * X = L->remove_last_subset ();
            if (!X->is_contained_by (&p_maximal))
                answ = false;
            if (!X->contains (&p_minimal))
                answ = false;
            delete X;
        }
        delete part_model;
        delete P;
        delete L;
        delete c;
        return answ;
    }
}