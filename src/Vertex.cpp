#include "Vertex.h"


Vertex::Vertex (Element * elm) 
{
	var = elm;
	lo = NULL;
	hi = NULL;
}


Vertex::Vertex (bool value)
{
	var = NULL;
	lo = NULL;
	hi = NULL;
	this->value = value;
}


Vertex::~Vertex () 
{
	return;
}

Element * Vertex::get_var ()
{
	return var;
}


Vertex * Vertex::get_child (bool side)
{
	if (side == true)
		return hi;
	return lo;
}


bool Vertex::set_child(Vertex * vertex, bool side)
{
	if (side == true && hi == NULL)
		hi = vertex;
	else if (side == false && lo == NULL)
		lo = vertex;
	else
		return false;
	return true;

}


int Vertex::get_value()
{
	if (var != NULL)
		return -1;
	return value;
}


unsigned int Vertex::get_id ()
{
	return id;
}


void Vertex::set_id (unsigned int x)
{
	id = x;
}