//============================================================================
// Name        : featselTest.cpp -- Unit tests of the featsel classes.
// Author      : Marcelo S Reis
// Version     : 0.1
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
//============================================================================


// Special data structures
//
#include "ElementTest.h"
#include "ElementSetTest.h"
#include "ElementSubsetTest.h"
#include "CollectionTest.h"

#include "VertexTest.h"
#include "ROBDDTest.h"

#include "UCSROBDDToolBoxTest.h"
#include "UCSROBDDToolBox4Test.h"
#include "UCSROBDDTest.h"
#include "UCSROBDD3Test.h"

#include "GeneticOrderingTest.h"
#include "OrderingNodeTest.h"

// Objective functions
//
#include "CostFunctionTest.h"


// Solvers
//
#include "SolverTest.h"
//
// Sub-optimal solvers
#include "SFSTest.h"
#include "SFFSTest.h"
//
// Optimal solvers
#include "BranchAndBoundTest.h"
#include "ExhaustiveSearchTest.h"
#include "PosetForestSearchTest.h"
#include "UCurveToolBoxTest.h"
#include "UCurveSearchTest.h"


// Number of passed and failed tests
//
unsigned int number_of_passed_tests = 0;
unsigned int number_of_failed_tests = 0;

void printResult (bool passed)
{
	if (passed)
	{
		cout << " OK\n";
		number_of_passed_tests++;
	}
	else
	{
		cout << " FAILED\n";
		number_of_failed_tests++;
	}
}

