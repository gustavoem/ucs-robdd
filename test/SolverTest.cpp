//
// SolverTest.cpp -- implementation of the namespace "SolverTest".
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

#include "SolverTest.h"

namespace SolverTest {

	bool it_should_give_the_abs_sum_cost_of_a_subset(){
		ElementSet set ("set", "input/CostFunctionTest3ElementsFile.xml");
		ElementSubset I ("I", &set);
		ElementSubset O ("O", &set);
		ElementSubset X ("X", &set);
		ElementSubset Y ("Y", &set);
		ElementSubset Z ("X", &set);
		SolverMock s1;
		MeanAbsSum c (&set);
		s1.set_parameters (&c, &set, false);
		I.set_complete_subset();
		X.add_element(0);   // X = [101]
		X.add_element(2);
		Y.add_element(1);   // Y = [011]
		Y.add_element(2);
		Z.add_element(1);   // Z = [010]
		if ((s1.subset_cost(&I) == 4) &&
			(s1.subset_cost(&X) == 2) &&
			(s1.subset_cost(&Y) == 3) &&
			(s1.subset_cost(&Z) == 0) &&
			(s1.subset_cost(&O) == 2) )
			return true;
		else
			return false;
	}

	bool it_should_give_the_hamming_distance_cost_of_a_subset(){
		ElementSet set ("set", "input/SolverTest3ElementsFile.xml");
		ElementSubset I ("I", &set);
		ElementSubset O ("O", &set);
		ElementSubset X ("X", &set);
		ElementSubset Y ("Y", &set);
		ElementSubset Z ("X", &set);
		SolverMock s1;
		HammingDistance c (&set);
		s1.set_parameters (&c, &set, false);
		I.set_complete_subset();
		X.add_element(0);    // X = [101]
		X.add_element(2);
		Y.add_element(1);    // Y = [011]
		Y.add_element(2);
		Z.add_element(1);    // Z = [010]
		if ((s1.subset_cost(&I) == 1) &&
			(s1.subset_cost(&X) == 0) &&
			(s1.subset_cost(&Y) == 2) &&
			(s1.subset_cost(&Z) == 3) &&
			(s1.subset_cost(&O) == 2) )
			return true;
		else
			return false;
	}

	bool an_empty_set_should_have_cost_zero(){
		ElementSet set ("set", "input/ElementSetTestEmptyFile.xml");
		ElementSubset O ("O", &set);
		SolverMock s1, s2;
		MeanAbsSum c1 (&set);
		HammingDistance c2 (&set);
		s1.set_parameters (&c1, &set, false);
		s2.set_parameters (&c2, &set, false);

		if(s1.subset_cost (&O) != 0)
			return false;
		if(s2.subset_cost (&O) != 0)
			return false;
		return true;
	}

} // end of namespace
