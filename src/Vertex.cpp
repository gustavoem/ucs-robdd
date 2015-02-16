#include "Vertex.h"


Vertex::Vertex ()
{
	var = NULL;
	lo = NULL;
	hi = NULL;
}


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


void Vertex::set_var (Element * var)
{
	this->var = var;
}


Vertex * Vertex::get_child (bool side)
{
	if (side == true)
		return hi;
	return lo;
}


void Vertex::set_child(Vertex * vertex, bool side)
{
	if (side == true)
		hi = vertex;
	else 
		lo = vertex;
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


void Vertex::set_id (unsigned int id)
{
	this->id = id;
}


unsigned int Vertex::get_index ()
{
	return index;
}


void Vertex::set_index (unsigned int index)
{
	this->index = index;
}


bool Vertex::is_terminal ()
{
	return var == NULL;
}