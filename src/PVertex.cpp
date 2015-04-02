#include "PVertex.h"


PVertex::PVertex ()
{
	var = NULL;
	lo = NULL;
	hi = NULL;
}


PVertex::PVertex (Element * elm, unsigned int index) 
{
	var = elm;
	lo = NULL;
	hi = NULL;
	this->index = index;
	this->id = index;
}


PVertex::PVertex (bool value, unsigned int index)
{
	var = NULL;
	lo = NULL;
	hi = NULL;
	this->value = value;
	this->index = index;
	this->id = index;
}


PVertex::~PVertex () 
{
	this->hi = NULL;
	this->lo = NULL;
	this->var = NULL;
}

Element * PVertex::get_var ()
{
	return var;
}


void PVertex::set_var (Element * var)
{
	this->var = var;
}


PVertex * PVertex::get_child (bool side)
{
	if (side == true)
		return hi;
	return lo;
}


void PVertex::set_child (PVertex * vertex, bool side)
{
	if (side == true)
		hi = vertex;
	else 
		lo = vertex;
}


int PVertex::get_value ()
{
	if (var != NULL)
		return -1;
	return value;
}


void PVertex::set_value (int value)
{
	this->value = value;
}


unsigned int PVertex::get_id ()
{
	return id;
}


void PVertex::set_id (unsigned int id)
{
	this->id = id;
}


unsigned int PVertex::get_index ()
{
	return index;
}


void PVertex::set_index (unsigned int index)
{
	this->index = index;
}


bool PVertex::is_terminal ()
{
	return var == NULL;
}


void PVertex::add_parent (PVertex * v)
{
	parents.push_back (v);
}


PVertex * PVertex::get_some_parent ()
{
	if (parents.empty ())
		return NULL;
	else
		return parents.front ();
}