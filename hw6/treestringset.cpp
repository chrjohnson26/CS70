/*
 * treestringset.cpp
 * Authors: Christian Johnson and Maddie Reeve
 * Implemenation of TreeStringSet and TreeStringSet::ConstIter.
 *
 * Part of CS70 Homework 6. This file may NOT be shared with anyone other
 * than the author(s) and the current semester's CS 70 staff without explicit
 * written permission from one of the CS 70 instructors.
 */

#include "treestringset.hpp"

#include <utility>
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <cstdlib>
#include <cassert>
#include <stack>
#include <algorithm>

// -----------------------------
// Implementation of TreeStringSet
// -----------------------------
TreeStringSet::TreeStringSet() : size_{0}, root_{nullptr} {
}

TreeStringSet::~TreeStringSet() {
    deleteSubtree(root_);
}

void TreeStringSet::deleteSubtree(Node* root) {
    // base case is that we are done, no more nodes to delete
    if (root == nullptr) {
        return;
    } else {
        // call delete on both sides of the root
        deleteSubtree(root->left_);
        deleteSubtree(root->right_);
        // delete the root
        delete root;
    }
}

size_t TreeStringSet::size() const {
    return size_;
}

bool TreeStringSet::exists(const std::string& str) const {
    return existsHelper(root_, str);
}

bool TreeStringSet::existsHelper(Node* root, const std::string& str) {
    if (root == nullptr) {
        // we have been through the tree and didn't find the key, return false
        return false;
    } else if (root->value_ == str) {
        // we have found the key so we can return true!
        return true;
    } else if (str < root->value_) {
        return existsHelper(root->left_, str);
    } else {
        return existsHelper(root->right_, str);
    }
}

// This code is based on the code from the CS 70 lesson materials
void TreeStringSet::insert(const std::string& str) {
    if (!exists(str)) {  // Don't insert keys already in the tree
        insertHelper(root_, str);
        ++size_;
    }
}

void TreeStringSet::insertHelper(Node*& tree, const std::string& str) {
    // if we are at a null pointer, we have reached the bottom, and can insert
    // our node
    if (tree == nullptr) {
        tree = new Node{str, nullptr, nullptr};
    } else if (str < tree->value_) {
        // need to move down left
        insertHelper(tree->left_, str);
    } else {
        // need to move down right
        insertHelper(tree->right_, str);
    }
}

std::ostream& TreeStringSet::printToStream(std::ostream& out) const {
    // display will recursively print out the tree
    display(root_, out);
    return out;
}

std::ostream& TreeStringSet::display(Node* root, std::ostream& out) {
    // follows the algorithm in the assignment guidelines
    if (root == nullptr) {
        out << "-";
    } else {
        out << "(";
        display(root->left_, out);
        out << ", ";
        out << root->value_;
        out << ", ";
        display(root->right_, out);
        out << ")";
    }
    return out;
}
std::ostream& operator<<(std::ostream& os, const TreeStringSet& tree) {
    // call our print to stream function
    tree.printToStream(os);
    return os;
}

bool TreeStringSet::operator==(const TreeStringSet& rhs) const {
    // we can use the std::equal function which takes 4 parameters, the start
    // and end of two iterators
    return std::equal(begin(), end(), rhs.begin(), rhs.end());
}

bool TreeStringSet::operator!=(const TreeStringSet& rhs) const {
    // using the operator== function we wrote above
    return !operator==(rhs);
}
double TreeStringSet::averageDepth() const {
    // an empty tree has average depth -1
    if (size_ == 0) {
        return -1;
    }
    // we wrote our depth helper to find the total sum of the depths, so we
    // divide by size() for the average depth
    return depthHelper(root_, 0) / size();
}

double TreeStringSet::depthHelper(Node* root, size_t count) {
    if (root == nullptr) {
        return 0;
    } else {
        // count reflects the current depth we are at, so we add it to the total
        // and increment it
        return count + depthHelper(root->left_, count + 1)
               + depthHelper(root->right_, count + 1);
    }
}

int TreeStringSet::height() const {
    return heightHelper(root_);
}

int TreeStringSet::heightHelper(Node* root) {
    // base case, we have counted all the nodes of the tree
    if (root == nullptr) {
        return -1;
    } else {
        // uses a use-or-lose it type of idea, to get the longest branch we take
        // the maximum
        return 1
               + std::max(heightHelper(root->left_),
                          heightHelper(root->right_));
    }
}

std::ostream& TreeStringSet::showStatistics(std::ostream& out) const {
    // outputs as specified in the assigmnent guidelines
    out << size();
    out << " nodes, height ";
    out << height();
    out << ", average depth ";
    out << averageDepth();
    out << std::endl;
    return out;
}

// iterator function implementations
TreeStringSet::ConstIter::ConstIter(Node* root) {
    pushToMinimum(root);
}
TreeStringSet::const_iterator TreeStringSet::begin() const {
    // the constructor calls push to min, so we can just use this
    return ConstIter(root_);
}

TreeStringSet::const_iterator TreeStringSet::end() const {
    return ConstIter(nullptr);
}

void TreeStringSet::ConstIter::pushToMinimum(Node* root) {
    // loop ends when we have reached a null ptr which will be the minimum
    while (root != nullptr) {
        stack_.push(root);
        // goes down the left branch of the tree
        root = root->left_;
    }
}

const std::string& TreeStringSet::ConstIter::operator*() const {
    return stack_.top()->value_;
}

TreeStringSet::ConstIter& TreeStringSet::ConstIter::operator++() {
    // save top node
    Node* oldtop = stack_.top();
    // pop the top node
    stack_.pop();
    // push to minimum with the next node
    pushToMinimum(oldtop->right_);
    return *this;
}

bool TreeStringSet::ConstIter::operator==(const ConstIter& rhs) const {
    // uses the stack's equals
    return (stack_ == rhs.stack_);
}

bool TreeStringSet::ConstIter::operator!=(const ConstIter& rhs) const {
    // uses our equals funcion we wrote above
    return !(*this == rhs);
}
