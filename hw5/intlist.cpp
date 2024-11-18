/*
 * intlist.cpp
 * Authors: YOUR ALIASES HERE
 * Implemenation of IntList and IntList::Iter.
 *
 * Part of CS70 Homework 5. This file may NOT be shared with anyone other
 * than the author(s) and the current semester's CS 70 staff without explicit
 * written permission from one of the CS 70 instructors.
 */

#include "intlist.hpp"

#include <utility>
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <cstdlib>
#include <cassert>

// -------------------------
// Implementation of IntList
// -------------------------

IntList::IntList() /* no member init list needed */ {
    selfCheck();
}

IntList::~IntList() {
    while (size_ != 0) {
        pop_front();
    }
    selfCheck();
}

IntList::IntList(const IntList& orig) /* no member init list needed */ {
    for (auto iter = orig.begin(); iter != orig.end(); ++iter) {
        // add all the current value from the original list to the new list
        push_back(*iter);
    }
    selfCheck();
}

void IntList::swap(IntList& rhs) {
    // This is the canonical way to swap arbitrary types; this incantation
    // will call std::swap unless we're swapping a class that provides its
    // own swap function (like we do), in which case that swap is called.
    // Here we end up calling std::swap since the swapped parts are primitives.

    using std::swap;

    swap(back_, rhs.back_);
    swap(front_, rhs.front_);
    swap(size_, rhs.size_);
    selfCheck();
}

void swap(IntList& lhs, IntList& rhs) {
    lhs.swap(rhs);
}

IntList& IntList::operator=(const IntList& rhs) {
    // Assignment is implemented using the copy-and-swap idiom.
    IntList copy = rhs;
    swap(copy);

    selfCheck();
    return *this;
}

size_t IntList::size() const {
    // Returns the size
    return size_;
}

bool IntList::empty() const {
    // return true if size is 0
    return (size_ == 0);
}

bool IntList::operator==(const IntList& rhs) const {
    // if their sizes are not the same, they cannot be equal
    if (size_ != rhs.size_) {
        return false;
    }
    // if there sizes are the same, loop through both (two iterators), and check
    // that each element is the same
    auto rhsCurr = rhs.begin();
    for (auto curr = begin(); curr != end(); ++curr) {
        if (*curr != *rhsCurr) {
            // if we ever reach a point where the nodes aren't the same, we
            // return false
            return false;
        }
        ++rhsCurr;
    }
    // if we never reached a point where the lists are different, they must be
    // the same
    return true;
}

bool IntList::operator!=(const IntList& rhs) const {
    // Idiomatic code: leverage == to implement !=
    return !operator==(rhs);
}

void IntList::push_front(int pushee) {
    // make the new node to add to the front
    front_ = new Node{pushee, front_};
    size_++;
    // if the list is size one, back should be set to front
    if (size_ == 1) {
        back_ = front_;
    }
    selfCheck();
    assert(!empty());
}

int IntList::pop_front() {
    // cannot pop from an empty list
    assert(!empty());
    // save the values of the front so we can return them
    int temp = front_->value_;
    auto nex = front_->next_;
    delete front_;
    if (size_ == 1) {
        // create an empty list if we are deleting the last node
        front_ = nullptr;
        back_ = nullptr;
    } else {
        // if we aren't deleting the last node, set the front node to be what
        // was the second node
        front_ = nex;
    }
    size_--;
    selfCheck();
    return temp;
}

void IntList::push_back(int pushee) {
    selfCheck();
    // if size is 0, let's just push front since it is the same
    if (size_ == 0) {
        push_front(pushee);
    } else {
        // make a new node after back
        back_->next_ = new Node{pushee, nullptr};
        // update back to be the new last node
        back_ = back_->next_;
        size_++;
        selfCheck();
        assert(!empty());
    }
}

void IntList::insert_after(iterator where, int value) {
    // set the node at the location of the iterator to be the new node
    // sets the new node to have the value of the original next of where.current
    where.current_->next_ = new Node{value, where.current_->next_};
    ++size_;
    selfCheck();
    assert(!empty());
}

IntList::iterator IntList::begin() {
    // make an iterator for the current first node
    IntList::iterator iter{front_};
    return iter;
}

IntList::iterator IntList::end() {
    // the past-the-end iterator is always an iterator of a null pointer
    IntList::iterator iter{nullptr};
    return iter;
}

IntList::const_iterator IntList::begin() const {
    // same as above but for const
    IntList::iterator iter{front_};
    return iter;
}

IntList::const_iterator IntList::end() const {
    // same as above but for const
    IntList::iterator iter{nullptr};
    return iter;
}

// given this code, did not change
void IntList::selfCheck() const {
    if (size_ == 0) {
        assert(front_ == nullptr);
        assert(back_ == nullptr);
    } else {
        assert(front_ != nullptr);
        assert(back_ != nullptr);
        if (size_ == 1) {
            assert(front_ == back_);
        } else {
            assert(front_ != back_);
        }
    }
}

// -----------------------------------
// Implementation of IntList::Iter
// -----------------------------------

IntList::Iter::Iter(Node* current) : current_(current) {
    // Nothing else to do.
}

IntList::Iter& IntList::Iter::operator++() {
    // ++ should increment the iterator to move to the next node in the list
    current_ = current_->next_;
    return *this;
}

IntList::Iter::reference IntList::Iter::operator*() const {
    // the operator should return the value of the node at current
    return current_->value_;
}

bool IntList::Iter::operator==(const Iter& rhs) const {
    // check if the two nodes are equal
    return current_ == rhs.current_;
}

bool IntList::Iter::operator!=(const Iter& rhs) const {
    // Idiomatic code: leverage == to implement !=
    return !(*this == rhs);
}
