//============================================================================
//
//    featsel -- a flexible feature selection program.
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


#include "global.h"
#include "string.h"
#include "ElementSet.h"
#include "CostFunction.h"

#include "functions/AbsSum.h"
#include "functions/Explicit.h"
#include "functions/HammingDistance.h"
#include "functions/MeanAbsSum.h"
#include "functions/MeanConditionalEntropy.h"

#include "algorithms/UCurveSearch.h"
#include "algorithms/ExhaustiveSearch.h"
#include "algorithms/SFS.h"
#include "algorithms/SFFS.h"
#include "algorithms/BranchAndBound.h"
#include "algorithms/PosetForestSearch.h"
#include "algorithms/UCSROBDD.h"
#include "algorithms/UCSROBDD2.h"
#include "algorithms/UCSROBDD3.h"
#include "algorithms/UCSROBDD4.h"
#include "algorithms/UCSROBDD5.h"
#include "algorithms/UCSROBDD6.h"
#include "algorithms/UCSROBDD7.h"
//#include "algorithms/UCSRT.h"
//#include "algorithms/UCSOBDD.h"

// Function to parse and verify the correctness of the parameters.
// It returns '0' if all the parameters were correct, '1' if there was an error,
// and '2' if the option '-h' (help) was called.
//
int parse_parameters
	(int, char **, string *, unsigned int *, string *,
	 unsigned int *, unsigned int *, bool *, string *, float *, unsigned int *,
	 unsigned int *);


