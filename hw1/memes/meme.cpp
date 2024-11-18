/*
 * meme.cpp
 *
 * This file contains `meme` program to generate custom memes.
 *
 * It forms part of CS70 Homework 1. This file may NOT be shared with
 * anyone other than the author(s) and the current semester's CS70
 * staff without explicit written permission from one of the CS70
 * instructors.
 *
 * How to compile and link. First make sure you're in the memes directory,
 * then run the following commands:
 *
    clang++ -c -std=c++17 -gdwarf-4 -Wall -Wextra -pedantic \
          -isystem /usr/include/opencv4 meme.cpp
    clang++ -o meme meme.o -lopencv_imgcodecs -lopencv_core -lopencv_imgproc
 *
 * How to run:
 *
    ./meme
 *
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

/**
 * \brief Converts a string to spongebob mocking capitalization.
 * \returns the modified string.
 */

string spongebobMocking(string input) {
    for (size_t i = 0; i < input.length(); ++i) {
        // iterates through string to make every letter lowercase

        input[i] = tolower(input[i]);
        // makes every other letter uppercase

        if (i%2) {
            input[i] = toupper(input[i]);
        }
    }

    return input;
}

/**
 * \brief Creates a meme with an image and a string of text.
 * \input Three strings, representing the name of the source image file,
 *        the text to add to the image, and the name of the destination
 *        image file.
 * \returns 0 if everything is successful, -1 otherwise.
 */
int makeMeme(string inputFilename, string text, string outputFilename) {
    // Open the image file
    cout << "Opening file: " << inputFilename << endl;
    Mat image = imread(inputFilename);

    if (image.empty()) {
        cerr << "Could not open or find the image " << inputFilename << endl;
        return -1;
    }

    int font = FONT_HERSHEY_TRIPLEX;
    float textScaling = 3;
    Scalar textColor{255, 255, 255};
    Point textPosition{50, 600};

    text = spongebobMocking(text);
    cout << "Adding text: " << text << endl;
    putText(image, text, textPosition, font, textScaling, textColor);

    // Write out the modified image
    cout << "Writing file: " << outputFilename << endl;
    bool isSuccess = imwrite(outputFilename, image);

    if (!isSuccess) {
        cerr << "Could not write the image " << outputFilename << endl;
        return -1;
    }

    return 0;
}

/**
 * \brief Gets input from the user, then uses that input to call makeMeme.
 * \input None, but asks for three input strings from the user with getline().
 * \returns 0 if everything is successful, -1 otherwise.
 */

int main() {
    string inputFilename;
    cout << "Enter image file name: ";
    getline(cin, inputFilename);

    string text;
    cout << "Enter meme text: ";
    getline(cin, text);

    string outputFilename;
    cout << "Enter output file name: ";
    getline(cin, outputFilename);

    return makeMeme(inputFilename, text, outputFilename);
}
