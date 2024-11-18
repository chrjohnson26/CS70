/* car.hpp
   =========

   Interface definition for the Car class, which generates
   a car with an array of bins

   Part of CS70 Homework 4. This file may NOT be
   shared with anyone other than the author(s) and
   the current semester's CS70 staff without
   explicit written permission from one of the
   CS70 instructors.

 */
#ifndef CAR_HPP_INCLUDED
#define CAR_HPP_INCLUDED

#include <ostream>
#include <cstddef>

/**
 * \class Car
 * \brief Generates a car with bin storage
 *
 * \details
 * Stores an array of bins which will either be empty or full
 * 
 */
class Car {
 public:
    static constexpr int CAPACITY = 4;
    Car(const Car& other) = delete;
    Car& operator=(const Car& other) = delete;
    ~Car() = default;

    Car();
   /**
     * \brief returns the usage of the car
     * \returns size_t of the usage of the car
     * \note const function because it won't change the members of car
     */
    size_t getUsage() const;


   /**
    * \brief returns whether or not the car is empty
    * \returns bool, true if the car is empty
    * \note const function because it won't change the members of car
   */
    bool isEmpty() const;
   /**
      * \brief returns whether or not the car is full
      * \returns bool true if it is full
      * \note const function because it won't change the members of car
   */
    bool isFull() const;

   /**
      * \brief adds a package to the car
      * \warning throws an error if the car is already full
   */
    void addPackage();
   /**
      * \brief removes a package to the car
      * \warning throws an error if the car is already empty
   */
    void removePackage();
   /**
      * \brief prints to the ostream
      * \param outStream the ostream to be printed to
      * \note const function because it won't change the members of car
   */
    void printToStream(std::ostream& outStream) const;


 private:
    bool bins_[CAPACITY];
    size_t binsInUse_;
};

std::ostream& operator<<(std::ostream& os, const Car& car);

#endif   // ifndef CAR_HPP_INCLUDED
