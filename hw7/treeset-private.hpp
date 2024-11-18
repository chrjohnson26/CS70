/*
 * treestringset.cpp
 * Authors: Sheridan and Olivia
 * Implemenation of TreeStringSet and TreeStringSet::ConstIter.
 *
 * Part of CS70 Homework 6. This file may NOT be shared with anyone other
 * than the author(s) and the current semester's CS 70 staff without explicit
 * written permission from one of the CS 70 instructors.
 */

#include <utility>
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <cstdlib>
#include <cassert>
#include <string>
#include <stack>
#include <algorithm>

// -------------------------
// Implementation of TreeSet<T>
// -------------------------

template <typename T>
std::ostream& operator<<(std::ostream& os, const TreeSet<T>& t) {
    t.printToStream(os);

    // To allow chaining of <<, we always return the stream we were given.
    return os;
}

template <typename T>
TreeSet<T>::TreeSet() : style_{LEAF} {
    // nothing here! everything is already initialized
}

template <typename T>
TreeSet<T>::TreeSet(bst_style style) : style_{style} {
    // nothing here
}

template <typename T>
TreeSet<T>::TreeSet(bst_style style, size_t seed)
    : style_{style}, seed_{seed}, rand_{RandUInt32{seed}} {
    // nothing here! everything is already initialized
}

template <typename T>
TreeSet<T>::~TreeSet() {
    // calls recursive helper function
    destructorHelper(root_);
}

template <typename T>
void TreeSet<T>::destructorHelper(Node* root) {
    // base case null root
    if (root == nullptr) {
        return;
    } else {
        // destroys left tree recursively
        destructorHelper(root->left_);
        // destroys right tree recursively
        destructorHelper(root->right_);
        delete root;
    }
}

template <typename T>
size_t TreeSet<T>::size() const {
    // check for empty tree
    if (root_ == nullptr) {
        return 0;
    }
    return root_->size_;
}

template <typename T>
size_t TreeSet<T>::nodeSize(const Node* root) {
    // check if the node has any children
    if (root == nullptr) {
        return 0;
    } else {
        return root->size_;
    }
}

template <typename T>
void TreeSet<T>::insert(const T& item) {
    // we do not insert an item if it already exists
    if (exists(item)) {
        return;
    } else if (style_ == LEAF) {
        // calls recursive leaf helper function
        insertLeafHelper(root_, item);
    } else if (style_ == ROOT) {
        // calls recursive root helper function
        insertRootHelper(root_, item);
    } else if (style_ == RANDOMIZED) {
        // calls recursive random helper function
        insertRandomHelper(root_, item);
    }
}

template <typename T>
void TreeSet<T>::insertLeafHelper(Node*& root, const T& item) {
    // creates new node
    if (root == nullptr) {
        root = new Node{item};
    } else if (item < root->value_) {
        // recursively inserts item somewhere in left tree
        insertLeafHelper(root->left_, item);
        ++root->size_;
    } else {
        // recursively inserts item somewhere in right tree
        insertLeafHelper(root->right_, item);
        ++root->size_;
    }
}

template <typename T>
void TreeSet<T>::insertRootHelper(Node*& root, const T& item) {
    // creates new node
    if (root == nullptr) {
        root = new Node{item};
    } else if (item < root->value_) {
        // recursively inserts item somewhere in left tree
        insertLeafHelper(root->left_, item);
        ++root->size_;
    } else {
        // recursively inserts item somewhere in right tree
        insertLeafHelper(root->right_, item);
        ++root->size_;
    }
}

template <typename T>
void TreeSet<T>::insertRandomHelper(Node*& root, const T& item) {
    int randomInt = rand_.get(nodeSize(root) + 1);
    // generates random number to see where to insert item
    bool doRootInsert = (randomInt == 0);
    if (doRootInsert) {
        // insert at root
        insertRootHelper(root, item);
    } else if (root == nullptr) {
        // don't go past the end of the tree
        root = new Node{item};
    } else if (item < root->value_) {
        // recursively inserts item somewhere in left tree
        insertRandomHelper(root->left_, item);
        ++root->size_;
    } else {
        // recursively inserts item somewhere in right tree
        insertRandomHelper(root->right_, item);
        ++root->size_;
    }
}

template <typename T>
void TreeSet<T>::rotateRight(Node*& top) {
    // adapted from code provided in CS 70, Week 10, Lesson 2
    Node* d = top;
    Node* b = top->left_;

    // Make a copy of the Node* to give a name that matches the diagram.
    Node* C = b->right_;

    // Change d's left child to be C
    d->left_ = C;
    // Change b's right child to be d
    b->right_ = d;

    // adjust node sizes
    b->size_ = nodeSize(d);
    d->size_ -= 1 + nodeSize(b->left_);

    // Make b the new top.
    top = b;
}

template <typename T>
void TreeSet<T>::rotateLeft(Node*& top) {
    Node* d = top;
    Node* b = top->right_;

    // Make a copy of the Node* to give a name that matches the diagram.
    Node* C = b->left_;

    // Change d's right child to be C
    d->right_ = C;
    // Change b's left child to be d
    b->left_ = d;

    // adjust node sizes
    d->size = nodeSize(b);
    b->size_ -= 1 + nodeSize(b->left_);

    // Make b the new top.
    top = b;
}

