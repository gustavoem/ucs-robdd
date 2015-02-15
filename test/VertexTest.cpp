#include "VertexTest.h"

namespace VertexTest {

	bool a_new_vertex_should_have_no_child ()
	{
		Element * elm = new Element (1, "elm_name");
		Vertex * new_vertex = new Vertex (elm, 1);
		bool answ = (new_vertex->get_child (false) == NULL) & (new_vertex->get_child (true) == NULL);
		delete elm;
		delete new_vertex;
		return answ;
	}

	bool a_terminal_vertex_should_have_no_var () 
	{
		Vertex * new_vertex = new Vertex (true, 1);
		bool answ = new_vertex->get_var () == NULL;
		delete new_vertex;
		return answ;
	}

	bool a_nonterminal_vertex_should_have_no_value ()
	{
		Element * elm = new Element (1, "elm_name");
		Vertex * new_vertex = new Vertex (elm, 1);
		bool answ = new_vertex->get_value () == -1;
		delete new_vertex;
		delete	elm;
		return answ;
	}

} // end of namespace

