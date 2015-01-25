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

SUMMARY:

(1) CONTENTS
(2) REQUIREMENTS
(3) HOW TO COMPILE
(4) USING FEATSEL
    (4.1) FEATSEL
    (4.2) FEATSEL UNIT TESTS
(5) BUG REPORT AND CONTACT

-----------------------------------------------------------------------------

(1) CONTENTS

This zip package should contain the following directories and files:

\featsel

 ---\docs    -    general documents
     ---\featsel.1  - man page of featsel program in troff format.
     ---\LICENSE.TXT - the GNU/GPL license.
     ---\TODO-LIST.TXT - the to-do list of this project.
     ---\uml-featsel.png - UML diagram of the featsel classes, png format.
     
 ---\input    -    input samples, used by some tests.
     
 ---\output    -   output samples.

 ---\parsers   -   interpreter files (parser and scanner).
     ---\XmlParserDriver.cpp
     ---\XmlParserDriver.h
     ---\XmlParser.yy
     ---\XmlScanner.ll
    
 ---\src    -     featsel classes and namespaces.
     ---\Collection.cpp
     ---\Collection.h
     ---\CostFunction.cpp
     ---\CostFunction.h
     ---\Element.cpp
     ---\Element.h
     ---\ElementSet.cpp
     ---\ElementSet.h
     ---\ElementSubset.cpp
     ---\ElementSubset.h
     ---\featsel.cpp
     ---\global.h
     ---\Solver.cpp
     ---\Solver.h
     ---\algorithms\  -  algorithms classes (they inherit class Solver)
     ---\functions\  -  cost functions classes (they inherit class CostFunction)
     
 ---\test    -    featsel unit test classes and namespaces.
     
 ---\Makefile - a Makefile to compile the source code and the test code.
  
 ---\README.TXT - this file.
  
-----------------------------------------------------------------------------

(2) REQUIREMENTS:

- a terminal environment (XTerm, MS-DOS prompt, etc.);
- the "make" command or equivalent;
- A C++ compiler (GNU g++ or equivalent), with the standard libraries.
- GNU Bison 2.4.1 or higher (optional).
- Flex 2.5 or higher (optional).

-----------------------------------------------------------------------------

(3) HOW TO COMPILE:

After unzip this package, just open a terminal and type, inside the directory
were it was unzipped:

$> make

To remove the objects produced by the compiler, type:

$> make clean

And to compile the tests, type:

$> make test

-----------------------------------------------------------------------------

(4) USING FEATSEL:

* 4.1 - featsel:

To run the featsel program, just type "featsel" inside the directory; examples:

$> ./featsel -f file.xml -m 5

$> ./featsel -n 3 -r 100 -m 2

If the parameters are correct, the output should be like this one:

 X : c(X)
 [000000010] : 3
 [001100000] : 2
 [000000100] : 2
 [010100000] : 1
 
 The first column is a subset X of the set S of elements, in the format 
 [b_1, ..., b_|S|], where the bit b_i is "1" is it belongs to X and "0" otherwise,
 and the second column is the cost of X, that is, the value of c(X).


For the proper use of the parameters, type "featsel -h" or look at featsel man page.


* 4.2 - featsel unit tests:

To run the test program, make test and type:

$> ./featselTest

It should run all the tests automatically, displaying the results into the
standard output.

-----------------------------------------------------------------------------

(5) BUG REPORT AND CONTACT:

Marcelo S. Reis
msreis at ime dot usp dot br

-----------------------------------------------------------------------------
END OF README.TXT
