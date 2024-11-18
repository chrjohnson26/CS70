/**
 * hashset-private.hpp
 * Authors: Christian and Olivia
 *
 * Implements HashSet<T>, a hash-table class template
 *
 * Part of CS70 Homework 8. This file may NOT be shared with anyone other
 * than the author(s) and the current semester's CS70 staff without explicit
 * written permission from one of the CS70 instructors.
 */

#ifndef HASHSET_HPP_INCLUDED
#warning "Don't include this file directly. Include hashset.hpp instead."
#endif

#pragma GCC diagnostic ignored "-Wunused-private-field"  // FIXME: Remove soon.
#pragma GCC diagnostic ignored "-Wunused-parameter"      // FIXME: Remove soon.

#include <iostream>
#include <forward_list>
#include <stdexcept>
#include <utility>
#include <cstddef>
#include <cassert>
#include <cmath>

template <typename T>
HashSet<T>::HashSet(size_t numBuckets, double maxLoadFactor)
    : buckets_{new std::forward_list<T>[numBuckets]},
      numBuckets_{numBuckets},
      maxLoad_{maxLoadFactor},
      size_{0},
      numHash_{0},
      collisions_{0},
      maximal_{0} {
    // nothing needed here! everything initialized
}

template <typename T>
void HashSet<T>::swap(HashSet<T>& other) {
    using std::swap;
    // go through and call std::swap on all the data members
    swap(buckets_, other.buckets_);
    swap(numBuckets_, other.numBuckets_);
    swap(maxLoad_, other.maxLoad_);
    swap(size_, other.size_);
}

template <typename T>
HashSet<T>::~HashSet() {
    // Returns private member variable
    delete[] buckets_;
}

template <typename T>
size_t HashSet<T>::size() const {
    // returns the size
    return size_;
}

template <typename T>
void HashSet<T>::insert(const T& value) {
    // checks if value is already in hash
    if (!(insertExists(value))) {
        // finds location with helper
        size_t locationInsert = myhash(value) % numBuckets_;
        if (!buckets_[locationInsert].empty()) {
            ++collisions_;
        }
        // inserts value
        buckets_[locationInsert].push_front(value);
        ++size_;
        if (loadFactor() > maxLoad_) {
            rehash();
        }
    }
}

template <typename T>
void HashSet<T>::newInsert(const T& value) {
    // finds location with helper
    size_t locationInsert = myhash(value) % numBuckets_;
    // inserts value
    buckets_[locationInsert].push_front(value);
    ++size_;
}

template <typename T>
bool HashSet<T>::exists(const T& value) const {
    // uses myhash function and current number of buckets to find correct bucket
    size_t locationCheck = myhash(value) % numBuckets_;
    size_t count = 0;
    for (auto i = buckets_[locationCheck].begin();
         i != buckets_[locationCheck].end(); ++i) {
        ++count;
        // count keeps track of length of bucket and updates maximal_
        // accordingly
        if (*i == value) {
            if (count > maximal_) {
                maximal_ = count;
            }
            return true;
        }
    }
    if (count > maximal_) {
        maximal_ = count;
    }
    return false;
}

template <typename T>
bool HashSet<T>::insertExists(const T& value) const {
    // uses myhash function and current number of buckets to find correct bucket
    size_t locationCheck = myhash(value) % numBuckets_;
    size_t count = 1;
    // count keeps track of length of bucket and updates maximal_
    // accordingly
    for (auto i = buckets_[locationCheck].begin();
         i != buckets_[locationCheck].end(); ++i) {
        ++count;
        if (*i == value) {
            if (count > maximal_) {
                maximal_ = count;
            }
            return true;
        }
    }
    if (count > maximal_) {
        maximal_ = count;
    }
    return false;
}

template <typename T>
std::ostream& HashSet<T>::printToStream(std::ostream& out) const {
    for (size_t val = 0; val < numBuckets_; ++val) {
        out << "[";
        out << val;
        out << "]";
        for (auto item = buckets_[val].begin(); item != buckets_[val].end();
             ++item) {
            // prints ", " unless at beginning of the current bucket
            if (!(item == buckets_[val].begin())) {
                out << ", ";
            }
            out << *item;
        }
        out << "\n";
    }
    return out;
}

template <typename T>
void HashSet<T>::maxLoadFactor(double newMaxLoadFactor) {
    // sets maxLoadFactor to new value
    maxLoad_ = newMaxLoadFactor;
}

template <typename T>
double HashSet<T>::getMaxLoad() {
    // gets the maxLoadFactor
    return maxLoad_;
}

template <typename T>
void HashSet<T>::rehash() {
    // make new empty hash with load half the size of maxLoad
    HashSet<T> newHash{numBuckets_ * 2, maxLoad_};
    // put all the values from the old hash into the new one
    for (size_t val = 0; val < numBuckets_; ++val) {
        for (auto item = buckets_[val].begin(); item != buckets_[val].end();
             ++item) {
            newHash.newInsert(*item);
        }
    }
    // swap the old and new hashes
    swap(newHash);
    ++numHash_;
}

template <typename T>
size_t HashSet<T>::buckets() const {
    // returns the number of buckets in the hash table
    return numBuckets_;
}

template <typename T>
double HashSet<T>::loadFactor() const {
    // returns the load factor
    // checks if dividing by 0
    if (numBuckets_ == 0) {
        return 0;
    }
    return double(size_) / numBuckets_;
}

template <typename T>
size_t HashSet<T>::reallocations() const {
    // Return the number of times the table has been rehashed
    return numHash_;
}

template <typename T>
size_t HashSet<T>::collisions() const {
    // returns the number of times we inserted into a non-empty bucket
    return collisions_;
}

template <typename T>
size_t HashSet<T>::maximal() const {
    // returns the longest run in the hash set
    return maximal_;
}

template <typename T>
std::ostream& HashSet<T>::showStatistics(std::ostream& out) const {
    // reallocations() counts expansions
    return out << reallocations() << " expansions"
               << ", "
               // loadFactor() calculates the load factor
               // collisions() gets the collisions member variable
               << "load factor " << loadFactor() << ", " << collisions()
               << " collisions"
               << ", "
               // maximal() counts the longest bucket
               << "longest run " << maximal() << std::endl;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const HashSet<T>& hashSet) {
    // overrides print operator
    return hashSet.printToStream(out);
}
