# 
# Makefile for the CS 70 TreeStringSet Assignment
#
# As usual, you can build this software by typing:
#
#     make 
#
# or, if you prefer more explanation about what is happening and why,
#
#     cs70-make
#
# (or specify a other target from the file)

TARGETS  = treestringset-test minispell

OPTFLAGS =                  # Used for optimization-related flags (-O, etc.)
DBGFLAGS = -gdwarf-4		# Used for debugging-related flags (-g, etc.)

CXX      = clang++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 $(DBGFLAGS) $(OPTFLAGS)
CPPFLAGS =                  # Used for -D, -isystem and -I preprocessor options
LDFLAGS  = -ltestinglogger  # Used for linking-related options (-l, etc.)

# Note: The rules below use useful-but-cryptic make "Automatic variables"
#       to avoid duplicating information in multiple places, the most useful
#       of which are:
#
#   $@  The file name of the target of the rule  (e.g., cs70-make below)
#   $^  The names of all the prerequisites, with spaces between them.
#   $<  The name of the first prerequisite
#
# For GNU make, you'll find that it supports quite an extensive list, at
#   http://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
# for cs70-make, $@, $<, $?, $* and $^ are supported.

all: $(TARGETS) 
minispell: treestringset.o minispell.o 
	$(CXX) -o minispell $(CXXFLAGS) minispell.o treestringset.o $(LDFLAGS)
treestringset-test: treestringset-test.o treestringset.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

treestringset.o: treestringset.cpp treestringset.hpp
treestringset-test.o: treestringset-test.cpp treestringset.hpp
minispell.o: minispell.cpp
clean:
	rm -f *.o $(TARGETS) *.dSYM listperf
