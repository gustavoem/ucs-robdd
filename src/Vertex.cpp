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


Vertex * Vertex::get_lo ()
{
	return lo;
}


bool Vertex::set_lo(Vertex * vertex)
{
	if (lo == NULL)
		lo = vertex;
	else
		return false;
	return true;
}


Vertex * Vertex::get_hi ()
{
	return hi;
}


bool Vertex::set_hi(Vertex * vertex)
{
	if (hi == NULL)
		hi = vertex;
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
