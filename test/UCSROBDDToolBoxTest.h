#ifndef UCSROBDDTOOLBOXTEST_H_
#define UCSROBDDTOOLBOXTEST_H_

#include "../src/algorithms/UCSROBDDToolBox.h"

namespace UCSROBDDToolBoxTest {

	bool theres_no_minial_element_when_all_subsets_are_restricted ();
	bool theres_no_maximal_element_when_all_subsets_are_restricted ();
	bool when_empty_set_is_not_restricted_its_the_minimal_subset ();
	bool it_should_return_null_when_theres_no_unvisited_adjacent ();
	bool it_should_return_an_unvisited_adjacent ();
	
}

#endif /* UCSROBDDTOOLBOXTEST_H_ */
