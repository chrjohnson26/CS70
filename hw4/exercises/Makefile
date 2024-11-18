#
# Makefile for CS 70 Valgrind exercises
#

CXX = clang++
CXXFLAGS = -gdwarf-4 -std=c++17 -Wall -Wextra
LDFLAGS =

TARGETS=exercise01 exercise02 exercise03 exercise04 exercise05 exercise06
all: $(TARGETS)

exercise01: exercise01.o
	$(CXX) $(CXXFLAGS) -o exercise01 exercise01.o $(LDFLAGS)

exercise02: exercise02.o
	$(CXX) $(CXXFLAGS) -o exercise02 exercise02.o $(LDFLAGS)

exercise03: exercise03.o
	$(CXX) $(CXXFLAGS) -o exercise03 exercise03.o $(LDFLAGS)

exercise04: exercise04.o
	$(CXX) $(CXXFLAGS) -o exercise04 exercise04.o $(LDFLAGS)

exercise05: exercise05.o
	$(CXX) $(CXXFLAGS) -o exercise05 exercise05.o $(LDFLAGS)

exercise06: exercise06.o
	$(CXX) $(CXXFLAGS) -o exercise06 exercise06.o $(LDFLAGS)


exercise01.o: exercise01.cpp
	$(CXX) $(CXXFLAGS) -c -std=c++17 -pedantic -Wall -Wextra exercise01.cpp

exercise02.o: exercise02.cpp
	$(CXX) $(CXXFLAGS) -c -std=c++17 -pedantic -Wall -Wextra exercise02.cpp

exercise03.o: exercise03.cpp
	$(CXX) $(CXXFLAGS) -c -std=c++17 -pedantic -Wall -Wextra exercise03.cpp

exercise04.o: exercise04.cpp
	$(CXX) $(CXXFLAGS) -c -std=c++17 -pedantic -Wall -Wextra exercise04.cpp

exercise05.o: exercise05.cpp
	$(CXX) $(CXXFLAGS) -c -std=c++17 -pedantic -Wall -Wextra exercise05.cpp

exercise06.o: exercise06.cpp
	$(CXX) $(CXXFLAGS) -c -std=c++17 -pedantic -Wall -Wextra exercise06.cpp


clean:
	rm -rf $(TARGETS) *.o
