#ifndef ORDERINGNODETEST_H_
#define ORDERINGNODETEST_H_

#include "../src/OrderingNode.h"
#include "../src/ROBDD.h"
#include "../src/GAROBDD.h"

namespace OrderingNodeTest {

	bool it_should_create_a_random_permutation ();
	bool it_should_represent_the_original_robdd ();
	bool it_should_recombine_to_other_permutations ();
	bool it_should_perform_a_mut ();
	bool it_should_perform_a_neighbour_mut ();

}

#endif /* ORDERINGNODETEST_H_ */
