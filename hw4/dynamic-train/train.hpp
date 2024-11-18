/* train.hpp
   =========

   Interface definition for the Car class, which generates
   a car with an array of bins

   Part of CS70 Homework 4. This file may NOT be
   shared with anyone other than the author(s) and
   the current semester's CS70 staff without
   explicit written permission from one of the
   CS70 instructors.

 */

#ifndef TRAIN_HPP_INCLUDED
#define TRAIN_HPP_INCLUDED

#include <ostream>
#include <cstddef>
#include "car.hpp"

enum traintype { BASIC, SMART };

class Train {
 public:
    Train() = delete;
    Train(const Train& other) = delete;
    Train& operator=(const Train& other) = delete;

    Train(traintype type);

    ~Train();

   /**
   * \brief    adds a package to the train
   * \note     this method calls on upsize if needed
   */
    void addPackage();
   /**
   * \brief    removes a package from the train
   * \note     this method calls on downsize if needed
   */
    void removePackage();

   /**
   * \brief    prints our train to the ostream
   * \param    outStream the ostream to print to
   * \note     uses the print method for the car
   */
    void printToStream(std::ostream& outStream) const;


 private:
    Car* cars_;
    size_t numCars_;
    size_t usage_;
    size_t revenue_;
    size_t operatingCost_;
    static constexpr double HANDLING_COST = 1.0;
    static constexpr double SHIPPING_COST = 4.0;
    static constexpr size_t BASIC_SIZE_CHANGE = 1;
    static constexpr size_t SMART_SIZE_CHANGE = 2;
    static constexpr size_t SMART_DOWNSIZE_THRESHOLD = 4;
    traintype type_;

    /**
     * \brief Changes the size of a train
     * \param size the size for the new train
     * \post The current train size are up to date.
     */
    void changeSize(size_t size);

    /**
     * \brief Check if the train needs to increase in size 
     * and then doing so via changeSize if necessary.
     */
    void upSizeIfNeeded();

    /**
     * \brief Check if the train needs to decrase in size 
     * and then calling changeSize if necessary.
     */
    void downSizeIfNeeded();

    /**
     * \brief Moves packages onto a train when moving packages
     * from train to train when changing sizes.
     */
    void loadPackage();
};

std::ostream& operator<<(std::ostream& os, const Train& train);

#endif   // ifndef CAR_HPP_INCLUDED
