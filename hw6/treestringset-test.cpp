#include <cs70/testinglogger.hpp>
#include "treestringset.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cstddef>
#include <cstdlib>
#include <cassert>

// Tests for part 2
bool part02Test() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"Tests the constructor and size methods"};
    // Set up and run the tests.

    TreeStringSet myTree;

    affirm_expected(myTree.size(), 0);
    return log.summarize();
}

// Tests for part 3
bool part03Test() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"Tests the insert and exists methods"};
    // Set up and run the tests.

    TreeStringSet myTree;
    affirm_expected(myTree.size(), 0);
    myTree.insert("C");
    myTree.insert("D");
    myTree.insert("B");
    myTree.insert("A");
    affirm_expected(myTree.size(), 4);
    affirm(myTree.exists("A"));
    myTree.insert("D");
    affirm_expected(myTree.size(), 4);
    affirm(!myTree.exists("M"));
    return log.summarize();
}

// Tests for part 4
bool part04Test() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"Tests the printToStream and << operator functions"};
    // Set up and run the tests.

    TreeStringSet myTree;
    myTree.insert("G");
    myTree.insert("D");
    myTree.insert("J");
    myTree.insert("E");
    std::stringstream ss;
    ss << myTree;
    affirm_expected(ss.str(), "((-, D, (-, E, -)), G, (-, J, -))");
    return log.summarize();
}

// Tests for part 5
bool part05Test() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"Tests the iterator functions"};
    // Set up and run the tests.

    TreeStringSet myTree;
    myTree.insert("G");
    myTree.insert("D");
    myTree.insert("J");
    myTree.insert("E");

    affirm_expected(*myTree.begin(), "D");
    affirm_expected(*(++myTree.begin()), "E");
    affirm(myTree.begin() != myTree.end());
    return log.summarize();
}

// Tests for part 6
bool part06Test() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"Tests the tree equals"};
    // Set up and run the tests.

    TreeStringSet myTree;
    myTree.insert("G");
    myTree.insert("D");
    myTree.insert("J");
    myTree.insert("E");
    TreeStringSet myTree2;
    myTree2.insert("G");
    myTree2.insert("D");
    myTree2.insert("J");
    myTree2.insert("E");
    affirm(myTree == myTree2);
    myTree2.insert("A");
    affirm(myTree != myTree2);
    myTree.insert("B");
    affirm(myTree != myTree2);
    return log.summarize();
}

// Tests for part 7
bool part07Test() {
    // Set up the TestingLogger object, giving a suitable description
    TestingLogger log{"Tests the statistics"};
    // Set up and run the tests.

    TreeStringSet myTree;
    myTree.insert("G");
    myTree.insert("D");
    myTree.insert("J");
    myTree.insert("E");
    myTree.insert("B");
    myTree.insert("A");
    myTree.insert("C");
    myTree.insert("H");
    myTree.insert("L");
    std::stringstream ss;
    myTree.showStatistics(ss);
    affirm_expected(ss.str(), "9 nodes, height 3, average depth 1.77778\n");
    return log.summarize();
}

int main(int, char**) {
    TestingLogger alltests{"all tests"};

    // include all of our tests
    part02Test();
    part03Test();
    part04Test();
    part05Test();
    part06Test();
    part07Test();
    if (alltests.summarize(true)) {
        return 0;  // Error code of 0 == Success!
    } else {
        return 2;  // Arbitrarily chosen exit code of 2 means tests failed.
    }
}