// The main function.
//
int main(int argc, char * argv[])
{
	unsigned int max_number_of_minima = 1;
	unsigned int n = 3;
	unsigned int range = 1000;
	unsigned int max_number_of_calls_of_cost_function = 0; // if == 0, then there is no limit
	unsigned int number_of_reorderings = 0;
	int i;
	CostFunction * cost_function;
	Solver * solver;
	ElementSet * S;
	string list;
	string a_cost_function ("abs_sum");
	string algorithm ("ucs");
	string file_name;
	bool store_visited_subsets = false;
	float threshold = FLT_MIN;
	ofstream log_file;

	// parses the parameters
	i = parse_parameters(argc, argv, &file_name, &max_number_of_minima, &a_cost_function,
						 &n, &range, &store_visited_subsets, &algorithm, &threshold,
						 &max_number_of_calls_of_cost_function, &number_of_reorderings);

	if (i != EXIT_SUCCESS)    // help or error in parameters
		return EXIT_FAILURE;
	else
	{
		// selects the type of instance (from XML file, from DAT file, or random)
		//
		if ((file_name.size () > 0) &&
			((file_name.find (".xml") != string::npos) || (file_name.find (".XML") != string::npos)))
			S = new ElementSet ("S", file_name.data ());
		else if ((file_name.size () > 0) &&
				((file_name.find (".dat") != string::npos) || (file_name.find (".DAT") != string::npos)))
		{
			// IMPORTANT: the use of .dat file requires the -n option!
			S = new ElementSet (file_name.data (), n);
		}
		else
			S = new ElementSet ("S", n, range);

		// Selects the proper solver
		//
		if (algorithm.compare ("ucs") == 0)
			solver = new UCurveSearch ();
		else if (algorithm.compare ("ucsr") == 0)
			solver = new UCSROBDD ();
		else if (algorithm.compare ("ucsr2") == 0)
			solver = new UCSROBDD2 ();
		/*else if (algorithm.compare ("ucsrt") == 0)
			solver = new UCSRT ();
		else if (algorithm.compare ("ucso") == 0)
			solver = new UCSOBDD ();*/
		else if (algorithm.compare ("ucsr3") == 0)
			solver = new UCSROBDD3 ();
		else if (algorithm.compare ("ucsr4") == 0)
			solver = new UCSROBDD4 ();
		else if (algorithm.compare ("ucsr5") == 0)
			solver = new UCSROBDD5 ();
		else if (algorithm.compare ("ucsr6") == 0)
			solver = new UCSROBDD6 ();
		else if (algorithm.compare ("ucsr7") == 0)
			solver = new UCSROBDD7 (number_of_reorderings);


		else if (algorithm.compare ("es") == 0)
			solver = new ExhaustiveSearch ();
		else if (algorithm.compare ("sfs") == 0)
			solver = new SFS ();
		else if (algorithm.compare ("sffs") == 0)
		{
			solver = new SFFS ();
			// S->permute_set ();    // TODO: shuffle the set to obtain a different running time
		}
		else if (algorithm.compare ("pfs") == 0)
			solver = new PosetForestSearch ();
		else if (algorithm.compare ("ubb") == 0)
		{
			solver = new BranchAndBound ();
			// S->permute_set ();    // TODO: shuffle the set to obtain a different running time
		}
		else
			return EXIT_FAILURE;

		// Selects the proper cost function
		//
		if (a_cost_function.compare ("mean_abs_sum") == 0)
			cost_function = new MeanAbsSum (S);
		else if (a_cost_function.compare ("abs_sum") == 0)
			cost_function = new AbsSum (S);
		else if (a_cost_function.compare ("explicit") == 0)
			cost_function = new Explicit (S);
		else if (a_cost_function.compare ("hamming_distance") == 0)
			cost_function = new HammingDistance (S);
		else if (a_cost_function.compare ("mce") == 0)
			cost_function = new MeanConditionalEntropy (S);
		else
			return EXIT_FAILURE;

		// If the solver has a heuristic strategy, here we
		// set the threshold value for the cost function,
		// for the first stage (pre-processing).
		//
		if (threshold > FLT_MIN)
			cost_function->set_threshold (threshold);

		// If the solver has a heuristic strategy, here we
		// set the maximum number of calls of the cost function,
		// for the second stage (search with limited range).
		//
		if (max_number_of_calls_of_cost_function > 0)
			cost_function->set_max_number_of_calls_of_cost_function
							  (max_number_of_calls_of_cost_function);

		// Sets the solver parameters
		//
		solver->set_parameters (cost_function, S, store_visited_subsets);

		// Runs the solver
		//
		solver->get_minima_list (max_number_of_minima);

		// Prints the results
		//
		cout << endl << "== List of best subsets found ==" << endl;
		cout << " X : c(X)" << endl;
		cout << solver->print_search_report ();
		if (store_visited_subsets)
		{
			cout << endl << "Visited subsets stored into 'visited.log' file" << endl;
			log_file.open ("visited.log");
			log_file << solver->print_list_of_visited_subsets () << endl;
			log_file.close ();
		}
		else
		{
			int elapsed_time =
					cost_function->get_the_elapsed_time_of_the_calls_of_this_cost_function ();
			// number of visited subsets is the number of calls
			// of the cost function!
			int number_of_subsets = solver->print_number_of_visited_subsets ();
			if (number_of_subsets > 0)
			{
				cout << endl << "Number of visited subsets: "
				 <<  number_of_subsets << endl;
				cout << "Required time to compute the visited subsets: "
				 << elapsed_time << " microseconds " << endl;
				cout << "(average " << elapsed_time / number_of_subsets
				 << " microseconds per node)" << endl;
			}
			cout << endl << "Elapsed time of execution of the algorithm (in microseconds): "
				 << solver->get_elapsed_time_of_the_algorithm () << endl;

			if ( (algorithm.compare ("ucs")   == 0) ||
				 (algorithm.compare ("ucsr")  == 0) ||
				 (algorithm.compare ("ucsr2") == 0) ||
				 (algorithm.compare ("ucsrt") == 0) ||
				 (algorithm.compare ("ucso") == 0)  ||
				 (algorithm.compare ("ucsr3") == 0) ||
				 (algorithm.compare ("ucsr4") == 0) ||
				 (algorithm.compare ("ucsr5") == 0) ||
				 (algorithm.compare ("ucsr6") == 0) ||
				 (algorithm.compare ("ucsr7") == 0))
			{
				cout << endl << "Elapsed time of the minima exhausting (in microseconds): "
					 << solver->get_elapsed_time_of_all_calls_of_the_minima_exhausting () << endl;
				cout << endl << "Number of calls of the minima exhausting: "
					 << solver->get_number_of_calls_of_minimum_exhausting () << endl;
				cout << endl << "Maximum size a graph achives during the minima exhausting: "
					 << solver->get_max_size_of_the_graph () << endl;
				cout << endl << "Number of times a minimal (maximal) element is computed: "
					 << solver->get_number_of_calls_of_minimal_and_maximal_element () << endl;
				cout << endl << "Consults to restrictions: "
					 << solver->get_number_of_restrictions_consults () << endl;
				cout << endl << "Updates to restrictions: "
					 << solver->get_number_of_restrictions_updates () << endl;
				cout << endl << "Reorderings to restrictions: "
					 << solver->get_number_of_restrictions_reorderings () << endl;
				cout << endl << "Elapsed time updating restrictions (in microseconds): "
					 << solver->get_elapsed_time_updating_restrictions () << endl;
				cout << endl << "Elapsed time reducing restrictions (in microseconds): "
					 << solver->get_elapsed_time_reducing_restrictions () << endl;
				cout << endl << "Elapsed time consulting restrictions (in microseconds): "
					 << solver->get_elapsed_time_consulting_restrictions () << endl;
				cout << endl << "Elapsed time reordering restrictions (in microseconds): "
					 << solver->get_elapsed_time_reordering_restrictions () << endl;
				cout << endl << "Maximum size of the ROBDD: " 
					 << solver->get_max_restriction_size () << endl;

			}

			if (algorithm.compare ("pfs") == 0)
			{
				cout << endl << "Number of iterations of the main algorithm: "
					 << solver->get_number_of_iterations () << endl;
				cout << endl << "Maximum size that achieves forest A: "
					 << solver->get_max_size_of_the_forest_A () << endl;
				cout << endl << "Maximum size that achieves forest B: "
					 << solver->get_max_size_of_the_forest_B () << endl;
			}
		}

		cout << endl << "== End of processing ==" << endl << endl;

		// exits to the OS
		//
		delete S;
		delete solver;
		delete cost_function;
		return EXIT_SUCCESS;
	}
} // end of main



