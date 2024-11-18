/**
 * train.cpp
 * Author(s): Maddie Reeve and Christian Johnson
 *
 * Part of CS70 Homework 4. This file may NOT be
 * shared with anyone other than the author(s) and
 * the current semester's CS70 staff without
 * explicit written permission from one of the
 * CS70 instructors.
 *
 */
#include "train.hpp"
#include "car.hpp"
#include <ostream>
#include <cstddef>

Train::Train(traintype type)
    : cars_{new Car[1]},
      numCars_{1},
      usage_{0},
      revenue_{0},
      operatingCost_{0},
      type_{type} {
    // Nothing to do here! Everything is initialized!
}
Train::~Train() {
    delete[] cars_;
}

void Train::addPackage() {
    upSizeIfNeeded();
    loadPackage();
    // increases the revenue because work has been done
    revenue_ += SHIPPING_COST;
}

void Train::removePackage() {
    // check if there is a package to be removed
    if (usage_ > 0) {
        --usage_;
        // finds the last car and calls remove package
        cars_[usage_ / Car::CAPACITY].removePackage();
        downSizeIfNeeded();
    }
}

void Train::printToStream(std::ostream& outStream) const {
    outStream << "(";
    outStream << revenue_;
    outStream << ", ";
    outStream << operatingCost_;
    outStream << ") ";
    // loops through and prints each car
    // uses the car printToStream method
    for (size_t i = 0; i < numCars_; ++i) {
        outStream << cars_[i];
    }
}

void Train::changeSize(size_t size) {
    Car* oldCars = cars_;
    size_t numOld = usage_;

    cars_ = new Car[size];
    numCars_ = size;
    usage_ = 0;

    // loads a package for each package that was there previously
    for (size_t i = 0; i < numOld; ++i) {
        loadPackage();
    }
    // deletes the old cars
    delete[] oldCars;
}

void Train::upSizeIfNeeded() {
    // checks if the train is full and we are trying to add
    if (cars_[numCars_ - 1].isFull()) {
        if (type_ == BASIC) {
            changeSize(BASIC_SIZE_CHANGE + numCars_);
        } else {
            changeSize(SMART_SIZE_CHANGE * numCars_);
        }
    }
}

void Train::downSizeIfNeeded() {
    // checks if there is at least one car in the train
    if (numCars_ > 1) {
        // checks the type and if the last car is empty
        if (type_ == BASIC && cars_[numCars_ - 1].isEmpty()) {
            changeSize(numCars_ - BASIC_SIZE_CHANGE);
        } else {
            // changes by the smart threshold
            if (usage_ <= numCars_ * Car::CAPACITY / SMART_DOWNSIZE_THRESHOLD) {
                changeSize(numCars_ / SMART_SIZE_CHANGE);
            }
        }
    }
}

void Train::loadPackage() {
    size_t i = 0;
    // finds the index of the first car in the train that isn't full
    while (cars_[i].isFull()) {
        ++i;
    }
    cars_[i].addPackage();
    ++usage_;
    operatingCost_ += HANDLING_COST;
}

std::ostream& operator<<(std::ostream& os, const Train& train) {
    train.printToStream(os);

    // To allow chaining of <<, we always return the stream we were given.
    return os;
}
