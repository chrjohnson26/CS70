/**
 * treestringset-test.cpp
 * CS 70 Starter Code
 * Unit tests the TreeStringSet class.
 *
 * Part of CS70 Homework 6. This file may NOT be shared with anyone other
 * than the author(s) and the current semester's CS 70 staff without explicit
 * written permission from one of the CS 70 instructors.
 */

#include "treeset.hpp"

#include <cs70/testinglogger.hpp>

#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstddef>
#include <cstdlib>
#include <cassert>
#include <stack>
#include <algorithm>

///////////////////////////////////////////////////////////
//  TESTING
///////////////////////////////////////////////////////////

/** \brief This test checks the default constructor, which should make an
 *         empty list, and makes sure that various properties of empty lists
 *         are true.
 */
bool treeSetTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"01 empty tree (default constructor, info funcs)"};

    // Set up and run the tests.
    TreeSet<std::string> myTree;

    affirm_expected(myTree.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks the size function, which should return the
 * size of the tree.
 */
bool sizeTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"02 size (default constructor, info funcs)"};

    // Set up and run the tests.
    TreeSet<std::string> myTree;

    affirm_expected(myTree.size(), 0);

    /*for (size_t i = 0; i < 10; i++) {
        myTree.insert("test");
        affirm_expected(myTree.size(), i + 1);
    }
    */
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks the insert and exists functions, which should add an
 * item to the tree, and makes sure that the tree has it
 */
bool insertExistsTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"03 tree insert (default constructor, insert func)"};

    // Set up and run the tests.
    TreeSet<std::string> myTree;

    affirm_expected(myTree.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    for (size_t i = 0; i < 10; ++i) {
        myTree.insert(std::to_string(i));
        affirm_expected(myTree.size(), (i + 1));
        affirm(myTree.exists(std::to_string(i)));
    }

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks the printToStream function and the << operator
 * function, which should print the tree
 */
bool printToStreamTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"04 printToStream (operator<<, member func)"};

    // Set up and run the tests.
    TreeSet<std::string> myTree;

    affirm_expected(myTree.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    for (size_t i = 0; i < 5; ++i) {
        myTree.insert(std::to_string(i));
    }

    std::stringstream ss;
    ss << myTree;
    affirm_expected(ss.str(), "(-, 0, (-, 1, (-, 2, (-, 3, (-, 4, -)))))");

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks the iterator, which should iterate through the tree
 */
bool iteratorTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"05 iterator (begin, end)"};

    // Set up and run the tests.
    TreeSet<std::string> myTree;

    affirm_expected(myTree.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    for (size_t i = 0; i < 10; ++i) {
        myTree.insert(std::to_string(i));
        affirm_expected(myTree.size(), (i + 1));
        affirm(myTree.exists(std::to_string(i)));
    }

    int count = 0;
    for (auto iter = myTree.begin(); iter != myTree.end(); ++iter) {
        affirm_expected(*iter, std::to_string(count));
        ++count;
    }

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks the operator == function, which should return
 * equality of iterators
 */
bool operatorTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"06 operators (==, !=)"};

    // Set up and run the tests.
    TreeSet<std::string> myTree;

    affirm_expected(myTree.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    for (size_t i = 0; i < 10; ++i) {
        myTree.insert(std::to_string(i));
    }

    TreeSet<std::string>::const_iterator iter1 = myTree.begin();
    TreeSet<std::string>::const_iterator iter2 = myTree.begin();

    affirm(iter1 == iter2);

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks the operator == function, which should return
 * equality of trees
 */
bool operatorTreeTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"07 tree operators (==, !=)"};

    // Set up and run the tests.
    TreeSet<std::string> myTree;
    TreeSet<std::string> myTree2;

    affirm_expected(myTree.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    for (size_t i = 0; i < 10; ++i) {
        myTree.insert(std::to_string(i));
        myTree2.insert(std::to_string(i));
    }

    affirm_expected(myTree, myTree2);

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks the operator == function, which should return
 * equality of trees
 */
bool statsTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"08 showStatistics (avg depth, height, visuals)"};

    // Set up and run the tests.
    TreeSet<std::string> myTree;

    affirm_expected(myTree.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    std::stringstream ss;
    ss.str("");

    for (size_t i = 0; i < 10; ++i) {
        myTree.insert(std::to_string(i));
    }

    myTree.showStatistics(ss);

    affirm_expected(ss.str(), "10 nodes, height 9, average depth 4.5");

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks that tree set works on doubles
 */
bool doubleTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"09 <double> (TreeSet, input)"};

    // Set up and run the tests.
    TreeSet<double> myTree(LEAF);

    affirm_expected(myTree.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks that tree set works on ints
 */
bool intTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"10 <int> (TreeSet, input)"};

    // Set up and run the tests.
    TreeSet<int> myTree;

    affirm_expected(myTree.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks that the root tree set insertion works
 */
bool rootInsertTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"11 ROOT TreeSet insert"};

    // Set up and run the tests.
    TreeSet<std::string> myTree(ROOT);

    affirm_expected(myTree.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    TreeSet<std::string> myLeafTree(LEAF);

    for (size_t i = 1; i < 10; ++i) {
        myLeafTree.insert(std::to_string(i));
        affirm_expected(myLeafTree.size(), (i));
        affirm(myLeafTree.exists(std::to_string(i)));
    }

    for (size_t j = 9; j > 0; --j) {
        myTree.insert(std::to_string(j));
        affirm_expected(myTree.size(), (10 - j));
        affirm(myTree.exists(std::to_string(j)));
    }

    std::stringstream ss;
    ss.str("");
    std::stringstream ss2;
    ss2.str("");

    myTree.showStatistics(ss);
    myTree.showStatistics(ss2);

    affirm_expected(ss.str(), ss2.str());

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks the size function on a ROOT tree, which should
 * return the size of the tree.
 */
bool rootSizeTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"12 ROOT TreeSet size"};

    // Set up and run the tests.
    TreeSet<std::string> myTree(ROOT);

    affirm_expected(myTree.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/*
 * Test the TreeSet!
 */
int main(int, char**) {
    TestingLogger alltests{"all tests"};

    treeSetTest();
    sizeTest();
    insertExistsTest();
    printToStreamTest();
    iteratorTest();
    operatorTest();
    operatorTreeTest();
    statsTest();
    doubleTest();
    intTest();
    rootInsertTest();
    rootSizeTest();

    // Print a summary of the all the affirmations and exit the program.

    if (alltests.summarize(true)) {
        return 0;  // Error code of 0 == Success!
    } else {
        return 2;  // Arbitrarily chosen exit code of 2 means tests failed.
    }
}
