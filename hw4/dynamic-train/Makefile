CXX = clang++
CXXFLAGS = -gdwarf-4 -Wall -Wextra -pedantic -std=c++17
LDFLAGS = -ltestinglogger

all: testtrain

testtrain: testtrain.o car.o train.o
	$(CXX) -o testtrain $(CXXFLAGS) testtrain.o car.o train.o $(LDFLAGS)

testtrain.o: testtrain.cpp car.hpp train.hpp
	$(CXX) -c $(CXXFLAGS) testtrain.cpp

train.o: train.cpp train.hpp car.hpp 
	$(CXX) -c $(CXXFLAGS) train.cpp

car.o: car.cpp car.hpp 
	$(CXX) -c $(CXXFLAGS) car.cpp

clean:
	rm -rf *.o testtrain