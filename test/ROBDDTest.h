#ifndef ROBDDTEST_H_
#define ROBDDTEST_H_

#include "../src/ROBDD.h"

namespace ROBDDTest {

	bool a_new_robdd_has_only_a_terminal_node ();
	bool print_r ();
	bool the_union_of_a_new_robdd_with_itself_should_be_itself ();
	bool the_union_of_all_subsets_must_be_the_function_1 ();

}

#endif /* ROBDDTEST_H_ */
