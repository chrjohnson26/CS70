#include "intvector.hpp"

#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

IntVector::IntVector(size_t capacity) :
    arr_{new int[capacity]}, capacity_{capacity}, size_{0}, start_{0} {
    assert(capacity > 0);
}

IntVector::IntVector(const IntVector& orig, size_t capacity)
    : IntVector(capacity) {
    // ^-- This is a delegating constructor.  It calls the default constructor
    //     so that we begin with an empty vector.  Avoids code duplication.

    // To preseve iterator validity, if possible we set start_ to the same
    // value as orig.start_.  If that's not possible, we leave start_ at 0.

    if (orig.capacity_ <= capacity_) {
        start_ = orig.start_;
    }

    // Copy the items from orig, reusing our iterator and push_back functions
    // (if the capacity is sufficient, no resizing will occur)
    for (int elem : orig) {
        push_back(elem);
    }
}

IntVector::IntVector(const IntVector& orig)
    : IntVector(orig, orig.capacity_) {
    // ^-- This is a delegating constructor.  It calls the above constructor
    //     so that we make a copy of orig with the same capacity.  Avoids
    //     code duplication.
}

IntVector& IntVector::operator=(const IntVector& rhs) {
    IntVector copy = rhs;
    swap(copy);
    return *this;
}

IntVector::~IntVector() {
    delete[] arr_;
    arr_ = nullptr;     // Not strictly necessary, but good practice to catch
    size_ = 0;          // bugs where someone tries to use a deleted object
    capacity_ = 0;
}

void IntVector::swap(IntVector& rhs) {
    using std::swap;
    swap(arr_, rhs.arr_);
    swap(capacity_, rhs.capacity_);
    swap(size_, rhs.size_);
    swap(start_, rhs.start_);
}

void IntVector::push_front(int pushee) {
    upsizeIfNeeded();
    // Because the array is circular, we just need to decrement start_ and
    // then write the value, being sure to handle the wraparound case.
    if (start_ == 0) {
        start_ = capacity_ - 1;
    } else {
        --start_;
    }

    arr_[start_] = pushee;          // Add the new element
    ++size_;
}

void IntVector::push_back(int pushee) {
    upsizeIfNeeded();

    // Because the array is circular, we must handle the wraparound case.
    arr_[(start_ + size_) % capacity_] = pushee;
    ++size_;
}

void IntVector::upsizeIfNeeded() {
    if (size_ >= capacity_) {
        adjustCapacity(2 * capacity_);
    }
}

void IntVector::adjustCapacity(size_t newCapacity) {
    assert(newCapacity >= size_);
    // We build a new IntVector and then swap it with this one.  This
    // approach allows us to reuse code from our constructors.

    IntVector newVector(*this, newCapacity);
    swap(newVector);
}

int IntVector::pop_front() {
    assert(size_ > 0);
    // Save the first item
    int firstVal = arr_[start_];

    // Because the array is circular, we don't need to shift items over
    // instead, we just need to update the start index
    start_ = (start_ + 1) % capacity_;

    --size_;
    downsizeIfNeeded();
    return firstVal;
}

int IntVector::pop_back() {
    assert(size_ > 0);
    --size_;

    // Because the array is circular, we need to wrap around to find the
    // last item in the array
    int lastVal = arr_[(start_ + size_) % capacity_];
    downsizeIfNeeded();
    return lastVal;
}

void IntVector::downsizeIfNeeded() {
    if (size_ * 4 <= capacity_) {
        adjustCapacity(capacity_ / 2);
    }
}

size_t IntVector::size() const {
    return size_;
}

bool IntVector::empty() const {
    return size_ == 0;
}

bool IntVector::operator==(const IntVector& rhs) const {
    if (size_ != rhs.size_) {
        // The vectors have different sizes and can't be equal
        return false;
    } else {
        return std::equal(begin(), end(), rhs.begin());
    }
}

bool IntVector::operator!=(const IntVector& rhs) const {
    return !(*this == rhs);
}

int& IntVector::operator[](size_t index) {
    assert(index < size_);
    // The array is circular, so we need to wrap around
    return arr_[(start_ + index) % capacity_];
}

int IntVector::operator[](size_t index) const {
    assert(index < size_);
    // The array is circular, so we need to wrap around
    return arr_[(start_ + index) % capacity_];
}

IntVector::iterator IntVector::begin() {
    return Iter(this, 0);
}

IntVector::iterator IntVector::end() {
    return Iter(this, size_);
}

IntVector::const_iterator IntVector::begin() const {
    return Iter(const_cast<IntVector*>(this), 0);
    // ^-- This is a bit of a hack.  The implementaiton uses a writable
    //     iterator, so we need to cast away the constness.  This is safe
    //     our wrapper class for const_iterator is const-correct.
}

IntVector::const_iterator IntVector::end() const {
    return Iter(const_cast<IntVector*>(this), size_);
}

/////////////////////
// Iter functions
/////////////////////

IntVector::Iter::Iter(IntVector* vec, size_t index)
    : vec_{vec}, index_{index} {
    if (index_ > vec_->size_) {
        // This is an invalid index.  We'll just set it to the end.
        throw std::out_of_range("Invalid index");
    }
    // Nothing else to do
}

IntVector::Iter::reference IntVector::Iter::operator*() const {
    return (*vec_)[index_];
}

IntVector::Iter& IntVector::Iter::operator++() {
    ++index_;
    return *this;
}

bool IntVector::Iter::operator==(const Iter& rhs) const {
    assert(vec_ == rhs.vec_);
    return index_ == rhs.index_;
}

bool IntVector::Iter::operator!=(const Iter& rhs) const {
    return !(*this == rhs);
}
