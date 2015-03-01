#include "UCSROBDDToolBoxTest.h"

namespace UCSROBDDToolBoxTest {

	bool theres_no_minial_element_when_all_subsets_are_restricted ()
	{
		ElementSet elm_set ("", 2, 2);
		ElementSubset subset ("", &elm_set);
		subset.add_element (0);
		subset.add_element (1);
		ROBDD R (&elm_set);
		UCSROBDDToolBox::update_lower_restriction (&R, &subset);
		ElementSubset * min_subset = UCSROBDDToolBox::get_minimal_subset (&R, &elm_set);
		bool ans = min_subset == NULL;
		return ans;
	}

	bool theres_no_maximal_element_when_all_subsets_are_restricted ()
	{
		ElementSet elm_set ("", 2, 2);
		ElementSubset subset ("", &elm_set);
		ROBDD R (&elm_set);
		UCSROBDDToolBox::update_upper_restriction (&R, &subset);
		ElementSubset * max_subset = UCSROBDDToolBox::get_maximal_subset (&R, &elm_set);
		bool ans = max_subset == NULL;
		delete max_subset;
		return ans;
	}

	bool when_empty_set_is_not_restricted_its_the_minimal_subset ()
	{
		ElementSet elm_set ("", 2, 2);
		ROBDD R (&elm_set);
		ElementSubset * min_subset = UCSROBDDToolBox::get_minimal_subset (&R, &elm_set);
		bool ans = min_subset->get_subset_cardinality () == 0;
		delete min_subset;
		return ans;
	}



} // end of namespace

