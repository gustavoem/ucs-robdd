#include "GeneticOrderingTest.h"

namespace GeneticOrderingTest {

	bool it_should_create_an_initial_population ()
	{	
		unsigned int setsize = 5;
		ElementSet elm_set ("", setsize, 2);
		ROBDD robdd (&elm_set);
		GeneticOrdering gen_ord (&robdd, 10, setsize);
		return true;
	}

} // end of namespace

