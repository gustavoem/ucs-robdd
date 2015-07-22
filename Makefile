#
# Makefile -- featsel's Makefile
#
#    This file is part of the featsel program
#    Copyright (C) 2010  Marcelo S. Reis
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

IDIR = ../

CXXFLAGS =	-O0 -g -Wall -fmessage-length=0

OBJS =		src/Element.o src/ElementSet.o src/ElementSubset.o \
			src/Collection.o src/Solver.o src/CostFunction.o \
			src/algorithms/UCurveSearch.o src/algorithms/UCurveToolBox.o \
			src/algorithms/ExhaustiveSearch.o src/algorithms/SFS.o src/algorithms/SFFS.o \
			src/algorithms/BranchAndBound.o src/algorithms/PosetForestSearch.o \
			src/functions/AbsSum.o src/functions/Explicit.o src/functions/MeanAbsSum.o \
			src/functions/HammingDistance.o src/functions/MeanConditionalEntropy.o \
			src/Vertex.o src/ROBDD.o src/algorithms/UCSROBDD.o src/algorithms/UCSROBDDToolBox.o \
			src/algorithms/UCSROBDD2.o src/algorithms/UCSROBDDToolBox2.o \
			src/algorithms/UCSROBDD3.o src/algorithms/UCSROBDDToolBox3.o \
			src/algorithms/UCSROBDD4.o src/algorithms/UCSROBDDToolBox4.o \
			src/algorithms/UCSROBDD5.o src/algorithms/UCSROBDDToolBox5.o \
			src/algorithms/UCSROBDD6.o src/algorithms/UCSROBDDToolBox6.o \
			src/algorithms/UCSROBDD7.o src/algorithms/UCSROBDDToolBox7.o \
			src/GeneticOrdering.o src/OrderingNode.o src/GAROBDD.o \

			#src/algorithms/UCSRT.o src/algorithms/UCSRTToolBox.o src/OBDD.o src/PVertex.o \
			#src/algorithms/UCSOBDD.o src/algorithms/UCSOBDDToolBox.o \
			    
TOBJS =		test/ElementTest.o test/ElementSetTest.o test/ElementSubsetTest.o \
			test/CollectionTest.o test/SolverTest.o \
			test/SolverMock.o test/UCurveToolBoxTest.o test/UCurveSearchTest.o \
			test/ExhaustiveSearchTest.o \
			test/CostFunctionTest.o test/CostFunctionMock.o test/SFSTest.o \
			test/SFFSTest.o test/SFFSMock.o test/PosetForestSearchMock.o \
			test/BranchAndBoundTest.o test/PosetForestSearchTest.o \
			test/VertexTest.o test/ROBDDTest.o test/UCSROBDDTest.o \
			test/UCSROBDD3Test.o test/UCSROBDDToolBoxTest.o \
			test/UCSROBDDToolBox4Test.o \
			test/GeneticOrderingTest.o test/OrderingNodeTest.o \

LIBS = -lm


TARGET =	featsel

TEST =		featselTest

$(TARGET):	help featsel.o $(OBJS)
	$(CXX) -o $(TARGET) src/featsel.o $(OBJS) $(LIBS) \
			parsers/XmlParser.cpp parsers/XmlScanner.cpp parsers/XmlParserDriver.cpp
	
$(TEST):	featselTest.o $(TOBJS) $(OBJS)
	$(CXX) -o $(TEST) test/featselTest.o $(TOBJS) $(OBJS) $(LIBS) \
			parsers/XmlParser.cpp parsers/XmlScanner.cpp parsers/XmlParserDriver.cpp

featsel.o:
	$(CXX)	-c -o src/featsel.o src/featsel.cpp

featselTest.o:
	$(CXX)	-c -o test/featselTest.o test/featselTest.cpp

help:
	groff -man -Tascii docs/featsel.1 > featsel.txt

bison:
	bison	-o parsers/XmlParser.cpp parsers/XmlParser.yy
	
flex:
	flex	-o parsers/XmlScanner.cpp parsers/XmlScanner.ll

all:	$(TARGET)

test:	$(TEST)

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f $(TOBJS) $(TEST)
	rm src/*.o
	rm test/*.o
	rm -f visited.log
	rm -f featsel.txt
