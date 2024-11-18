/**
 * intlist.hpp
 * A list of ints.
 *
 * Part of CS70 Homework 5. This file may NOT be shared with anyone other
 * than the author(s) and the current semester's CS 70 staff without explicit
 * written permission from one of the CS 70 instructors.
 *
 */

#ifndef INTLIST_HPP_INCLUDED
#define INTLIST_HPP_INCLUDED

#include <utility>
#include <iterator>
#include <cstddef>

#include "const_adaptor.hpp"  // Students don't need to understand this header

/**
 * IntList
 *
 * A linked list of many Node objects that store ints.
 *
 * Class allocates memory dynamically; thus can't use C++'s
 *          defaults for copy constructor, assignment operator and
 *          destructor.
 */
class IntList {
 private:
    // Forward declaration of private class.
    class Iter;

 public:
    // Provide all the usual operations for a forward iterator
    /**
     * \brief    A default constructor
     * \note     Creates an empty list.
     * \note     Requires Θ(1) time.
     */
    IntList();
    /**
     * \brief    A Copy constructor
     * \note     Creates an copy of orig list.
     * \note     Requires Θ(n) time.
     */
    IntList(const IntList& orig);
    /**
     * \brief    An assignment operator
     * \note     Destroys the existing List value of and replaces with rhs.
     * \note     Requires Θ(n) time.
     */
    IntList& operator=(const IntList& rhs);
    /**
     * \brief    A destructor
     * \note     Destroys all list elements and deallocates the respective heap
     * memory \note     Requires Θ(n) time.
     */
    ~IntList();
    /**
     * \brief       Swaps two IntLists
     * \param orig  Reference to a IntList
     * \note        Requires Θ(1) time.
     */
    void swap(IntList& rhs);
    /**
     * \brief       Pushes a new int to the front of the list
     * \param orig  Integer to be added
     * \note        Requires Θ(1) time.
     */
    void push_front(int pushee);  // Push onto head of list
                                  /**
                                   * \brief       Pushes a new int to the end of the list
                                   * \param orig  Integer to be added
                                   * \note        Requires Θ(1) time.
                                   */
    void push_back(int pushee);   // Push onto tail of list
                                  /**
                                   * \brief       Removes int from the front of the list
                                   * \note        Requires Θ(1) time.
                                   * \warning     Users cannot call push_back on an empty list
                                   */
    int pop_front();              // Drop & return the head element
                                  /**
                                   * \brief       Returns number of elements in list
                                   * \note        Requires Θ(1) time.
                                   * \return      size_t
                                   */
    size_t size() const;          // Size of the list
                                  /**
                                   * \brief       Returns boolean, whether there are elements in the list
                                   * \note        Requires Θ(1) time.
                                   */
    bool empty() const;           // true if the list is empty
                                  /**
                                   * \brief         sees if two intLists contain the same elements
                                   * \returns       returns a boolean, true if same lists
                                   */
    bool operator==(const IntList& rhs) const;
    /**
     * \brief         sees if two intLists don't contain the same elements
     * \returns       returns a boolean, true if different lists
     */
    bool operator!=(const IntList& rhs) const;

    ///////////////////////////////
    // Iterator-based functionality
    //
    // We allow users to iterate over the contents of the list.
    //
    // There are two user-facing iterator types: const_iterator and iterator
    // (when people want to iterate over an IntList, they will use one of them,
    // depending on whether they want to modify the list elements or not).
    //
    // They are both defined in terms of our private Iter class, which is
    // defined later on.  The iterator type is a type alias for Iter, and
    // the const_iterator type is a type alias for const_adaptor<Iter>.

    using iterator = Iter;
    using const_iterator = const_adaptor<Iter>;

    iterator begin();              // An iterator set to the first element
    iterator end();                // A "past-the-end" iterator
    const_iterator begin() const;  // A const_iterator set to the first element
    const_iterator end() const;    // A "past-the-end" const_iterator

    /*
     * Insert a value after a given iterator
     *
     * The iterator cannot be end()
     */
    void insert_after(iterator where, int value);

 private:
    /*
     * Node
     *
     * The list is stored as a linked list of Nodes.
     * This type is private so only IntList knows about it.
     *
     */
    struct Node {
        int value_ = 0;         // Value of the list element
        Node* next_ = nullptr;  // Next list node
    };

    // Data members
    Node* front_ = nullptr;  // Current head of list
    Node* back_ = nullptr;   // Current tail of list
    size_t size_ =
        0;  // Current size of list
            // ^-------- by specifying initializations here, we can avoid
            //           needing to specify a member initialization list.

    void selfCheck() const;  // Contains asserts to check IntList is okay

    /*
     * Iterator
     * C++-style iterator for IntList.
     */
    class Iter {
     public:
        // Iterator traits
        //   These definitions are required by the standard library to make
        //   iterators work correctly in generic algorithms.
        using value_type = int;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        // Provide all the usual operations for a forward iterator
        /**
         * \brief    A default constructor
         * \note     Creates an default iterator
         */
        Iter() = default;

        /**
         * \brief        A copy constructor
         * \param orig   iterator to set our new iterator to
         */
        Iter(const Iter& orig) = default;

        /**
         * \brief       iter1 = iter2, the assignment operator
         **/
        Iter& operator=(const Iter& orig) = default;

        /**
         * \brief        A default destructor
         * \note         Destroys the iterator element
         */
        ~Iter() = default;

        /**
         * \brief        Advances the iterator to the next list element
         * \warning      can't advance past the past the end value
         * \returns      the iter reference
         */
        Iter& operator++();

        /**
         * \brief         allows you to access and modify the current element of
         * the iterator \warning       cannot be used on the past the end
         * iterator \returns       returns an int& so that the integer at the
         * current position can be modified
         */
        int& operator*() const;
        /**
         * \brief         sees if two iterators are set to the same list element
         * \warning       cannot be used to compare iterators from different
         * list \returns       returns a boolean, true if the same element
         */
        bool operator==(const Iter& rhs) const;

        /**
         * \brief         sees if two iterators are set to the same list element
         * \warning       cannot be used to compare iterators from different
         * list \returns       returns a boolean, true if a different element
         */
        bool operator!=(const Iter& rhs) const;

     private:
        // Friends can create non-default iterators and access current_.
        friend class IntList;
        explicit Iter(Node* current);

        Node* current_ = nullptr;  // The current list node
    };
};

// Provide a non-member version of swap to allow standard swap(x,y) usage.
void swap(IntList& lhs, IntList& rhs);

#endif  // INTLIST_HPP_INCLUDED
