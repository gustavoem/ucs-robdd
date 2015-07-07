//
// ElementSet.cpp -- implementation of the class "ElementSet".
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

# include "global.h"
# include "ElementSet.h"
# include "../parsers/XmlParserDriver.h"


using namespace std;

ElementSet::ElementSet (string set_name)
{
	if (set_name.length () > 0)
		name = set_name;
	else
		name = "S";
	number_of_elements = 0;
	list_of_elements = NULL;
	has_extra_element = false;
}


// this constructor uses the class "XMLParserDriver".
//
ElementSet::ElementSet (string a_set_name, string file_name)
{
	XmlParserDriver driver;
	list_of_elements = NULL;
	has_extra_element = false;
	number_of_elements = 0;

	if (driver.parse (file_name.data ()))
	{
		std::cout << "Error in ElementSet, processing the XML file!" << std::endl;
	}
	else
	{
		list_of_elements = driver.list_of_elements;
		number_of_elements = driver.number_of_elements;
		name = driver.set_name;
		explicit_cost = driver.explicit_cost;
	}

	set_elm_indexes ();
}


// loads .dat files, in order to perform W-operator feature selection
//
ElementSet::ElementSet (string file_name, unsigned int n)
{
	// example of a line of a .dat file with five elements:
	// 0 1 1 0  11 27\n
	// where the last two numbers are the number of occurrences of the labels
	// "0" and "1"  (in this case, "0" occurred 11 times and "1" 27 times).
	//
	//
	unsigned int i, max_number_of_values, current_value;
	long begin, end;
	ifstream my_file (file_name.c_str ());

	has_extra_element = true;
	name = "W-operator window";
	number_of_elements = n;

	begin = my_file.tellg ();
	my_file.seekg (0, ios::end);
	end = my_file.tellg ();
	my_file.seekg (0, ios::beg);
	// a conservative estimation, since the values of the last two numbers
	// often have more than 2 digits.
	max_number_of_values = (end - begin) / (2 * (number_of_elements + 2));

	// the extra positions is to store the classification for a given window state
	//
	list_of_elements = new Element * [number_of_elements + 2];
	if (list_of_elements == 0)
		cout << "Error in ElementSet: could not allocate memory for ElementSet elements!" << endl;

	for (i = 0; i < number_of_elements + 2; i++)
		list_of_elements [i] = new Element (max_number_of_values, "");

	i = 0;
	while (my_file >> current_value)
	{
		list_of_elements [i]->add_element_value (current_value);
		i++;
		if (i > (number_of_elements + 1))
			i = 0;
	}
	my_file.close ();

	set_elm_indexes ();
}


ElementSet::ElementSet (string set_name, unsigned int n, unsigned int range)
{
	unsigned int i;
	std::ostringstream stm;
	has_extra_element = false;
	number_of_elements = n;

	if(set_name.length () > 0)
		name = set_name;
	else
		name = "S";

	if (number_of_elements == 0)
		list_of_elements = NULL;
	else
	{
		list_of_elements = new Element*[number_of_elements];
		if (list_of_elements == 0)
			cout << "Error in ElementSet: could not allocate memory for elements!" << endl;
		srand ( (unsigned) time (NULL) );
		for (i = 0; i < n; i++)
		{
			stm.str ("");
			stm << "elem-" << i;
			list_of_elements[i] = new Element (1, stm.str ());
			if (range == 0)
				list_of_elements[i]->add_element_value (0);
			else
			{
				list_of_elements[i]->add_element_value ((int) rand () % range );
			}
		}
	}

	set_elm_indexes	();
}


ElementSet::~ElementSet ()
{
	unsigned int i;
	for (i = 0; i < number_of_elements; i++)
	{
		delete list_of_elements[i];
	}

	if (has_extra_element)
	{
		delete list_of_elements [number_of_elements];
		delete list_of_elements [number_of_elements + 1]; // 2 labels in W-operator table
	}

	if (list_of_elements != NULL)
		delete [] list_of_elements;
	explicit_cost.clear ();
}


void ElementSet::set_elm_indexes ()
{
	for (unsigned int i = 0; i < number_of_elements; i++)
		element_indexes.insert (make_pair (list_of_elements[i], i));
}


void ElementSet::print_list_of_elements ()
{
	unsigned int i;
	for (i = 0; i < number_of_elements; i++)
	{
		list_of_elements[i]->print_element ();
	}
}


unsigned int ElementSet::get_set_cardinality ()
{
	return number_of_elements;
}


Element * ElementSet::get_element (unsigned int index)
{
	if ( (has_extra_element && (index <= (number_of_elements + 1)) ) ||
		 (index < number_of_elements)
	   )
		return list_of_elements[index];
	else
		// ElementSet error: index out of range!
		return NULL;
}


unsigned int ElementSet::get_element_index (Element * elm)
{
	map<Element *, unsigned int>::iterator it = element_indexes.find (elm);
	if (it == element_indexes.end ())
		return -1;
	else
		return it->second;
}


string ElementSet::get_set_name ()
{
	return name;
}


float ElementSet::get_explicit_cost (string key)
{
	return explicit_cost [key];
	// if there is no element with a given key it returns the empty string ""
}



void ElementSet::permute_set ()
{
	unsigned int i, j, n;
	Element * * uniform_permutation, * k;

	n = number_of_elements + 1; // the extra element is used in MCE estimation

	uniform_permutation = new (nothrow) Element * [n];
	if (uniform_permutation == NULL)
		cout << "Error in ElementSet::permute_set : no memory available!\n";

	for (i = 0; i < n; i++)
		uniform_permutation[i] = list_of_elements[i];

	// PERMUTE-IN-PLACE algorithm
	for (i = 0; i < n - 1; i++)
	{
		srand ( (unsigned) time(NULL) );
		j = ((unsigned int) rand () % (n - i)) + i;   // random number between i and n
		k = uniform_permutation[i];
		uniform_permutation[i] = uniform_permutation[j];
		uniform_permutation[j] = k;
	}

	for (i = 0; i < number_of_elements; i++)
		list_of_elements[i] = uniform_permutation[i];

	if (uniform_permutation != NULL)
		delete [] uniform_permutation;
}