// function implementation
//
int parse_parameters (int argc, char ** argv, string * file_name,
					  unsigned int * m, string * c, unsigned int * n,
					  unsigned int * range, bool * keep_subsets,
					  string * a, float * threshold,
					  unsigned int * max_number_of_calls_of_cost_function,
					  unsigned int * number_of_reorderings)
{
	int i;
	bool error = false;
	string a_line;
	ifstream a_file;
	string disclaimer ("featsel -- a flexible feature selection program.\n\
Copyright (C) 2010  Marcelo S. Reis.\n\n \
This program comes with ABSOLUTELY NO WARRANTY.\n \
This is free software, and you are welcome to redistribute it\n \
under certain conditions; see 'LICENSE.TXT' for details.");
	// parsing the arguments
	//
	for (i=1; i<argc; i++)
	{
		// -f
		//
		if( (strcmp (argv[i],"-f") == 0) && ((i+1) < argc) )
		{
			a_file.open (argv[++i]);
			if (a_file.is_open ())
			{
				a_file.close ();
				file_name->append (argv[i]);
			}
			else
			{
				cout << "\nError: unable to open input file '" << argv[i] << "'!" << endl;
				error = true;
			}
		}
		else if ( (strcmp (argv[i],"-f") == 0) && ((i+1) >= argc) )
		{
			cout << "\nError: parameter '-f' must have a file name." << endl;
			error = true;
		}
		// -r
		//
		else if ( (strcmp( argv[i],"-r") == 0) && ((i+1) < argc) )
		{
			*range = atoi (argv[++i]);
			if (*range >= RAND_MAX)
			{
				cout << "\nError: range should be in [0, " << RAND_MAX << ") !\n";
				error = true;
			}
		}
		else if ( (strcmp (argv[i],"-r") == 0) && ((i+1) >= argc) )
		{
			cout << "\nError: parameter '-r' must have a value." << endl;
			error = true;
		}
		// -t1  pre-processing of the heuristic mode; it receives a threshold
		//
		else if ( (strcmp( argv[i],"-t1") == 0) && ((i+1) < argc) )
		{
			*threshold = atof (argv[++i]);
		}
		else if ( (strcmp (argv[i],"-t1") == 0) && ((i+1) >= argc) )
		{
			cout << "\nError: parameter '-t1' must have a value." << endl;
			error = true;
		}
		// -t2  second stage of the heuristic mode; it receives a limit to
		//      the number of calls of the cost function
		//
		else if ( (strcmp( argv[i],"-t2") == 0) && ((i+1) < argc) )
		{
			*max_number_of_calls_of_cost_function = atoi (argv[++i]);
		}
		else if ( (strcmp (argv[i],"-t2") == 0) && ((i+1) >= argc) )
		{
			cout << "\nError: parameter '-t2' must have a value." << endl;
			error = true;
		}
		// -n
		//
		else if ( (strcmp (argv[i],"-n") == 0) && ((i+1) < argc) )
		{
			if (atoi (argv[++i]) > 0)
				*n = atoi (argv[i]);
			else
			{
				cout << "\nError: number of elements should be a positive integer!" << endl;
				error = true;
			}
		}
		else if ( (strcmp (argv[i],"-n") == 0) && ((i+1) >= argc) )
		{
			cout << "\nError: parameter '-n' must have a value." << endl;
			error = true;
		}
		// -c
		//
		else if ( (strcmp (argv[i],"-c") == 0) && ((i+1) < argc) )
		{
			i++;
			if ( (strcmp (argv[i], "abs_sum") == 0) ||
				 (strcmp (argv[i], "mean_abs_sum") == 0) ||
				 (strcmp (argv[i], "mce") == 0) ||
				 (strcmp (argv[i], "explicit") == 0) ||
				 (strcmp (argv[i], "hamming_distance") == 0) )
			{
				c->clear();
				c->append(argv[i]);
			}
			else
			{
				cout << "\nError: unknown cost function '" << argv[i] << "'!" << endl;
				error = true;
			}
		}
		// -a
		//
		else if ( (strcmp(argv[i],"-a") == 0) && ((i+1) < argc) )
		{
			i++;
			if ( (strcmp (argv[i], "ucs") == 0)   ||
				 (strcmp (argv[i], "es") == 0)    ||
				 (strcmp (argv[i], "sfs") == 0)   ||
				 (strcmp (argv[i], "sffs") == 0)  ||
				 (strcmp (argv[i], "pfs") == 0)   ||
				 (strcmp (argv[i], "ubb") == 0)   ||
				 (strcmp (argv[i], "ucsr") == 0)  ||
				 (strcmp (argv[i], "ucsr2") == 0) ||
				 (strcmp (argv[i], "ucsr3") == 0) ||
				 (strcmp (argv[i], "ucsr4") == 0) ||
				 (strcmp (argv[i], "ucsr5") == 0) ||
				 (strcmp (argv[i], "ucsr6") == 0) ||
				 (strcmp (argv[i], "ucsr7") == 0) ||
				 (strcmp (argv[i], "ucsrt") == 0) ||
				 (strcmp (argv[i], "ucso") == 0) )
			{
				a->clear();
				a->append(argv[i]);
			}
			else
			{
				cout << "\nError: unknown algorithm '" << argv[i] << "'!" << endl;
				error = true;
			}
		}
		else if ( (strcmp(argv[i],"-c") == 0) && ((i+1) >= argc) )
		{
			cout << "\nError: parameter '-c' must have a cost function name." << endl;
			error = true;
		}
		// -m
		//
		else if ( (strcmp (argv[i],"-m") == 0) && ((i+1) < argc) )
		{
			if (atoi (argv[++i]) > 0)
				*m = atoi (argv[i]);
			else
			{
				cout << "\nError: maximum number of minima should be a positive integer!" << endl;
				error = true;
			}
		}
		else if ( (strcmp (argv[i],"-m") == 0) && ((i+1) >= argc) )
		{
			cout << "\nError: parameter '-m' must have a value." << endl;
			error = true;
		}
		// -d
		//
		else if ( (strcmp (argv[i],"-d") == 0) && ((i+1) < argc) )
		{
			if (atoi (argv[++i]) > 0)
				*number_of_reorderings = atoi (argv[i]);
			else
			{
				cout << "\nError: maximum number of minima should be a positive integer!" << endl;
				error = true;
			}
		}
		else if ( (strcmp (argv[i],"-d") == 0) && ((i+1) >= argc) )
		{
			cout << "\nError: parameter '-d' must have a value." << endl;
			error = true;
		}
		// -s
		//
		else if (strcmp (argv[i],"-s") == 0)
		{
			*keep_subsets = true;
		}
		// -h
		//
		else if (strcmp (argv[i],"-h") == 0)
		{
			cout << endl << disclaimer << endl << endl;
			a_file.open ("featsel.txt");
			if(a_file.is_open ())
				while(a_file.good ())
				{
					getline (a_file, a_line);
					cout << a_line << endl;
				}
			a_file.close ();
			return EXIT_FAILURE;
		}
		else
		{
			cout <<  endl << "Unknown option '" << argv[i] << "'." << endl;
			error = true;
		}
	}
	if ( (error) || (argc == 1) )
	{
		cout << endl << disclaimer << endl;
		cout << endl << "Type 'featsel -h' for help." << endl << endl;
		return EXIT_FAILURE;
	}
	else
		return EXIT_SUCCESS;

} // end of function

