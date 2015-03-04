#include "UCSROBDDTest.h"

namespace UCSROBDDTest
{

	bool a_lattice_with_constant_cost_should_be_totally_exausted ()
	{
		ElementSet a_set1 ("S1", 3, 1);    // |S1| = 3
		ElementSet a_set2 ("S2", 10, 1);   // |S2| = 10
		ElementSet a_set3 ("S3", 1, 1);    // |S3| = 1
		MeanAbsSum c1 (&a_set1);
		MeanAbsSum c2 (&a_set2);
		MeanAbsSum c3 (&a_set3);
		UCSROBDD ucs1;
		UCSROBDD ucs2;
		UCSROBDD ucs3;
		string list;
		ucs1.set_parameters (&c1, &a_set1, false);
		ucs1.get_minima_list (8);
		list = ucs1.print_list_of_minima ();
		ucs2.set_parameters (&c2, &a_set2, false);
		ucs2.get_minima_list(1024);
		ucs3.set_parameters (&c3, &a_set3, false);
		ucs3.get_minima_list (2);

		if ((list.find ("<000>") != string::npos) &&
		    (list.find ("<001>") != string::npos) &&
		    (list.find ("<010>") != string::npos) &&
		    (list.find ("<011>") != string::npos) &&
		    (list.find ("<100>") != string::npos) &&
		    (list.find ("<101>") != string::npos) &&
		    (list.find ("<110>") != string::npos) &&
		    (list.find ("<111>") != string::npos) &&
		    (ucs1.number_of_minima () == 8) &&
		    (ucs2.number_of_minima () == 1024) &&
		    (ucs3.number_of_minima () == 2) )
			return true;
		else
			return false;
	}

} // end of namespace