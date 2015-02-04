#include "VertexTest.h"

namespace VertexTest {

	bool a_new_vertex_should_have_no_child ()
	{
		Element * elm = new Element (1, "elm_name");
		Vertex * new_vertex = new Vertex (elm);
		return (new_vertex->get_lo () == NULL) & (new_vertex->get_hi () == NULL);
	}

	bool its_possible_to_add_lo () 
	{
		Element * elm1 = new Element (1, "elm1_name");
		Element * elm2 = new Element (1, "elm2_name");
		Vertex * new_vertex = new Vertex (elm1);
		Vertex * new_lo = new Vertex (elm2);
		bool answ = new_vertex->set_child (new_lo, false);
		return answ;
	}

	bool its_possible_to_add_hi () 
	{
		Element * elm1 = new Element (1, "elm1_name");
		Element * elm2 = new Element (1, "elm2_name");
		Vertex * new_vertex = new Vertex (elm1);
		Vertex * new_hi = new Vertex (elm2);
		bool answ = new_vertex->set_child (new_hi, true);
		return answ;
	}
	
	bool a_terminal_vertex_should_have_no_var () 
	{
		Vertex * new_vertex = new Vertex (true);
		return new_vertex->get_var () == NULL;
	}

	bool a_nonterminal_vertex_should_have_no_value ()
	{
		Element * elm = new Element (1, "elm_name");
		Vertex * new_vertex = new Vertex (elm);
		return new_vertex->get_value () == -1;
	}

} // end of namespace

