/**
 * car.cpp
 * Author(s): Maddie Reeve and Christian Johnson
 *
 * Part of CS70 Homework 4. This file may NOT be
 * shared with anyone other than the author(s) and
 * the current semester's CS70 staff without
 * explicit written permission from one of the
 * CS70 instructors.
 *
 */

#include "car.hpp"

#include <iostream>
#include <ostream>
#include <cstddef>
#include <stdexcept>

Car::Car():
    binsInUse_{0}
{
    // sets all the bins to be initially empty
    for (size_t i = 0; i < CAPACITY; ++i) {
        bins_[i] = false;
    }
}

size_t Car::getUsage() const {
    // Returns the amount of bins in usage
    return binsInUse_;
}

bool Car::isEmpty() const {
    // Returns a bool value based on the binsInUse_ variables
    return binsInUse_ == 0;
}

bool Car::isFull() const {
    // Returns a bool value based on the binsInUse_ and CAPACITY variables
    return binsInUse_ == CAPACITY;
}

void Car::addPackage() {
    // checks if we can add a package and increments binsInUse_ if possible
    if (!isFull()) {
        bins_[binsInUse_] = true;
        ++binsInUse_;
    } else {
        // throw this error if we can't add a new package
        throw std::length_error("Train is already full!");
    }
}

void Car::removePackage() {
    // checks if we can remove a package
    if (!isEmpty()) {
        bins_[binsInUse_ - 1] = false;
        --binsInUse_;
    } else {
        // throw this error if we can't remove a new package
        throw std::length_error("Train is empty!");
    }
}

void Car::printToStream(std::ostream& outStream) const {
    // loops through all the elements of the car
    for (size_t i = 0; i < CAPACITY; ++i) {
        if (bins_[i]) {
            // prints this to represent a package
            outStream << "[x]";
        } else {
            // prints this to represent an empty bin
            outStream << "[_]";
        }
    }
    // this symbol will be the connecter between cars
    outStream << "~";
}
std::ostream& operator<<(std::ostream& os, const Car& car) {
    car.printToStream(os);

    // To allow chaining of <<, we always return the stream we were given.
    return os;
}
