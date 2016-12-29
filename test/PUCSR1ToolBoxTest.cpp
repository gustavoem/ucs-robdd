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
            fixed[i] = i < 2; // we are fixing the first 2 elements
        
        Partition * partition = new Partition (&original_set, fixed);
        ElementSet * fixed_set = partition->get_fixed_elm_set ();
        ElementSubset p_subset ("", fixed_set);
        p_subset.add_element (1);
        PartitionNode * P = new PartitionNode (partition, &p_subset);
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
        delete partition;
        delete P;
        delete L;
        delete c;
        return answ;
    }

    bool it_should_find_an_adjacent_partition ()
    {
        bool answ = true;
        ElementSet original_set ("", 5, 50);
        bool fixed[5];
        for (unsigned int i = 0; i < 5; i++)
            fixed[i] = i < 2; // we are fixing the first 2 elements
        
        Partition * partition = new Partition (&original_set, fixed);
        ElementSet * fixed_set = partition->get_unfixed_elm_set ();
        ElementSubset p_subset ("", fixed_set);
        p_subset.add_element (1);
        PartitionNode * P = new PartitionNode (partition, &p_subset);
        ElementSubset * p_fixed = P->get_selected_elements ();
        PartitionNode * Q = PUCSR1ToolBox::adjacent_partition (P, 0);
        ElementSubset * q_fixed = Q->get_selected_elements ();
        q_fixed->subset_intersection (p_fixed);
        if (q_fixed->get_subset_cardinality () != 1)
            answ = false;

        delete partition;
        delete P;
        delete Q;
        delete p_fixed;
        delete q_fixed;
        return answ;
    }

    bool it_should_prune_and_walk ()
    {
        bool answ = true;
        ElementSet original_set ("", 5, 50);
        bool fixed[5];
        for (unsigned int i = 0; i < 5; i++)
            fixed[i] = i < 2; // we are fixing the first 2 elements
        
        Partition * partition = new Partition (&original_set, fixed);
        ElementSet * fixed_set = partition->get_unfixed_elm_set ();
        ElementSubset p_subset ("", fixed_set);
        p_subset.add_element (1);
        PartitionNode * P = new PartitionNode (partition, &p_subset);
        PartitionNode * Q = PUCSR1ToolBox::adjacent_partition (P, 0); 
        // P = 01XXX
        // Q = 11XXX
        
        CostFunction * c = new AbsSum (&original_set);
        ROBDD * R = new ROBDD (fixed_set);

        PartitionNode * next;
        next = PUCSR1ToolBox::prune_and_walk (P, Q, c, R);
        ElementSubset * min1 = P->get_minimal_element ();
        ElementSubset * min2 = Q->get_minimal_element ();
        ElementSubset * max1 = P->get_maximal_element ();
        ElementSubset * max2 = Q->get_maximal_element ();
        if (next == NULL) 
        {
            if (!(c->cost (min2) > c->cost (min1)))
                answ = false;
            if (!(c->cost (max1) > c->cost (max2)))
                answ = false;
        }
        else if (next == P) 
        {
            if (c->cost (max1) > c->cost (max2))
                answ = false;
        }
        else if (next == Q)
        {
            if (!(c->cost (max1) > c->cost (max2)))
                answ = false;
            if (c->cost (max2) > c->cost (max1))
                answ = false;
        }

        delete c;
        delete min1;
        delete max1;
        delete min2;
        delete max2;
        delete R;
        delete P;
        delete Q;
        delete partition;
        return answ;
    }
}