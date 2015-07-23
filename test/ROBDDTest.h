#ifndef ROBDDTEST_H_
#define ROBDDTEST_H_

#include "../src/ROBDD.h"
#include "../src/GeneticOrdering.h"

namespace ROBDDTest {

	bool a_new_robdd_has_only_a_terminal_node ();
	bool print_r ();
	bool the_union_of_a_new_robdd_with_itself_should_be_itself ();
	bool the_union_of_all_subsets_must_be_the_function_1 ();
	bool a_new_robdd_contais_no_subset ();
	bool an_added_subset_must_be_covered ();
	bool the_function_one_covers_all_subsets ();
	bool the_function_one_have_no_subset_evaluated_zero ();
	bool its_possible_to_get_a_random_subset_evaluated_zero ();
	bool the_robdd_maintains_a_log_of_restrictions ();
	bool it_should_represent_the_same_space_after_reordering ();

}

#endif /* ROBDDTEST_H_ */
