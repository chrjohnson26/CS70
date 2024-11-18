#include <cs70/testinglogger.hpp>
// hashset.hpp is already included below
// Feel free to add more includes you need here

// Define a myhash function for any type that you want to hash here
// Make sure you define these functions *before* HashSet gets included

#include <string>
size_t myhash(const int& integer);
size_t myhash(const std::string& str);
#include "hashset.hpp"

size_t myhash(const std::string& str) {
    size_t hash = 0;
    size_t i = 0;

    while (i < str.length()) {
        hash += str[i++];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

size_t myhash(const int& integer) {
    size_t sum = integer + 3 * integer + 7 * integer;  // Adds values
    size_t hash = (sum % 20) + (sum % 3) + (sum % 5);  // jumble
    return hash;
}

///////////////////////////////////////////////////////////
//  TESTING
///////////////////////////////////////////////////////////

/** \brief This test checks the default constructor, which should make an
 *         empty list, and makes sure that various properties of empty lists
 *         are true.
 */
bool hashSetTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"01 empty hash (default constructor, info funcs)"};

    // Set up and run the tests.
    HashSet<int> myHash(10, 4);

    affirm_expected(myHash.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    affirm_expected(myHash.buckets(), 10);

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks the swap function which should switch all the
 * parameters of two hashs
 */
bool hashSetSwapTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"02 swap hash (default constructor, swap funcs)"};

    // Set up and run the tests.
    HashSet<int> myHash1(10, 50);
    HashSet<int> myHash2(12, 48);
    affirm_expected(myHash1.size(), 0);
    affirm_expected(myHash1.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    affirm_expected(myHash1.buckets(), 10);

    myHash1.swap(myHash2);

    affirm_expected(myHash2.buckets(), 10);

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks the insert and exists functions
 */
bool insertTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"03 insert hash (insert func, exist func)"};

    // Set up and run the tests.
    HashSet<int> myHash(10, 50);
    affirm_expected(myHash.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    myHash.insert(5);
    affirm_expected(myHash.size(), 1);

    // should still be size of 1 because 5 already exists in hash
    myHash.insert(5);
    affirm_expected(myHash.size(), 1);

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks the printToStream function to see if the
 * visualization of the hash is correct
 */
bool printTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"04 printToStream (visual output)"};

    // Set up and run the tests.
    HashSet<int> myHash1(10, 50);
    affirm_expected(myHash1.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    myHash1.insert(5);
    myHash1.insert(10);
    myHash1.insert(15);

    std::stringstream ss;
    ss << myHash1;
    affirm_expected(ss.str(),
                    "[0]\n[1]\n[2]10\n[3]\n[4]\n[5]15\n[6]5\n[7]\n[8]\n[9]\n");

    // test for commas between keys in one bucket
    HashSet<int> myHash2(10, 50);
    affirm_expected(myHash2.size(), 0);

    for (size_t i = 1; i < 11; ++i) {
        myHash2.insert(i);
    }
    std::stringstream ss2;
    ss2 << myHash2;
    affirm_expected(
        ss2.str(),
        "[0]4\n[1]7\n[2]10, 8\n[3]9\n[4]1\n[5]2\n[6]5, 3\n[7]6\n[8]\n[9]\n");

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks the rehash functions
 */
bool rehashTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{
        "05 rehash test (loadFactor, maxLoadFactor, rehash, reallocate)"};

    // Set up and run the tests.
    HashSet<int> myHash(10, 30);
    affirm_expected(myHash.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    for (size_t i = 1; i < 27; ++i) {
        myHash.insert(i);
    }
    // after inserting 26 elements the loadFactor count should be 2.6
    affirm_expected(myHash.loadFactor(), 2.6);

    // after setting the max load factor to 3 the function should return the new
    // max load factor
    // myHash.maxLoadFactor(3);
    // affirm_expected(myHash.getMaxLoad(), 3);

    for (size_t i = 1; i < 11; ++i) {
        myHash.insert(11 * i);
    }

    // after inserting 11 more elements the reallocation count should be 1
    affirm_expected(myHash.reallocations(), 1);

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief This test checks the collisions and maximal functions
 */
bool collisionsTest() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"06 collisions and maximal test (member variables)"};

    // Set up and run the tests.
    HashSet<int> myHash(1, 30);
    affirm_expected(myHash.size(), 0);
    // ^-- Reminder, affirm_expected compares the first argument to the
    // second one and fails if they don't match.

    for (size_t i = 1; i < 27; ++i) {
        myHash.insert(i);
    }

    // after inserting 26 elements the collision count should be 25 and the
    // longest bucket should be 26
    affirm_expected(myHash.collisions(), 25);
    affirm_expected(myHash.maximal(), 26);

    std::stringstream ss;
    ss.str("");
    myHash.showStatistics(ss);
    affirm_expected(
        ss.str(),
        "0 expansions, load factor 26, 25 collisions, longest run 26\n");

    // Print a short summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

int main() {
    // Initalize testing environment
    TestingLogger alltests{"All tests"};

    hashSetTest();
    hashSetSwapTest();
    insertTest();
    printTest();
    rehashTest();
    collisionsTest();

    if (alltests.summarize(true)) {
        return 0;  // Error code of 0 == Success!
    } else {
        return 2;  // Arbitrarily chosen exit code of 2 means tests failed.
    }
}
