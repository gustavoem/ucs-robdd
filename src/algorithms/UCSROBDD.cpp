#include "UCSROBDD.h"

UCSROBDD::UCSROBDD ()
{
	/*lower_restriction = new ROBDD (set);
	upper_restriction = new ROBDD (set);*/
	restrictions = new ROBDD (set);
	list_of_visited_subsets = new Collection ();
	cost_function = NULL;
}


UCSROBDD::~UCSROBDD ()
{
	/*delete lower_restriction;
	delete upper_restriction;*/
	delete restrictions;
	delete list_of_visited_subsets;
}


void UCSROBDD::get_minima_list (unsigned int max_size_of_minima_list)
{
	
}