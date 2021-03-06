#ifndef UCSROBDD6TEST_H_
#define UCSROBDD6TEST_H_

#include "../src/algorithms/UCSROBDD6.h"
#include "../src/functions/MeanAbsSum.h"
#include "../src/functions/HammingDistance.h"
#include "../src/functions/Explicit.h"
#include "../src/functions/AbsSum.h"

namespace UCSROBDD6Test
{
	
	bool it_should_find_a_global_minimum ();
	bool it_should_converge_for_large_hamming_sets ();
	bool it_should_converge_for_large_abs_sum_sets ();
	bool it_should_always_give_the_correct_answer ();
	
}

#endif /* UCSROBDD6TEST_H_ */
