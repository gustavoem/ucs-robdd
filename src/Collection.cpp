//
// Collection.cpp -- implementation of the class "Collection".
//
//    This file is part of the featsel program
//    Copyright (C) 2010  Marcelo S. Reis
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "Collection.h"


Collection::Collection ()
{
	nof_consults = 0;
	nof_updates = 0;
	time_consulting = 0;
	time_updating = 0;
}


Collection::~Collection ()
{
	map<string, ElementSubset *>::iterator it;
	for (it = my_map.begin (); it != my_map.end (); it++)
		delete it->second;
	my_map.clear ();
}


bool Collection::lower_covers (ElementSubset * X)
{
	nof_consults++;
	timeval start, end;
	gettimeofday (& start, NULL);
	
	map<string, ElementSubset *>::iterator it;
	if (X == NULL)
	{
		cout << "Collection::lower_covers error: NULL subset!" << endl;
		return false;
	}
	for (it = my_map.begin (); it != my_map.end (); it++)
	{
		if (it->second->contains (X))
			return true;
	}

	gettimeofday (& end, NULL);
	time_consulting += (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));

	return false;
}


bool Collection::upper_covers (ElementSubset * X)
{
	nof_consults++;
	timeval start, end;
	gettimeofday (& start, NULL);

	map<string, ElementSubset *>::iterator it;
	if (X == NULL)
	{
		cout << "Collection::upper_covers error: NULL subset!" << endl;
		return false;
	}
	for (it = my_map.begin (); it != my_map.end (); it++)
	{
		if (it->second->is_contained_by (X))
			return true;
	}

	gettimeofday (& end, NULL);
	time_consulting += (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));

	return false;
}


unsigned int Collection::remove_lower_covered_subsets (ElementSubset * X)
{
	return remove_covered_subsets (X, true);
}


unsigned int Collection::remove_upper_covered_subsets (ElementSubset * X)
{
	return remove_covered_subsets (X, false);
}


string Collection::print_collection ()
{
	map<string, ElementSubset *>::iterator it;
	string collection_string ("");
	for (it = my_map.begin (); it != my_map.end (); it++)
		collection_string.append (it->second->print_subset ());
	return collection_string;
}


string Collection::print_collection (CostFunction * c)
{
	map<string, ElementSubset *>::iterator it;
	string collection_string ("");
	std::ostringstream value;
	for (it = my_map.begin (); it != my_map.end (); it++)
	{
		collection_string.append (it->second->print_subset ());
		collection_string.append (": ");
		value <<  c->cost (it->second);
		collection_string.append (value.str ());
		collection_string.append ("\n");
		value.str ("");
	}
	return collection_string;
}


void Collection::copy (Collection * C)
{
	map<string, ElementSubset *>::iterator it;
	for (it = C->my_map.begin (); it != C->my_map.end (); it++)
		if (! add_subset (it->second))
			cout << "Error copying collection!" << endl;
}


ElementSubset * Collection::add_subset (ElementSubset * X)
{
	nof_updates++;
	timeval start, end;
	gettimeofday (& start, NULL);

	pair<map<string, ElementSubset *>::iterator,bool> ret;
	ElementSubset * Y;
	Y = new ElementSubset ("", X->get_set_that_contains_this_subset());
	Y->copy (X);
	ret = my_map.insert (pair<string, ElementSubset *> (Y->print_subset (), Y));

	gettimeofday (& end, NULL);
	time_updating += (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));

	if (ret.second)
		return ret.first->second;
	else
	{
		delete Y;
		return NULL;
	}
}


ElementSubset * Collection::remove_last_subset ()
{
	timeval start, end;
	gettimeofday (& start, NULL);

	map<string, ElementSubset *>::iterator it;
	ElementSubset * X;
	it = my_map.begin ();
	X = it->second;
	my_map.erase (it);

	nof_updates++;
	gettimeofday (& end, NULL);
	time_updating += (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));
	
	return X;
}


bool Collection::has_subset (ElementSubset * X)
{
	nof_consults++;

	timeval start, end;
	gettimeofday (& start, NULL);

	if (my_map.find (X->print_subset ()) == my_map.end ()) 
	{
		gettimeofday (& end, NULL);
		time_consulting += (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));
		return false;
	}
	else
	{
		gettimeofday (& end, NULL);
		time_consulting += (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));
		return true;
	}
}


ElementSubset * Collection::get_subset (ElementSubset * X)
{
	nof_consults++;
	timeval start, end;
	gettimeofday (& start, NULL);
	
	map<string, ElementSubset *>::iterator it;
	it = my_map.find (X->print_subset ());

	gettimeofday (& end, NULL);
	time_consulting += (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));

	if (it == my_map.end ())
		return NULL;
	else
		return it->second;
}



unsigned int Collection::size ()
{
	return my_map.size ();
}



// Private methods

unsigned int Collection::remove_covered_subsets (ElementSubset * X, bool lower_cover)
{
	timeval start, end;
	gettimeofday (& start, NULL);

	unsigned int number_of_removed_subsets = 0;
	map<string, ElementSubset *>::iterator it;
	for (it = my_map.begin (); it != my_map.end (); it++)
	{
		if ( ( ( lower_cover) && (X->contains (it->second)) ) ||
		     ( (!lower_cover) && (X->is_contained_by (it->second)) ) )
		{
			delete it->second;
			my_map.erase (it);
			number_of_removed_subsets++;
			nof_updates++;
		}
	}

	gettimeofday (& end, NULL);
	time_updating += (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));

	return number_of_removed_subsets;
}

unsigned int Collection::get_nof_consults () 
{
	return nof_consults;
}


unsigned int Collection::get_nof_updates () 
{
	return nof_updates;
}


int Collection::get_time_consulting ()
{
	return time_consulting;
}


int Collection::get_time_updating ()
{
	return time_updating;
}