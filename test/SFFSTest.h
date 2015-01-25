//
// SFFSTest.h -- definition of the namespace "SFFSTest".
//
//    This file is part of the featsel program
//    Copyright (C) 2010  Marcelo S. Reis
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

#ifndef SFFSTEST_H_
#define SFFSTEST_H_

#include "../src/algorithms/SFFS.h"
#include "../src/functions/MeanAbsSum.h"
#include "../src/functions/HammingDistance.h"
#include "SFFSMock.h"

namespace SFFSTest
{

	bool it_should_add_the_best_element ();

	bool it_should_remove_the_worst_element ();

	bool it_should_find_a_local_minimum ();

	bool it_should_find_a_global_minimum ();

	bool it_should_store_all_the_visited_subsets ();

	bool it_should_give_the_number_of_the_visited_subsets ();

	bool it_should_converge_for_large_hamming_sets ();

	bool it_should_converge_for_large_abs_sum_sets ();

}

#endif /* SFFSTEST_H_ */
