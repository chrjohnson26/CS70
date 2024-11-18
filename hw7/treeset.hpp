/**
 * treeset.hpp
 * A binary search tree.
 *
 * Part of CS70 Homework 6. This file may NOT be shared with anyone other
 * than the author(s) and the current semester's CS 70 staff without explicit
 * written permission from one of the CS 70 instructors.
 *
 */

#ifndef TREESET_HPP_INCLUDED
#define TREESET_HPP_INCLUDED

#include <utility>
#include <iterator>
#include <cstddef>
#include <string>
#include <iostream>
#include <stack>
#include <algorithm>
#include <cs70/randuint32.hpp>

enum bst_style { LEAF, ROOT, RANDOMIZED };

template <typename T>

class TreeSet {
 private:
    class ConstIter;
    bst_style style_;
    size_t seed_;
    RandUInt32 rand_;

 public:
    TreeSet();
    TreeSet(bst_style style);
    TreeSet(bst_style style, size_t seed);
    TreeSet& operator=(const TreeSet& rhs) = delete;
    ~TreeSet();

    /**
     * \brief Returns size of the tree
     * \post No changes made
     * \returns Size of tree
     */
    size_t size() const;  // Size of the tree

    /**
     * \brief Inserts item into the tree
     * \post List has new item and size increases by one
     * \post Iterators are no longer valid
     */
    void insert(const T& item);

    /**
     * \brief Returns whether item is in tree
     * \post No changes made
     * \returns True if item in tree and False if item not in tree
     */
    bool exists(const T& item) const;

    /**
     * \brief Returns height of the tree
     * \post No changes made
     * \returns height of tree (-1 if tree is empty)
     */
    int height() const;

    /**
     * \brief Returns average depth of the tree
     * \post No changes made
     * \returns average depth of tree (-1 if tree is empty)
     */
    double averageDepth() const;

    /**
     * \brief Returns equality of trees
     * \post No changes made
     * \returns True if trees are equal and False if they are not
     */
    bool operator==(const TreeSet& rhs) const;

    /**
     * \brief Returns inequality of trees
     * \post No changes made
     * \returns True if trees are not equal and False if they are
     */
    bool operator!=(const TreeSet& rhs) const;

    /**
     * \brief Visualizes the tree
     * \post Prints out root and leaves
     * \returns the outStream that was passed in
     */
    std::ostream& printToStream(std::ostream& outStream) const;

    /**
     * \brief Visualizes the tree
     * \post Prints out root and leaves
     * \returns the outStream that was passed in
     */
    std::ostream& printSizesToStream(std::ostream& outStream) const;

    /**
     * \brief Prints statistics that describe the tree
     * \post Prints out ...
     * \returns the outStream that was passed in
     */
    std::ostream& showStatistics(std::ostream& outStream) const;

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

    using const_iterator = ConstIter;

    /**
     * \brief Returns an iterator that is set to the first element of the list
     * \post N/A
     * \returns iterater at first element or past-the-end iterator if empty
     */
    const_iterator begin() const;  // An iterator set to the first element

    /**
     * \brief Returns a past-the-end iterator
     * \post N/A
     * \returns past-the-end iterator
     */
    const_iterator end() const;  // A "past-the-end" iterator

    /*
     * Insert a value after a given iterator
     *
     * The iterator cannot be end()
     */
    void insert_after(const_iterator where, int value);

 private:
    /*
     * Node
     *
     * The tree is stored as a linked list of Nodes.
     *        This type is private so only TreeSet knows about it.
     *
     */
    struct Node {
        T value_;                // Value of the node
        Node* left_ = nullptr;   // Left subtree
        Node* right_ = nullptr;  // Right subtree
        size_t size_ = 1;        // Current size of tree
    };

    // Helper functions

    /**
     * \brief Destroys and deallocates the given root
     * \post Root is destroyed/deallocated
     */
    static void destructorHelper(Node* root);

    /**
     * \brief Inserts an item into a subtree using recursion
     * \post Node is added
     */
    static void insertLeafHelper(Node*& root, const T& item);

    /**
     * \brief Inserts an item into a subtree using recursion
     * \post Node added becomes the root
     */
    static void insertRootHelper(Node*& root, const T& item);

    /**
     * \brief Inserts an item into a subtree using recursion
     * \post Node added to tree
     */
    void insertRandomHelper(Node*& root, const T& item);

    /**
     * \brief Shifts tree right
     * \post Root is changed
     */
    static void rotateRight(Node*& root);

    /**
     * \brief Shifts tree left
     * \post Root is changed
     */
    static void rotateLeft(Node*& root);

    /**
     * \brief Checks if an item is in a tree using recursion
     * \post Nothing changed
     * \return True if it exists and False if it does not
     */
    static bool existsHelper(Node* root, const T& item);

    /**
     * \brief Displays a tree using recursion
     * \post Nothing changed
     */
    static std::ostream& displayHelper(Node* root, std::ostream& outStream);

    /**
     * \brief Displays a tree using recursion
     * \post Nothing changed
     */
    static std::ostream& displaySizeHelper(Node* root, std::ostream& outStream);

    /**
     * \brief Counts the depth
     * \post total depth
     * \return total depth calculated
     */
    static double depthHelper(Node* root, int count);

    /**
     * \brief Counts the height
     * \post highest depth counted
     * \return height
     */
    static int heightHelper(Node* root);

    /**
     * \brief Counts the size
     * \post gives size
     * \return size
     */
    static size_t nodeSize(const Node* root);

    // Data members
    Node* root_ = nullptr;  // Current root of the tree

    /*
     * Iterator
     * C++-style iterator for IntList.
     */
    class ConstIter {
     private:
        friend class TreeSet;
        explicit ConstIter(Node* root);
        void pushToMinimum(Node* root_);
        std::stack<Node*> stack_;

     public:
        // Iterator traits
        //   These definitions are required by the standard library to make
        //   iterators work correctly in generic algorithms.
        using value_type = T;
        using reference = const value_type&;
        using pointer = const value_type*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        // Provide all the usual operations for a forward iterator

        ConstIter() = default;
        ConstIter(const ConstIter&) = default;
        ConstIter& operator=(const ConstIter&) = default;
        ~ConstIter() = default;

        ConstIter& operator++();
        const T& operator*() const;
        bool operator==(const ConstIter& rhs) const;
        bool operator!=(const ConstIter& rhs) const;
    };
};

template <typename T>

std::ostream& operator<<(std::ostream& os, const TreeSet<T>& t);

#include "treeset-private.hpp"

#endif  // TREESET_HPP_INCLUDED
