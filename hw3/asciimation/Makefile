OPENCV_LIBS=-lopencv_imgcodecs -lopencv_core -lopencv_imgproc -lopencv_video -lopencv_videoio

all: our-movie

# The target "generateSegfault.o" has two dependencies: "generateSegfault.cpp" and "helloSayer.hpp"
# Make will confirm that the dependenies are up to date and then it will run
# the command on the following line to generate generateSegault.o.

our-movie: our-movie.o asciimation.o sprite.o
	clang++ -o our-movie -std=c++17 -g -Wall -Wextra -pedantic our-movie.o asciimation.o sprite.o $(OPENCV_LIBS)

our-movie.o: our-movie.cpp asciimation.hpp sprite.hpp
	clang++ -c -std=c++17 -g -Wall -Wextra -pedantic -isystem /usr/include/opencv4 our-movie.cpp

asciimation.o: asciimation.cpp asciimation.hpp sprite.hpp 
	clang++ -c -std=c++17 -g -Wall -Wextra -pedantic -isystem /usr/include/opencv4 asciimation.cpp

# The target "helloSayer.o" has two dependencies "helloSayer.cpp" and
# "helloSayer.hpp". Make will make sure that the command runs if either of these
# files have changed since the last time Make had to make helloSayer.o
# (Note the -c in the command, this means that clang will not link, but will
# just comile into an object (.o) file.  We are naming that output file
# helloSayer.o

sprite.o: sprite.cpp sprite.hpp
	clang++ -c -std=c++17 -g -Wall -Wextra -pedantic -isystem /usr/include/opencv4 sprite.cpp

# The target "generateSegfault" has two dependencies "generateSegfault.o" and
# "helloSayer.o"  Make will make sure these two dependencies are up to date and
# then it will run the commend on the following line, to compile an executable
# and give it the name "generateSegfault"

# This is a "phony" target.  When we tell Make to make clean, it has no
# dependencies and it will just run the command below, which removes all object
# files and the executable (if they exist).

clean:
	rm -rf *.o our-movie