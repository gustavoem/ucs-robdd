//
// ElementSetTest.h -- definition of the namespace "ElementSetTest".
//
//    This file is part of the featsel program
//    Copyright (C) 2016  Gustavo Estrela de Matos
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

#ifndef PUCSR1TOOLBOXTEST_H_
#define PUCSR1TOOLBOXTEST_H_

#include "../src/algorithms/PUCSR1ToolBox.h"
#include "../src/ElementSubset.h"
#include "../src/ElementSet.h"
#include "../src/Partition.h"
#include "../src/PartitionNode.h"
#include "../src/Collection.h"
#include "../src/functions/AbsSum.h"

namespace PUCSR1ToolBoxTest
{

    bool it_should_find_the_part_minimum ();
    bool it_should_find_an_adjacent_part ();
    bool it_should_prune_and_walk ();
    
}

#endif /* PUCSR1TOOLBOXTEST_H_ */
