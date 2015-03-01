#include "UCSROBDDToolBoxTest.h"

namespace UCSROBDDToolBoxTest {

	bool theres_no_minial_element_when_all_subsets_are_restricted ()
	{
		ElementSet elm_set ("", 2, 2);
		ElementSubset subset ("", &elm_set);
		subset.add_element (0);
		subset.add_element (1);
		ROBDD R (&elm_set);
		R.add_interval (&subset, false);
		ElementSubset * min_subset = UCSROBDDToolBox::get_minimal_subset (&R, &elm_set);
		bool ans = min_subset == NULL;
		return ans;
	}

	bool theres_no_maximal_element_when_all_subsets_are_restricted ()
	{
		ElementSet elm_set ("", 2, 2);
		ElementSubset subset ("", &elm_set);
		subset.add_element (0);
		subset.add_element (1);
		ROBDD R (&elm_set);
		R.add_interval (&subset, false);
		ElementSubset * max_subset = UCSROBDDToolBox::get_maximal_subset (&R, &elm_set);
		bool ans = max_subset == NULL;
		return ans;
	}

} // end of namespace

