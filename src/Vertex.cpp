#include "Vertex.h"


Vertex::Vertex (Element * elm, unsigned int id) 
{
	var = elm;
	lo = NULL;
	hi = NULL;
	this->id = id;
}


Vertex::Vertex (bool value, unsigned int id)
{
	var = NULL;
	lo = NULL;
	hi = NULL;
	this->value = value;
	this->id = id;
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


bool Vertex::is_terminal ()
{
	return var == NULL;
}