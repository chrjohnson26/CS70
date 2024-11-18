/**
 * intlist-test.cpp
 * CS 70 Starter Code
 * Unit tests the IntList class.
 *
 * Part of CS70 Homework 5. This file may NOT be shared with anyone other
 * than the author(s) and the current semester's CS 70 staff without explicit
 * written permission from one of the CS 70 instructors.
 */

#include "intlist.hpp"

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

///////////////////////////////////////////////////////////
//  TESTING
///////////////////////////////////////////////////////////

// PHASE 1 TESTS -------------------------------------------------

/** \brief This test checks the default constructor, which should make an
 *         empty list, and makes sure that various properties of empty lists
 *         are true.
 */
bool emptyListTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"01 empty list (default constructor, info funcs)"};

    // Set up and run the tests.
    IntList myList;

    affirm_expected(myList.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    affirm(myList.empty());
    // ^-- affirm fails if the argument doesn't evaluate to true.

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

////////////////////////////////////////////
// Following the above model, add more tests
////////////////////////////////////////////

// PHASE 2 TESTS -------------------------------------------------
bool push_frontTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"Push front test"};

    // Set up and run the tests.
    IntList myList;

    myList.push_front(14);
    affirm_expected(myList.size(), 1);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    affirm(!myList.empty());
    // ^-- affirm fails if the argument doesn't evaluate to true.

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.

    for (size_t i = 0; i < 100; ++i) {
        myList.push_front(i);
    }

    affirm_expected(myList.size(), 101);
    affirm(!myList.empty());
    return log.summarize();
}

bool pop_frontTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"Pop front test"};

    // Set up and run the tests.
    IntList myList;
    myList.push_front(14);
    affirm_expected(myList.size(), 1);
    myList.pop_front();

    affirm_expected(myList.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    affirm(myList.empty());
    // ^-- affirm fails if the argument doesn't evaluate to true.

    for (size_t i = 0; i < 100; ++i) {
        myList.push_front(i);
    }
    for (size_t i = 0; i < 90; ++i) {
        myList.pop_front();
    }
    affirm_expected(myList.size(), 10);
    affirm(!myList.empty());
    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}
// PHASE 3 TESTS -------------------------------------------------
bool iterator_Test() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"Testing iterator functionality"};

    // Set up and run the tests.
    IntList myList;
    // checking that begin() and end() are the same if empty
    affirm_expected(myList.begin(), myList.end());
    for (size_t i = 0; i < 100; ++i) {
        myList.push_front(i);
    }

    int j = 99;
    for (auto i = myList.begin(); i != myList.end(); ++i) {
        // checking that the value the iterator points to is i
        // we do this since we made our list full of 0-99, in reverse order
        affirm_expected(*i, j);
        j--;
    }

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

// PHASE 4 TESTS -------------------------------------------------
bool equal_Test() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"Testing equal and not equal for intList"};

    // Set up and run the tests.
    IntList myList1;
    IntList myList2;

    // Checks if the two empty lists are equivalent
    affirm(myList1 == myList2);

    for (size_t i = 0; i < 100; ++i) {
        myList1.push_front(i);
        myList2.push_front(i);
    }
    // we pushed the same thing, the lists should be equal
    affirm(myList1 == myList2);

    myList2.pop_front();
    // once we pop from myList2, they should no longer be equal
    affirm(myList1 != myList2);
    // the lists should no longer be equal since we removed a node from one

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

// PHASE 5 TESTS -------------------------------------------------
bool pushBackTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"Testing push back functionality"};

    // Set up and run the tests.
    IntList myList;

    myList.push_front(0);
    for (size_t i = 1; i < 100; ++i) {
        myList.push_back(i);
    }

    int j = 0;
    for (auto i = myList.begin(); i != myList.end(); ++i) {
        // checking that the value the iterator points to is i
        // we do this since we made our list full of 0-99
        affirm_expected(*i, j);
        j++;
    }

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}
bool insertAfterTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"Testing instert after functionality"};

    // Set up and run the tests.
    IntList myList;

    myList.push_front(0);
    for (size_t i = 1; i < 10; ++i) {
        myList.push_back(i);
    }
    auto location = myList.begin();
    ++location;
    ++location;

    myList.insert_after(location, 14);
    // the value at the location iterator should still be 2
    affirm_expected(*location, 2);
    // the value at the location after the iterator should be 14, which we just
    // added
    affirm_expected(*(++location), 14);
    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

// PHASE 6 TESTS -------------------------------------------------
bool copyConstructorTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"Copy constructor test"};

    // Set up and run the tests.
    IntList myList;
    for (size_t i = 0; i < 10; ++i) {
        myList.push_back(i);
    }
    // the copy constructor
    IntList newList = myList;
    // the copy constructor should make two equal lists
    affirm(newList == myList);
    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/*
 * Test the IntList!
 */
int main(int, char**) {
    TestingLogger alltests{"all tests"};
    // try all of our tests
    emptyListTest();
    push_frontTest();
    pop_frontTest();
    iterator_Test();
    equal_Test();
    pushBackTest();
    insertAfterTest();
    copyConstructorTest();
    // Print a summary of the all the affirmations and exit the program.

    if (alltests.summarize(true)) {
        return 0;  // Error code of 0 == Success!
    } else {
        return 2;  // Arbitrarily chosen exit code of 2 means tests failed.
    }
}
