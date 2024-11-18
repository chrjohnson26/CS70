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

TARGETS  = treeset-test minispell 
DBGFLAGS = -gdwarf-4		# Used for debugging-related flags (-g, etc.)

CXX      = clang++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 $(DBGFLAGS) $(OPTFLAGS)
CPPFLAGS =                  # Used for -D, -isystem and -I preprocessor options
LDFLAGS  = -ltestinglogger -lranduint32  # Used for linking-related options (-l, etc.)

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

minispell: minispell.o
	$(CXX) -o minispell $(CXXFLAGS) minispell.o $(LDFLAGS)

treeset-test: treeset-test.o 
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Make has a built-in implicit rule for turning .cpp -> .o, it runs the command:
#
#   $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c -o $@ $<
#
# so we just list the prerequisites, not the the build command

minispell.o: minispell.cpp treeset.hpp treeset-private.hpp

treeset-test.o: treeset-test.cpp treeset.hpp treeset-private.hpp

clean:
	rm -f *.o $(TARGETS)