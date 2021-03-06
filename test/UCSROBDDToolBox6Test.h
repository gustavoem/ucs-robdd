#ifndef UCSROBDDTOOLBOX6TEST_H_
#define UCSROBDDTOOLBOX6TEST_H_

#include "../src/algorithms/UCSROBDDToolBox6.h"
#include "../src/Collection.h"

namespace UCSROBDDToolBox6Test {

	bool it_should_return_null_when_theres_no_unvisited_adjacent ();
	bool it_should_return_an_unvisited_adjacent ();
	bool it_should_collect_the_minimum ();
	
}

#endif /* UCSROBDDTOOLBOX6TEST_H_ */
