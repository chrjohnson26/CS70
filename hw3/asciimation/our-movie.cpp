/**
 * \file our-movie.cpp
 * \author Anonymized for Peer Review
 *
 * \brief Provides the main() function for creating and running
 * a specific asciimation movie.
 *
 * \details
 *
 * \remarks
 *
 */

#include <iostream>
#include <string>
#include "asciimation.hpp"

using namespace std;

void makeExampleMovie() {
    // Creates an Asciimation object based off given parameters
    Asciimation exMovie = Asciimation(20, 80, 30,
                                    15, "sprite-images/mystery1.txt");
    // Uses the previously created object exMovie to generate the movie
    exMovie.generateMovie("example-movie.mp4", 25);
}

void makeStudentMovie() {
    // Creates an Asciimation object based off student's parameters
    Asciimation studentMovie = Asciimation(20, 80, 30,
                                        15, "sprite-images/movie.txt");
    // Uses the previously created object studentMovie to generate the movie
    studentMovie.generateMovie("student-movie.mp4", 25);
}

int main() {
    // Runs both functions
    makeExampleMovie();
    makeStudentMovie();
}
