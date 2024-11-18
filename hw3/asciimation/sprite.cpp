/**
 * \file sprite.cpp
 * \author CS70 Provided Code -- do not copy or share
 *
 * \brief Implements the Sprite class
 *
 * \details
 *
 * \remarks
 *
 */

#include "sprite.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstddef>

using namespace std;

#pragma GCC diagnostic ignored "-Wunused-parameter"

Sprite::Sprite(string fname) {
    ifstream fileIn{fname};
    char c;
    for (int i = 0; i < SPRITE_WIDTH * SPRITE_HEIGHT; ++i) {
        fileIn.get(c);
        // Now c has the next character in the file
        contents_[i] = c;
    }
}

char Sprite::getCharAt(int row, int col) const {
    // Returns an element in the 1D array based on the inputed row and column
    return contents_[(SPRITE_WIDTH*row) + col];
}
