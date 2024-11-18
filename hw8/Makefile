#
# Makefile for CS 70 HashSet
#

OPTFLAGS =
CXX = clang++
CXXFLAGS = $(OPTFLAGS) -gdwarf-4 -std=c++17 -Wall -Wextra -pedantic
LDFLAGS = $(CXXFLAGS)
LDLIBS =  
TARGETS = stringhash-test hashset-cow-test hashset-test minispell

# Note: The rules below use useful-but-cryptic make "Automatic variables"
#       to avoid duplicating information in multiple places, the most useful
#       of which are:
#
#   $@  The file name of the target of the rule
#   $^  The names of all the prerequisites, with spaces between them.
#   $<  The name of the first prerequisite
#
# For GNU make, you'll find that it supports quite an extensive list, at
#   http://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
# The most commonly used and supported are $@, $<, $?, $* and $^

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
	rm -rf *.o

stringhash-test: stringhash.o
	$(CXX) $(LDFLAGS) $^ -o $@ -lstringhashtest

hashset-cow-test: hashset-cow-test.o 
	$(CXX) $(LDFLAGS) $^ -o $@ -ltestinglogger

hashset-test: hashset-test.o
	$(CXX) $(LDFLAGS) $^ -o $@ -ltestinglogger

minispell: minispell.o stringhash.o
	$(CXX) $(LDFLAGS) $^ -o $@

hashset-cow-test.o: hashset-cow-test.cpp hashset.hpp hashset-private.hpp
hashset-test.o: hashset-test.cpp hashset.hpp hashset-private.hpp
minispell.o: minispell.cpp hashset.hpp hashset-private.hpp
stringhash.o: stringhash.cpp