template <typename T>
bool TreeSet<T>::exists(const T& item) const {
    // calls recursive helper function
    return existsHelper(root_, item);
}

template <typename T>
bool TreeSet<T>::existsHelper(Node* root, const T& item) {
    // base case null root
    if (root == nullptr) {
        return false;
    } else if (root->value_ == item) {
        return true;
    } else if (item < root->value_) {
        // recursive call to left tree
        return existsHelper(root->left_, item);
    } else {
        // recursive call to right tree
        return existsHelper(root->right_, item);
    }
}

template <typename T>
int TreeSet<T>::height() const {
    return heightHelper(root_);
}

template <typename T>
int TreeSet<T>::heightHelper(Node* root) {
    if (root == nullptr) {
        // empty tree has height of -1 by definition
        return -1;
    }
    // finds highest depth of tree
    return 1 + std::max(heightHelper(root->left_), heightHelper(root->right_));
}

template <typename T>
double TreeSet<T>::averageDepth() const {
    if (size() == 0) {
        return -1;
    } else {
        // calls recursive helper function
        return depthHelper(root_, 0) / size();
    }
}

template <typename T>
double TreeSet<T>::depthHelper(Node* root, int count) {
    if (root == nullptr) {
        return 0;
    } else {
        // adds depth from both trees
        return count + depthHelper(root->left_, count + 1)
               + depthHelper(root->right_, count + 1);
    }
}

template <typename T>
bool TreeSet<T>::operator==(const TreeSet<T>& rhs) const {
    // compares beginning iterator and past the end iterator for both trees
    return std::equal(begin(), end(), rhs.begin(), rhs.end());
}

template <typename T>
bool TreeSet<T>::operator!=(const TreeSet<T>& rhs) const {
    // Idiomatic code: leverage == to implement !=
    return !(*this == rhs);
}

template <typename T>
std::ostream& TreeSet<T>::printToStream(std::ostream& outStream) const {
    return displayHelper(root_, outStream);
}

template <typename T>
std::ostream& TreeSet<T>::printSizesToStream(std::ostream& outStream) const {
    displaySizeHelper(root_, outStream);
}

template <typename T>
std::ostream& TreeSet<T>::displaySizeHelper(Node* root,
                                            std::ostream& outStream) {
    if (root == nullptr) {
        // print a dash if no node
        outStream << "0";
    } else {
        outStream << "(";
        // recursive call to left subtree
        displaySizeHelper(root->left_, outStream);
        outStream << ", ";
        outStream << nodeSize(root);
        outStream << ", ";
        // recursive call to right subtree
        displayHelper(root->right_, outStream);
        outStream << ")";
    }
}

template <typename T>
std::ostream& TreeSet<T>::displayHelper(Node* root, std::ostream& outStream) {
    if (root == nullptr) {
        // print a dash if no node
        outStream << "-";
    } else {
        outStream << "(";
        // recursive call to left subtree
        displayHelper(root->left_, outStream);
        outStream << ", ";
        outStream << root->value_;
        outStream << ", ";
        // recursive call to right subtree
        displayHelper(root->right_, outStream);
        outStream << ")";
    }
    return outStream;
}

template <typename T>
std::ostream& TreeSet<T>::showStatistics(std::ostream& outStream) const {
    outStream << size();
    outStream << " nodes, height ";
    outStream << height();
    outStream << ", average depth ";
    outStream << averageDepth();
    return outStream;
}

template <typename T>
typename TreeSet<T>::ConstIter TreeSet<T>::begin() const {
    return ConstIter{root_};
}

template <typename T>
typename TreeSet<T>::ConstIter TreeSet<T>::end() const {
    return ConstIter{};
}

// -----------------------------------
// Implementation of TreeSet<T>::ConstIter
// -----------------------------------

template <typename T>
TreeSet<T>::ConstIter::ConstIter(Node* root) {
    pushToMinimum(root);
}

template <typename T>
typename TreeSet<T>::ConstIter& TreeSet<T>::ConstIter::operator++() {
    // saves old top
    Node* oldtop = stack_.top();
    // removes old top
    stack_.pop();
    // calls push to minimum on right children of the old top
    pushToMinimum(oldtop->right_);
    return *this;
}

template <typename T>
typename TreeSet<T>::ConstIter::reference TreeSet<T>::ConstIter::operator*()
    const {
    return stack_.top()->value_;
}

template <typename T>
bool TreeSet<T>::ConstIter::operator==(const ConstIter& rhs) const {
    return stack_ == rhs.stack_;
}

template <typename T>
bool TreeSet<T>::ConstIter::operator!=(const ConstIter& rhs) const {
    // Idiomatic code: leverage == to implement !=
    return !(*this == rhs);
}

template <typename T>
void TreeSet<T>::ConstIter::pushToMinimum(Node* root) {
    // checks if no children
    if (root == nullptr) {
        return;
    }
    // pushes node onto stack
    stack_.push(root);
    // calls push to minimum on left subtree
    pushToMinimum(root->left_);
}
