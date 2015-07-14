//
// global.h -- Global libraries, structures, and definitions.
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

#ifndef GLOBAL_H_
#define GLOBAL_H_

# include <cfloat>
# include <climits>
# include <cmath>
# include <cstdlib>
# include <ctime>
# include <fstream>
# include <iostream>
# include <list>
# include <map>
# include <sstream>
# include <string>
# include <vector>
# include <algorithm>
# include <iterator>

// # include <omp.h>        // OpenMP 3.0 Library
// to include the OpenMP functions, add the -fopenmp flag in the Makefile file!

# include <glpk.h>       // GLPK Library
// to include the glpk functions, add the -lglpk flag in the Makefile file!

# define INFINITY_COST FLT_MAX

using namespace std;

#endif /* GLOBAL_H_ */
