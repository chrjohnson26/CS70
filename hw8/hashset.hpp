/**
 * hashset.hpp
 *
 * Authors: Christian and Olivia
 *
 * Provides HashSet<T>, a set class template, using hash tables
 *
 * Part of CS70 Homework 8. This file may NOT be shared with anyone other
 * than the author(s) and the current semester's CS70 staff without explicit
 * written permission from one of the CS70 instructors.
 */

#ifndef HASHSET_HPP_INCLUDED
#define HASHSET_HPP_INCLUDED

#include <iostream>
#include <forward_list>
#include <utility>
#include <cstddef>

template <typename T>
class HashSet {
 public:
    /* \brief Default number of buckets, used by constructor but also
     *        accessible to client code
     */
    static constexpr size_t DEFAULT_NUM_BUCKETS = 10;
    /* \brief Default maximum load factor, used by constructor but also
     *        accessible to client code
     */
    static constexpr double DEFAULT_MAX_LOAD_FACTOR = 4.0;

    /* \brief Parameterized constructor
     * \param initial number of buckets in the hash table
     * \param maximum load factor
     * This constructor is also the default constructor
     */
    explicit HashSet(size_t numBuckets = DEFAULT_NUM_BUCKETS,
                     double maxLoadFactor = DEFAULT_MAX_LOAD_FACTOR);

    // Copy constructor and assignment operator are disabled.  You are
    // allowed to implement them if you want, but you don't have to.

    HashSet(const HashSet<T>& other) = delete;
    HashSet<T>& operator=(const HashSet<T>& other) = delete;

    /* \brief Swaps the contents of two HashSet<T> objects
     * \param the HashSet<T> to swap with
     * \note Requires Θ(1) time.
     */
    void swap(HashSet<T>&);

    /* \brief Destructor
     * \note Requires Θ(n) time, where n is the number of elements in the set.
     */
    ~HashSet();

    /* \brief Returns the number of values in the hash table
     * \note Takes Θ(1) time.
     */
    size_t size() const;

    /* \brief Inserts an item into the hash table
     * \param the item to insert
     * \note Takes Θ(1) amortized expected time under the probability model
     *       discussed in the lesson, with a O(n) time bound.
     */
    void insert(const T&);

    /* \brief Inserts an item into the hash table w/o checking if it exists
     * \param the item to insert
     * \note Takes Θ(1) amortized expected time under the probability model
     *       discussed in the lesson, with a O(n) time bound.
     */
    void newInsert(const T&);

    /* \brief Returns whether an item is in the hash table
     * \param the item to search for
     * \note Takes Θ(1) amortized expected time under the probability model
     *       discussed in the lesson, with a O(n) time bound.
     */
    bool exists(const T&) const;

    /* \brief Prints the hash table to a stream
     * \param the stream to print to
     */
    std::ostream& printToStream(std::ostream&) const;

    /* \brief Sets the maximum load factor
     * \param the new maximum load factor
     * \note Takes Θ(1) time.  The hash table is not rehashed by this call.
     */
    void maxLoadFactor(double);

    /* \brief Gets the max load factor
     * \returns max load factor
     */
    double getMaxLoad();

    /* \brief Rehashes the hash table
     * \note Takes Θ(n) time.
     */
    void rehash();

    /* \brief Returns the number of buckets in the hash table
     * \note Takes Θ(1) time.
     */
    size_t buckets() const;

    /* \brief Returns the current load factor of the hash table
     * \note Takes Θ(1) time.
     */
    double loadFactor() const;

    /* \brief Returns the number of times the hash table has been reallocated
     * \note Takes Θ(1) time.
     */
    size_t reallocations() const;

    /* \brief Returns the number of collisions since the last reallocation
     * \note Takes Θ(1) time.
     */
    size_t collisions() const;

    /* \brief Returns the maximal number of steps taken to find a key since the
     * last reallocation \note Takes Θ(1) time.
     */
    size_t maximal() const;

    /* \brief Prints statistics about the hash table to a stream
     * \param the stream to print to
     */
    std::ostream& showStatistics(std::ostream&) const;

 private:
    // Data members
    std::forward_list<T>* buckets_;  // contains the items in the hash
    size_t numBuckets_;              // Number of buckets
    double maxLoad_;          // Maximum allowed load factor for the hash table
    size_t size_;             // Size of table
    size_t numHash_;          // Number of times the table has been rehashed
    size_t collisions_;       // Number of collisions
    mutable size_t maximal_;  // maximal number of steps

    // HELPER FUNCTIONS
    /* \brief checks if it exists when inserting
     */
    bool insertExists(const T& value) const;
};

template <typename T>
std::ostream& operator<<(std::ostream&, const HashSet<T>&);

#include "hashset-private.hpp"

#endif  // HASHSET_HPP_INCLUDED
