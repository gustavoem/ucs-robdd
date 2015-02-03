#include "ROBDD.h"


ROBDD::ROBDD (ElementSet * set)
{
	elm_set = set;
	root = new Vertex (false);
}


ROBDD::~ROBDD ()
{
	return;
}


Vertex * ROBDD::get_root()
{
	return root;
}


void ROBDD::print ()
{
	print (root);
}


void ROBDD::print (Vertex * v) 
{
	Element * var = v->get_var ();
	cout << var->get_element_name () << endl;
	if (var != NULL)
	{
		cout << "L ";
		print (v->get_lo ());
		cout << "R ";
		print (v->get_hi ());
		return;
	}
	cout << v->get_value () << endl;
}