int main(void) {

	cout << endl << "Starting Unit Tests... " << endl << endl;
/*
	// Testing Class "Element"
	cout << "ElementTest::an_element_should_have_a_name";
	cout.flush ();
	printResult (ElementTest::an_element_should_have_a_name ());
	cout << "ElementTest::a_new_element_should_not_have_added_values";
	cout.flush ();
	printResult (ElementTest::a_new_element_should_not_have_added_values ());
	cout << "ElementTest::an_element_without_all_values_added_should_allow_adding";
	cout.flush ();
	printResult (ElementTest::an_element_without_all_values_added_should_allow_adding ());
    cout << "ElementTest::an_element_with_all_values_added_should_not_allow_adding";
	cout.flush ();
	printResult (ElementTest::an_element_with_all_values_added_should_not_allow_adding ());
	cout << "ElementTest::an_added_value_should_be_found";
	cout.flush ();
	printResult (ElementTest::an_added_value_should_be_found ());
	cout << endl;
*/
	// Testing Class "ElementSet"
/*	cout << "ElementSetTest::a_set_should_have_a_name";
	cout.flush ();
	printResult (ElementSetTest::a_set_should_have_a_name ());
	cout << "ElementSetTest::an_empty_set_should_not_have_elements";
	cout.flush ();
	printResult (ElementSetTest::an_empty_set_should_not_have_elements ());
	cout << "ElementSetTest::it_should_load_data_of_a_set_from_file";
	cout.flush ();
	printResult (ElementSetTest::it_should_load_data_of_a_set_from_file ());
	cout << "ElementSetTest::it_should_load_data_of_a_set_from_a_DAT_file";
	cout.flush ();
	printResult (ElementSetTest::it_should_load_data_of_a_set_from_a_DAT_file ());
	cout << "ElementSetTest::it_should_create_a_set_with_random_values";
	cout.flush ();
	printResult (ElementSetTest::it_should_create_a_set_with_random_values ());
	cout << "ElementSetTest::it_should_return_the_set_cardinality";
	cout.flush ();
	printResult (ElementSetTest::it_should_return_the_set_cardinality ());
	cout << "ElementSetTest::it_should_return_an_element_that_belongs_to_the_set";
	cout.flush ();
	printResult (ElementSetTest::it_should_return_an_element_that_belongs_to_the_set ());
	cout << "ElementSetTest::it_should_not_return_an_element_that_not_belongs_to_the_set";
	cout.flush ();
	printResult (ElementSetTest::it_should_not_return_an_element_that_not_belongs_to_the_set ());
	cout << "ElementSetTest::values_from_a_random_set_should_be_within_the_given_range";
	cout.flush ();
	printResult (ElementSetTest::values_from_a_random_set_should_be_within_the_given_range ());
	cout << "ElementSetTest::it_should_store_element_index";
	cout.flush ();
	printResult (ElementSetTest::it_should_store_element_index ());
	cout << endl;*/
/*
	// Testing Class "ElementSubset"
	cout << "ElementSubsetTest::a_new_subset_should_be_an_empty_set";
	cout.flush ();
	printResult (ElementSubsetTest::a_new_subset_should_be_an_empty_set ());
	cout << "ElementSubsetTest::an_element_not_in_subset_should_be_added";
	cout.flush ();
	printResult (ElementSubsetTest::an_element_not_in_subset_should_be_added ());
	cout << "ElementSubsetTest::an_element_in_subset_should_be_removed";
	cout.flush ();
	printResult (ElementSubsetTest::an_element_in_subset_should_be_removed ());
	cout << "ElementSubsetTest::it_should_give_the_set_that_belongs_the_subset";
	cout.flush ();
	printResult (ElementSubsetTest::it_should_give_the_set_that_belongs_the_subset ());
	cout << "ElementSubsetTest::a_set_should_contains_its_subset";
	cout.flush ();
	printResult (ElementSubsetTest::a_set_should_contains_its_subset ());
	cout << "ElementSubsetTest::a_subset_should_be_contained_by_its_set";
	cout.flush ();
	printResult (ElementSubsetTest::a_subset_should_be_contained_by_its_set ());
	cout << "ElementSubsetTest::a_subset_should_be_successfully_cloned";
	cout.flush ();
	printResult (ElementSubsetTest::a_subset_should_be_successfully_cloned ());
	cout << "ElementSubsetTest::a_random_element_should_be_removed";
	cout.flush ();
	printResult (ElementSubsetTest::a_random_element_should_be_removed ());
	cout << "ElementSubsetTest::it_should_give_the_complement_of_the_set";
	cout.flush ();
	printResult (ElementSubsetTest::it_should_give_the_complement_of_the_set ());
	cout << endl;

    // Testing Class "Collection"
    cout << "CollectionTest::a_lower_covered_subset_should_be_found";
	cout.flush ();
	printResult (CollectionTest::a_lower_covered_subset_should_be_found ());
	cout << "CollectionTest::a_non_lower_covered_subset_should_not_be_found";
	cout.flush ();
	printResult (CollectionTest::a_non_lower_covered_subset_should_not_be_found ());
	cout << "CollectionTest::it_should_remove_lower_covered_subsets_in_a_collection";
	cout.flush ();
	printResult (CollectionTest::it_should_remove_lower_covered_subsets_in_a_collection ());
	cout << "CollectionTest::the_evaluated_subset_should_not_be_deleted";
	cout.flush ();
	printResult (CollectionTest::the_evaluated_subset_should_not_be_deleted ());
	cout << "CollectionTest::an_upper_covered_subset_should_be_found";
	cout.flush ();
	printResult (CollectionTest::an_upper_covered_subset_should_be_found ());
	cout << "CollectionTest::a_non_upper_covered_subset_should_not_be_found";
	cout.flush ();
	printResult (CollectionTest::a_non_upper_covered_subset_should_not_be_found ());
	cout << "CollectionTest::it_should_remove_upper_covered_subsets_in_a_collection";
	cout.flush ();
	printResult (CollectionTest::it_should_remove_upper_covered_subsets_in_a_collection ());
	cout << "CollectionTest::it_should_copy_a_collection";
	cout.flush ();
	printResult (CollectionTest::it_should_copy_a_collection ());
	cout << endl;

	// Testing Class "CostFunction"
	//

	//
	// Explicit cost function
	//
	cout << "CostFunctionTest::it_should_works_with_an_explicitly_declared_cost_function";
	cout.flush ();
	printResult (CostFunctionTest::it_should_works_with_an_explicitly_declared_cost_function ());
	//
	// Mean conditional entropy for W-operator feature selection
	//
	cout << "CostFunctionTest::it_should_store_the_frequencies_of_the_samples";
	cout.flush ();
	printResult (CostFunctionTest::it_should_store_the_frequencies_of_the_samples ());
	cout << "CostFunctionTest::it_should_store_the_label_frequencies_of_the_samples";
	cout.flush ();
	printResult (CostFunctionTest::it_should_store_the_label_frequencies_of_the_samples ());
	cout << "CostFunctionTest::it_should_calculate_the_conditional_entropy";
	cout.flush ();
	printResult (CostFunctionTest::it_should_calculate_the_conditional_entropy ());
	//
	// Testing the storage of the elapsed time of all calls of the cost function
	//
	cout << "CostFunctionTest::it_should_add_and_retrieve_the_elapsed_time";
	cout.flush ();
	printResult (CostFunctionTest::it_should_add_and_retrieve_the_elapsed_time ());
	cout << endl;

	// Testing Class "Solver"
	cout << "SolverTest::it_should_give_the_abs_sum_cost_of_a_subset";
	cout.flush ();
	printResult (SolverTest::it_should_give_the_abs_sum_cost_of_a_subset ());
	cout << "SolverTest::it_should_give_the_hamming_distance_cost_of_a_subset";
	cout.flush ();
	printResult (SolverTest::it_should_give_the_hamming_distance_cost_of_a_subset ());
	cout << "SolverTest::an_empty_set_should_have_cost_zero";
	cout.flush ();
	printResult (SolverTest::an_empty_set_should_have_cost_zero ());
	cout << endl;

	// Testing Class "UCurveToolBox"
	cout << "UCurveToolBoxTest::it_should_not_update_lower_restriction_set_with_a_covered_subset";
	cout.flush ();
	printResult (UCurveToolBoxTest::it_should_not_update_lower_restriction_set_with_a_covered_subset ());
	cout << "UCurveToolBoxTest::it_should_update_lower_restriction_set_with_an_outer_subset";
	cout.flush ();
	printResult (UCurveToolBoxTest::it_should_update_lower_restriction_set_with_an_outer_subset ());
	cout << "UCurveToolBoxTest::it_should_not_update_upper_restriction_set_with_a_covered_subset";
	cout.flush ();
	printResult (UCurveToolBoxTest::it_should_not_update_upper_restriction_set_with_a_covered_subset ());
	cout << "UCurveToolBoxTest::it_should_update_upper_restriction_set_with_an_outer_subset";
	cout.flush ();
	printResult (UCurveToolBoxTest::it_should_update_upper_restriction_set_with_an_outer_subset ());
	cout << "UCurveToolBoxTest::it_should_get_a_maximal_subset";
	cout.flush ();
	printResult (UCurveToolBoxTest::it_should_get_a_maximal_subset ());
	cout << "UCurveToolBoxTest::it_should_get_a_minimal_subset";
	cout.flush ();
	printResult (UCurveToolBoxTest::it_should_get_a_minimal_subset ());
	cout << endl;

	// Testing Class "UCurveSearch"
	cout << "UCurveSearchTest::a_lattice_with_constant_cost_should_be_totally_exausted";
	cout.flush ();
	printResult (UCurveSearchTest::a_lattice_with_constant_cost_should_be_totally_exausted ());
	cout << "UCurveSearchTest::it_should_find_a_global_minimum";
	cout.flush ();
	printResult (UCurveSearchTest::it_should_find_a_global_minimum ());
	cout << "UCurveSearchTest::it_should_converge_for_large_hamming_sets";
	cout.flush ();
	printResult (UCurveSearchTest::it_should_converge_for_large_hamming_sets ());
	cout << "UCurveSearchTest::it_should_converge_for_large_abs_sum_sets";
	cout.flush ();
	printResult (UCurveSearchTest::it_should_converge_for_large_abs_sum_sets());
	cout << "UCurveSearchTest::it_should_store_all_the_visited_subsets";
	cout.flush ();
	printResult (UCurveSearchTest::it_should_store_all_the_visited_subsets ());
	cout << "UCurveSearchTest::it_should_give_the_number_of_the_visited_subsets";
	cout.flush ();
	printResult (UCurveSearchTest::it_should_give_the_number_of_the_visited_subsets ());
	cout << "UCurveSearchTest::it_should_always_give_the_correct_answer";
	cout.flush ();
	printResult (UCurveSearchTest::it_should_always_give_the_correct_answer ());
	cout << endl;

	// Testing Class "BranchAndBound"
	cout << "BranchAndBoundTest::a_lattice_with_constant_cost_should_be_totally_exausted";
	cout.flush ();
	printResult (BranchAndBoundTest::a_lattice_with_constant_cost_should_be_totally_exausted ());
	cout << "BranchAndBoundTest::it_should_find_a_global_minimum";
	cout.flush ();
	printResult (BranchAndBoundTest::it_should_find_a_global_minimum ());
	cout << "BranchAndBoundTest::it_should_converge_for_large_hamming_sets";
	cout.flush ();
	printResult (BranchAndBoundTest::it_should_converge_for_large_hamming_sets ());
	cout << "BranchAndBoundTest::it_should_converge_for_large_abs_sum_sets";
	cout.flush ();
	printResult (BranchAndBoundTest::it_should_converge_for_large_abs_sum_sets());
	cout << "BranchAndBoundTest::it_should_store_all_the_visited_subsets";
	cout.flush ();
	printResult (BranchAndBoundTest::it_should_store_all_the_visited_subsets ());
	cout << "BranchAndBoundTest::it_should_give_the_number_of_the_visited_subsets";
	cout.flush ();
	printResult (BranchAndBoundTest::it_should_give_the_number_of_the_visited_subsets ());
	cout << "BranchAndBoundTest::it_should_always_give_the_correct_answer";
	cout.flush ();
	printResult (BranchAndBoundTest::it_should_always_give_the_correct_answer ());
	cout << endl;

	// Testing Class "PosetForestSearch"
    //
	// Tests of the subroutines
	cout << "PosetForestSearchTest::it_should_branch_in_a_lower_tree";
	cout.flush ();
	printResult (PosetForestSearchTest::it_should_branch_in_a_lower_tree ());
	cout << "PosetForestSearchTest::it_should_branch_in_an_upper_tree";
	cout.flush ();
	printResult (PosetForestSearchTest::it_should_branch_in_an_upper_tree ());
	cout << "PosetForestSearchTest::it_should_search_the_lower_children";
	cout.flush ();
	printResult (PosetForestSearchTest::it_should_search_the_lower_children ());
	cout << "PosetForestSearchTest::it_should_search_the_upper_children";
	cout.flush ();
	printResult (PosetForestSearchTest::it_should_search_the_upper_children ());
	cout << "PosetForestSearchTest::it_should_search_a_lower_root";
	cout.flush ();
	printResult (PosetForestSearchTest::it_should_search_a_lower_root ());
	cout << "PosetForestSearchTest::it_should_search_an_upper_root";
	cout.flush ();
	printResult (PosetForestSearchTest::it_should_search_an_upper_root ());
	cout << "PosetForestSearchTest::it_should_prune_a_lower_tree";
	cout.flush ();
	printResult (PosetForestSearchTest::it_should_prune_a_lower_tree ());
	cout << "PosetForestSearchTest::it_should_prune_an_upper_tree";
	cout.flush ();
	printResult (PosetForestSearchTest::it_should_prune_an_upper_tree ());
	// Tests of the main algorithm
	cout << "PosetForestSearchTest::a_poset_with_constant_cost_should_be_totally_exausted";
	cout.flush ();
	printResult (PosetForestSearchTest::a_poset_with_constant_cost_should_be_totally_exausted ());
	cout << "PosetForestSearchTest::it_should_find_a_global_minimum";
	cout.flush ();
	printResult (PosetForestSearchTest::it_should_find_a_global_minimum ());
	cout << "PosetForestSearchTest::it_should_converge_for_large_hamming_sets";
	cout.flush ();
	printResult (PosetForestSearchTest::it_should_converge_for_large_hamming_sets ());
	cout << "PosetForestSearchTest::it_should_converge_for_large_abs_sum_sets";
	cout.flush ();
	printResult (PosetForestSearchTest::it_should_converge_for_large_abs_sum_sets());
	cout << "PosetForestSearchTest::it_should_store_all_the_visited_subsets";
	cout.flush ();
	printResult (PosetForestSearchTest::it_should_store_all_the_visited_subsets ());
	cout << "PosetForestSearchTest::it_should_give_the_number_of_the_visited_subsets";
	cout.flush ();
	printResult (PosetForestSearchTest::it_should_give_the_number_of_the_visited_subsets ());
	cout << "PosetForestSearchTest::it_should_always_give_the_correct_answer";
	cout.flush ();
	printResult (PosetForestSearchTest::it_should_always_give_the_correct_answer ());
	cout << endl;

	// Testing Class "ExhaustiveSearch"
	cout << "ExhaustiveSearchTest::a_lattice_with_constant_cost_should_be_totally_exausted";
	cout.flush ();
	printResult (ExhaustiveSearchTest::a_lattice_with_constant_cost_should_be_totally_exausted ());
	cout << "ExhaustiveSearchTest::it_should_find_a_global_minimum";
	cout.flush ();
	printResult (ExhaustiveSearchTest::it_should_find_a_global_minimum ());
	cout << "ExhaustiveSearchTest::it_should_store_all_the_visited_subsets";
	cout.flush ();
	printResult (ExhaustiveSearchTest::it_should_store_all_the_visited_subsets ());
	cout << "ExhaustiveSearchTest::it_should_give_the_number_of_the_visited_subsets";
	cout.flush ();
	printResult (ExhaustiveSearchTest::it_should_give_the_number_of_the_visited_subsets ());
	cout << endl;

	// Testing Class "SFS"
	cout << "SFSTest::it_should_find_a_local_minimum";
	cout.flush ();
	printResult (SFSTest::it_should_find_a_local_minimum ());
	cout << "SFSTest::it_should_store_all_the_visited_subsets";
	cout.flush ();
	printResult (SFSTest::it_should_store_all_the_visited_subsets ());
	cout << "SFSTest::it_should_give_the_number_of_the_visited_subsets";
	cout.flush ();
	printResult (SFSTest::it_should_give_the_number_of_the_visited_subsets ());
	cout << "SFSTest::it_should_converge_for_large_hamming_sets";
	cout.flush ();
	printResult (SFSTest::it_should_converge_for_large_hamming_sets ());
	cout << endl;

	// Testing Class "SFFS"
	cout << "SFFSTest::it_should_add_the_best_element";
	cout.flush ();
	printResult (SFFSTest::it_should_add_the_best_element ());
	cout << "SFFSTest::it_should_remove_the_worst_element";
	cout.flush ();
	printResult (SFFSTest::it_should_remove_the_worst_element ());
	cout << "SFFSTest::it_should_find_a_local_minimum";
	cout.flush ();
	printResult (SFFSTest::it_should_find_a_local_minimum ());
	cout << "SFFSTest::it_should_store_all_the_visited_subsets";
	cout.flush ();
	printResult (SFFSTest::it_should_store_all_the_visited_subsets ());
	cout << "SFFSTest::it_should_give_the_number_of_the_visited_subsets";
	cout.flush ();
	printResult (SFFSTest::it_should_give_the_number_of_the_visited_subsets ());
	cout << "SFFSTest::it_should_converge_for_large_hamming_sets";
	cout.flush ();
	printResult (SFFSTest::it_should_converge_for_large_hamming_sets ());
	cout << "SFFSTest::it_should_converge_for_large_abs_sum_sets";
	cout.flush ();
	printResult (SFFSTest::it_should_converge_for_large_abs_sum_sets ());
	cout << endl;
*/
	// Testing Class "Vertex"
	/*cout << "VertexTest::a_new_vertex_should_have_no_child";
	cout.flush ();
	printResult (VertexTest::a_new_vertex_should_have_no_child ());
	cout << "VertexTest::a_terminal_vertex_should_have_no_var";
	cout.flush ();
	printResult (VertexTest::a_terminal_vertex_should_have_no_var ());
	cout << "VertexTest::a_nonterminal_vertex_should_have_no_value";
	cout.flush ();
	printResult (VertexTest::a_nonterminal_vertex_should_have_no_value ());
	cout << endl;*/

	// Testing Class "ROBDD"
	cout << "ROBDDTest::a_new_robdd_has_only_a_terminal_node";
	cout.flush ();
	printResult (ROBDDTest::a_new_robdd_has_only_a_terminal_node ());
	cout << "ROBDDTest::the_union_of_a_new_robdd_with_itself_should_be_itself";
	cout.flush ();
	printResult (ROBDDTest::the_union_of_a_new_robdd_with_itself_should_be_itself ());
	cout << "ROBDDTest::the_union_of_all_subsets_must_be_the_function_1";
	cout.flush ();
	printResult (ROBDDTest::the_union_of_all_subsets_must_be_the_function_1 ());
	cout << "ROBDDTest::a_new_robdd_contais_no_subset";
	cout.flush ();
	printResult (ROBDDTest::a_new_robdd_contais_no_subset ());
	cout << "ROBDDTest::an_added_subset_must_be_covered";
	cout.flush ();
	printResult (ROBDDTest::an_added_subset_must_be_covered ());
	cout << "ROBDDTest::the_function_one_covers_all_subsets";
	cout.flush ();
	printResult (ROBDDTest::the_function_one_covers_all_subsets ());
	cout << "ROBDDTest::the_function_one_have_no_subset_evaluated_zero";
	cout.flush ();
	printResult (ROBDDTest::the_function_one_have_no_subset_evaluated_zero ());
	cout << "ROBDDTest::its_possible_to_get_a_random_subset_evaluated_zero";
	cout.flush ();
	printResult (ROBDDTest::its_possible_to_get_a_random_subset_evaluated_zero ());
	cout << "ROBDDTest::the_robdd_maintains_a_log_of_restrictions";
	cout.flush ();
	printResult (ROBDDTest::the_robdd_maintains_a_log_of_restrictions ());
	cout << "ROBDDTest::it_should_represent_the_same_space_after_reordering";
	cout.flush ();
	printResult (ROBDDTest::it_should_represent_the_same_space_after_reordering ());
	cout << endl;


	// Testing Class "UCSROBDDToolBox"
/*	cout << "UCSROBDDToolBoxTest::it_should_return_null_when_theres_no_unvisited_adjacent";
	cout.flush ();
	printResult (UCSROBDDToolBoxTest::it_should_return_null_when_theres_no_unvisited_adjacent ());
	cout << "UCSROBDDToolBoxTest::it_should_return_an_unvisited_adjacent";
	cout.flush ();
	printResult (UCSROBDDToolBoxTest::it_should_return_an_unvisited_adjacent ());
	cout << endl;

    // Testing Class "UCSROBDDToolBox4"
	cout << "UCSROBDDToolBox4Test::it_should_return_null_when_theres_no_unvisited_adjacent";
	cout.flush ();
	printResult (UCSROBDDToolBox4Test::it_should_return_null_when_theres_no_unvisited_adjacent ());
	cout << "UCSROBDDToolBox4Test::it_should_return_an_unvisited_adjacent";
	cout.flush ();
	printResult (UCSROBDDToolBox4Test::it_should_return_an_unvisited_adjacent ());
	cout << endl;*/

	// Testing Class "UCSROBDD2"
	/*cout << "UCSROBDDTest::a_lattice_with_constant_cost_should_be_totally_exausted";
	cout.flush ();
	printResult (UCSROBDDTest::a_lattice_with_constant_cost_should_be_totally_exausted ());
	cout << "UCSROBDDTest::it_should_find_a_global_minimum";
	cout.flush ();
	printResult (UCSROBDDTest::it_should_find_a_global_minimum ());
	cout << "UCSROBDDTest::it_should_converge_for_large_hamming_sets";
	cout.flush ();
	printResult (UCSROBDDTest::it_should_converge_for_large_hamming_sets ());
	cout << "UCSROBDDTest::it_should_converge_for_large_abs_sum_sets";
	cout.flush ();
	printResult (UCSROBDDTest::it_should_converge_for_large_abs_sum_sets());
	cout << "UCSROBDDTest::it_should_store_all_the_visited_subsets";
	cout.flush ();
	printResult (UCSROBDDTest::it_should_store_all_the_visited_subsets ());
	cout << "UCSROBDDTest::it_should_give_the_number_of_the_visited_subsets";
	cout.flush ();
	printResult (UCSROBDDTest::it_should_give_the_number_of_the_visited_subsets ());
	cout << "UCSROBDDTest::it_should_always_give_the_correct_answer";
	cout.flush ();
	printResult (UCSROBDDTest::it_should_always_give_the_correct_answer ());
	cout << endl;*/

	// Testing Class "UCSROBDD3"
	// cout << "UCSROBDD3Test::it_should_find_a_global_minimum";
	// cout.flush ();
	// printResult (UCSROBDDTest::it_should_find_a_global_minimum ());
	// cout << "UCSROBDD3Test::it_should_converge_for_large_hamming_sets";
	// cout.flush ();
	// printResult (UCSROBDDTest::it_should_converge_for_large_hamming_sets ());
	// cout << "UCSROBDD3Test::it_should_converge_for_large_abs_sum_sets";
	// cout.flush ();
	// printResult (UCSROBDD3Test::it_should_converge_for_large_abs_sum_sets());
	// cout << "UCSROBDD3Test::it_should_always_give_the_correct_answer";
	// cout.flush ();
	// printResult (UCSROBDD3Test::it_should_always_give_the_correct_answer ());
	// cout << endl;
	
	// Testing Class "GeneticOrdering"
	cout << "GeneticOrderingTest::it_should_create_an_initial_population";
	cout.flush ();
	printResult (GeneticOrderingTest::it_should_create_an_initial_population ());
	/*cout << "GeneticOrderingTest::it_should_give_a_better_ordering_robdd";
	cout.flush ();
	printResult (GeneticOrderingTest::it_should_give_a_better_ordering_robdd ());
	cout << endl;*/


	// Testing Class "OrderingNode"
	cout << "OrderingNodeTest::it_should_create_a_random_permutation";
	cout.flush ();
	printResult (OrderingNodeTest::it_should_create_a_random_permutation ());
	cout << "OrderingNodeTest::it_should_represent_the_original_robdd";
	cout.flush ();
	printResult (OrderingNodeTest::it_should_represent_the_original_robdd ());
	cout << "OrderingNodeTest::it_should_recombine_to_other_permutations";
	cout.flush ();
	printResult (OrderingNodeTest::it_should_recombine_to_other_permutations ());
	cout << "OrderingNodeTest::it_should_perform_a_mut";
	cout.flush ();
	printResult (OrderingNodeTest::it_should_perform_a_mut ());
	cout << "OrderingNodeTest::it_should_perform_a_neighbour_mut";
	cout.flush ();
	printResult (OrderingNodeTest::it_should_perform_a_neighbour_mut ());
	cout << endl;


	cout << "Total " << number_of_passed_tests + number_of_failed_tests << " test(s), ";
	cout << number_of_passed_tests << " test(s) passed, " << number_of_failed_tests;
	cout << " test(s) failed." << endl << endl;

	// End of tests
	return EXIT_SUCCESS;
}
