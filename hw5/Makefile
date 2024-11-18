# 
# Makefile for the CS 70 IntList Assignment
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

TARGETS  = intlist-test intvector-example

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

intlist-test: intlist-test.o intlist.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

intvector-example: intvector-example.o intvector.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^


# This next rule is a little unusual because it builds the executable directly
# rather than using a separate compilation step.  We do this so that we can
# use specific compilation settings only for this (performance-checking)
# executable, regardless of the settings normally used to make .o files.

LISTPERF_FLAGS = -O3 -fsized-deallocation -flto
listperf: listperf.cpp intlist.cpp intvector.cpp
	$(CXX) $(LISTPERF_FLAGS) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o $(TARGETS) *.dSYM listperf

# Make has a built-in implicit rule for turning .cpp -> .o, it runs the command:
#
#   $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c -o $@ $<
#
# so we just list the prerequisites, not the the build command

intlist.o: intlist.cpp intlist.hpp const_adaptor.hpp
intlist-test.o: intlist-test.cpp intlist.hpp const_adaptor.hpp
intvector.o: intvector.cpp intvector.hpp const_adaptor.hpp
intvector-example.o: intvector-example.cpp intvector.hpp const_adaptor.hpp