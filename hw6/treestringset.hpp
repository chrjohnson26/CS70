/**
 * treestringset.hpp
 *
 * Part of CS70 Homework 6. This file may NOT be shared with anyone other
 * than the author(s) and the current semester's CS 70 staff without explicit
 * written permission from one of the CS 70 instructors.
 *
 */

#ifndef TREESTRINGSET_HPP_INCLUDED
#define TREESTRINGSET_HPP_INCLUDED

#include <utility>
#include <iterator>
#include <cstddef>
#include <iostream>
#include <string>
#include <stack>

/**
 * TreeStringSet
 *
 * A binary tree of many Node objects that store Strings.
 */

class TreeStringSet {
 private:
    class ConstIter;

 public:
    /**
     * \brief    A default constructor
     * \note     Creates an empty tree.
     */
    TreeStringSet();

    /**
     * \brief    A destructor
     * \note     Destroys all tree elements and deallocates the respective heap
     * memory         */
    ~TreeStringSet();

    /**
     * \brief the copy constructor and assignment operators are disabled
     */
    TreeStringSet(TreeStringSet& orig) = delete;
    TreeStringSet& operator=(TreeStringSet& orig) = delete;

    // Size of the list
    /**
     * \brief       Returns number of elements in the list
     * \returns     size_t, the number of elements
     * \note        Requires Θ(1) time.
     */
    size_t size() const;

    /**
     * \brief       Inserts the given item into the tree
     * \param str   const std::string& item to insert
     * \note        Requires Θ(height) time.
     */
    void insert(const std::string& str);

    /**
     * \brief       Returns whether the item is found in the tree
     * \returns     bool, whether the element is in the list already
     * \note        Requires Θ(height) time.
     * \note        Can be called on a read-only tree
     */
    bool exists(const std::string& str) const;

    /**
     * \brief       Returns the height of the tree
     * \returns     int, height of the tree
     * \note        Requires Θ(n) time.
     * \note        Can be called on a read-only tree
     */
    int height() const;

    /**
     * \brief       Returns the average depth of the tree
     * \returns     double, average height of the tree
     * \note        Requires Θ(n) time.
     * \note        Can be called on a read-only tree
     */
    double averageDepth() const;

    /**
     * \brief       Tests if the two trees have the same values
     * \returns     bool, whether the two trees have the same values
     * \note        Requires Θ(n) time.
     * \note        Can be called on a read-only tree
     */
    bool operator==(const TreeStringSet& rhs) const;

    /**
     * \brief       Tests if the two trees have different values
     * \returns     bool, whether the two trees have different values
     * \note        Requires Θ(n) time.
     * \note        Can be called on a read-only tree
     */
    bool operator!=(const TreeStringSet& rhs) const;

    /**
     * \brief       Prints representation of the tree
     * \returns     std::ostream&, tree in required format
     * \note        Can be called on a read-only tree
     */
    std::ostream& printToStream(std::ostream& out) const;

    /**
     * \brief       Prints statistics about the tree
     * \returns     std::ostream&, tree statistics
     * \note        Can be called on a read-only tree
     */
    std::ostream& showStatistics(std::ostream&) const;

    using const_iterator = ConstIter;

    /**
     * \brief       creates a iterator set to the first node of the tree
     * \returns     const_iterator, set to the tree's first node
     * \note        Can be called on a read-only tree
     * \note        Requires Θ(height) time.
     */
    const_iterator begin() const;

    /**
     * \brief       creates a iterator set to the "past the end" node of the
     * tree \returns     const_iterator, set to the tree's "past the end" node
     * \note        Can be called on a read-only tree
     * \note        Requires Θ(1) time.
     */
    const_iterator end() const;

 private:
    /*
     * Node
     * The list is stored as a linked list of Nodes.
     * This type is private so only IntList knows about it.
     *
     */
    struct Node {
        std::string value_;      // Value of the list element
        Node* left_ = nullptr;   // left  node
        Node* right_ = nullptr;  // right node
    };

    // necessary member variables size and root
    size_t size_;
    Node* root_;

    /**
     * \brief Delete subtree function, a helper function for the destructor
     * \param root the root of the subtree to delete
     */

    // our helper functions:
    static void deleteSubtree(Node* root);

    /**
     * \brief       helper function for insert
     * \param tree  Node*&, reference to a pointer to a Node
     * \param str   const std::string&, string reference of element to be
     * inserted
     */
    static void insertHelper(Node*& tree, const std::string& str);

    static bool existsHelper(Node* root, const std::string& str);

    /**
     * \brief       helper function for printToStream
     * \param root  Node*, pointer to a Node
     * \param out   const std::string&, string reference
     */
    static std::ostream& display(Node* root, std::ostream& out);

    /**
     * \brief       helper function for depth
     * \param root  Node*, pointer to a Node
     * \param count size_t, current count of nodes
     * \returns     double, number of nodes in the given tree
     */
    static double depthHelper(Node* root, size_t count);

    /**
     * \brief       helper function for height
     * \param root  Node*, pointer to a Node inserted
     * \returns     int, length of current branch
     */
    static int heightHelper(Node* root);
    // our const iterator specifications
    class ConstIter {
     private:
        friend class TreeStringSet;
        std::stack<Node*> stack_;
        // helper functions
        void pushToMinimum(Node* root);

     public:
        using value_type = std::string;
        using reference = const value_type&;
        using pointer = const value_type*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        ConstIter(Node* root);

        /**
         * \brief    A default constructor
         * \note     Creates an default iterator
         */
        ConstIter() = default;

        /**
         * \brief        A copy constructor
         * \param orig   iterator to set our new iterator to
         */
        ConstIter(const ConstIter& orig) = default;

        /**
         * \brief       iter1 = iter2, the assignment operator
         **/
        ConstIter& operator=(const ConstIter& orig) = default;

        /**
         * \brief        A default destructor
         * \note         Destroys the iterator element
         */
        ~ConstIter() = default;

        /**
         * \brief        Advances the iterator to the next element
         * \warning      can't advance past the past the end value
         * \returns      the iter reference
         */
        ConstIter& operator++();

        /**
         * \brief         allows you to access the current element of the
         * iterator \warning       cannot be used on past the end iterator
         */
        const std::string& operator*() const;

        /**
         * \brief         checks if two iterators point to the same element
         * \warning       cannot be used on past the end iterator
         * \param         rhs the element to compare it to
         * \returns       whether or not they are equal
         */
        bool operator==(const ConstIter& rhs) const;

        /**
         * \brief         checks if two iterators point to the same element
         * \warning       cannot be used on past the end iterator
         * \param         rhs the element to compare it to
         * \returns       whether or not they are not equal
         */
        bool operator!=(const ConstIter& rhs) const;
    };
};

std::ostream& operator<<(std::ostream& os, const TreeStringSet& tree);

#endif  // TREESTRINGSET_HPP_INCLUDED
