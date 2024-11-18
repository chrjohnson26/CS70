#ifndef INT_VECTOR_INCLUDED_HPP
#define INT_VECTOR_INCLUDED_HPP

#include <utility>
#include <iterator>
#include <cstddef>

#include "const_adaptor.hpp"  // Students don't need to understand this header

class IntVector {
 private:
    // Forward declarations
    class Iter;

 public:
    /**
     * \brief Constructs an empty IntVector, optionally with a given capacity
     * \warning The capacity must be not be zero.
     */
    IntVector(size_t capacity = 1);

    /**
     * \brief Constructs a deep copy of orig, into an IntVector with a given
     *        capacity
     * \param orig  an existing IntVector to be copied
     * \param capacity  the capacity of the new IntVector
     */
    IntVector(const IntVector& orig, size_t capacity);

    /**
     * \brief Constructs a deep copy of orig
     * \param orig  an existing IntVector to be copied
     */
    IntVector(const IntVector& orig);

    /**
     * \brief Makes this IntVector a deep copy of rhs
     * \param rhs  an existing IntVector to be copied
     * \returns    a reference to this IntVector
     */
    IntVector& operator=(const IntVector& rhs);

    /**
     * \brief Destructor
     */
    ~IntVector();

    /**
     * \brief Swaps all members between this IntVector and rhs
     * \param rhs  an existing IntVector to swap with
     */
    void swap(IntVector& rhs);

    /**
     * \brief Adds the given int to the front of the list
     * \param pushee  the int to push to the list
     */
    void push_front(int pushee);

    /**
     * \brief Adds the given int to the back of the list
     * \param pushee  the int to push to the list
     */
    void push_back(int pushee);

    /**
     * \brief Removes and returns the first item of the list
     * \returns the first int in the list
     * \warning Calling pop_front on an empty list is against the rules
     */
    int pop_front();

    /**
     * \brief Removes and returns the last item of the list
     * \returns the last int in the list
     * \warning Calling pop_back on an empty list is against the rules
     */
    int pop_back();

    /**
     * \brief Returns the number of items in the list
     * \returns the number of items in the list
     */
    size_t size() const;

    /**
     * \brief Returns true if the list is empty, false otherwise
     * \returns a boolean indicating whether the list is empty
     */
    bool empty() const;

    /**
     * \brief Compares the contents of two lists
     * \param rhs  an IntVector to compare to
     * \returns true if this IntVector has the same contents in the same order
     * as rhs, false otherwise
     */
    bool operator==(const IntVector& rhs) const;

    /**
     * \brief Compares the contents of two lists
     * \param rhs  an IntVector to compare to
     * \returns false if this IntVector has the same contents in the same order
     * as rhs, true otherwise
     */
    bool operator!=(const IntVector& rhs) const;

    /**
     * \brief Returns the int at the given index (for a const IntVector)
     * \param index  The index of the item to return
     * \returns The item at the given index
     * \warning An out-of-bounds index has undefined behavior
     */
    int operator[](size_t index) const;

    /**
     * \brief Returns the int at the given index (for a non-const IntVector)
     * \param index  The index of the item to return
     * \returns A reference to the item at the given index
     * \warning An out-of-bounds index has undefined behavior
     */
    int& operator[](size_t index);

    ///////////////////////////////
    // Iterator-based functionality
    //
    // We allow users to iterate over the contents of the vector.
    //
    // There are two user-facing iterator types: const_iterator and iterator
    // (when people want to iterate over an IntVector, they will use one of
    // them, depending on whether they want to modify the elements or not).
    //
    // They are both defined in terms of our private Iter class, which is
    // defined later on.  The iterator type is a type alias for Iter, and
    // the const_iterator type is a type alias for const_adaptor<Iter>.

    using iterator = Iter;
    using const_iterator = const_adaptor<Iter>;

    /**
     * \brief Creates and returns an iterator positioned at the first item
     * \returns An iterator positioned at the first item
     */
    iterator begin();

    /**
     * \brief Creates and returns an iterator positioned "just past" the last
     *        item
     * \returns An iterator positioned "just past" the last item
     * \warning The returned iterator can only be used for comparison and
     *          reassignment (or be destroyed).  There is no list item for
     *          operator* to access, and ++ does not make sense when we
     *          are already past the end.
     */
    iterator end();

    /**
     * \brief Creates and returns an const_iterator positioned at the first
     *        item
     * \returns An iterator positioned at the first item
     */
    const_iterator begin() const;

    /**
     * \brief Creates and returns an const_iterator positioned "just past" the
     *        last item
     * \returns An iterator positioned "just past" the last item
     * \warning The returned iterator can only be used for comparison and
     *          reassignment (or be destroyed).  There is no list item for
     *          operator* to access, and ++ does not make sense when we
     *          are already past the end.
     */
    const_iterator end() const;

 private:
    // Data members
    int* arr_;         // Contains the items in the list
    size_t capacity_;  // The size of the array
    size_t size_;      // The number of items in the list
    size_t start_;     // The index of the first item in the list

    class Iter {
        friend class IntVector;

     public:
        // Iterator traits
        //   These definitions are required by the standard library to make
        //   iterators work correctly in generic algorithms.
        using value_type        = int;
        using reference         = value_type&;
        using pointer           = value_type*;
        using difference_type   = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        /**
         * \brief Constructs an invalid iterator
         * \warning A default-constructed iterator can only be reassigned, or
         *          destroyed.  It cannot be dereferenced or incremented.
         */
        Iter() = default;

        // The synthesized copy constructor, copy assignment operator, and
        // destructor are fine.
        Iter(const Iter& orig) = default;
        Iter& operator=(const Iter& rhs) = default;
        ~Iter() = default;

        /**
         * \brief Accesses the item at the current position
         * \returns A reference to the int at the current position
         * \warning It is against the rules to call operator* on an iterator
         *          that is past-the-end or isn't valid (such as a default-
         *          constructed iterator)
         */
        int& operator*() const;

        /**
         * \brief Advances the iterator to the next position
         * \returns A reference to the iterator
         * \warning Advancing a past-the-end iterator is not allowed
         */

        Iter& operator++();
        /**
         * \brief Compares the positions of two iterators
         * \returns True when two iterators have the same position
         * \warning Comparing iterators from different IntVectors is not allowed
         */

        bool operator==(const Iter& rhs) const;

        /**
         * \brief Compares the positions of two iterators
         * \returns True when two iterators don't the same position
         * \warning Comparing iterators from different IntVectors is not allowed
         */
        bool operator!=(const Iter& rhs) const;

     private:
        /**
         * \brief Constructs an iterator positioned at the given location
         * \param curLoc The address of the item in the array at which the
         * iterator should be positioned
         */
        Iter(IntVector* vec, size_t index = 0);

        IntVector* vec_ = nullptr;  // The IntVector we're iterating over
        size_t index_ = 0;          // The index of the current item
    };

    // Private helper functions

   /**
     * \brief Doubles the capacity if the list is full
     */
    void upsizeIfNeeded();

    /**
     * \brief Halves the capacity if the list is 1/4 full
     */
    void downsizeIfNeeded();

    /**
     * \brief Changes the capacity of the list to the given value
     * \param newCapacity  the new capacity of the list
     */
    void adjustCapacity(std::size_t newCapacity);
};

/**
 * \brief Swaps the values of all members of two IntList objects
 * \param lhs   One of the lists to be swapped
 * \param rhs   The other list to be swapped
 */
void swap(IntVector& lhs, IntVector& rhs);

#endif  // INT_VECTOR_INCLUDED_HPP
