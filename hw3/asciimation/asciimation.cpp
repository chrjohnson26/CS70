/**
 * asciimation.cpp
 * Author(s): Christian Johnson and Sheridan Dorsey
 *
 * Part of CS70 Homework 3. This file may NOT be
 * shared with anyone other than the author(s) and
 * the current semester's CS70 staff without
 * explicit written permission from one of the
 * CS70 instructors.
 *
 */

#include "asciimation.hpp"
#include "sprite.hpp"

#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <unistd.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/** 
 * Constructor for the Asciimation object initializes four int
 * arguments and one string
**/
Asciimation::Asciimation(int numRows, int numCols, int rowHeight,
                        int colWidth, string spriteFilename)
        :numRows_{numRows},
        numCols_{numCols},
        rowHeight_{rowHeight},
        colWidth_{colWidth},
        sprite_{spriteFilename},
        spriteCurrentRow_{(numRows_ - Sprite::SPRITE_HEIGHT)/2},
        spriteCurrentCol_{-1 * Sprite::SPRITE_WIDTH}
        {
    }

void Asciimation::addFrame(VideoWriter& vw) {
    // Sets the matrix object's attributes
    const Scalar BACKGROUND_COLOR = Scalar(0, 0, 0);
    const Scalar TEXT_COLOR = Scalar(255, 255, 255);
    const float TEXT_SCALING = 1.0;
    Mat matrix = Mat(rowHeight_*numRows_, colWidth_*numCols_,
                    COLORTYPE, BACKGROUND_COLOR);
    char currentCharacter;
    /**
     * Double for loop iterates throught each row and column
     * updating currentPosition and placing text using the 
     * putText function
    */
    for (int i = 0; i < Sprite::SPRITE_HEIGHT; ++i) {
        for (int j = 0; j < Sprite::SPRITE_WIDTH; ++j) {
            currentCharacter = sprite_.getCharAt(i, j);
            Point currentPosition = Point(colWidth_ * (j + spriteCurrentCol_),
                                        rowHeight_ * (i + spriteCurrentRow_));
            putText(matrix, string(1, currentCharacter),
                    currentPosition, FONT, TEXT_SCALING, TEXT_COLOR);
        }
    }
    vw.write(matrix);
}

void Asciimation::generateMovie(const string& fname, int frameRate) {
    Size movieSize(numCols_ * colWidth_, numRows_ * rowHeight_);
    int codec = VideoWriter::fourcc('m', 'p', '4', 'v');
    VideoWriter vw;
    vw.open(fname, codec, frameRate, movieSize);
    // Iterates the spriteCurrentCol_ through numCols_
    while (spriteCurrentCol_ <= numCols_) {
        // Adds video writer object to each frame in matrix
        addFrame(vw);
        ++spriteCurrentCol_;
    }

    vw.release();
}
