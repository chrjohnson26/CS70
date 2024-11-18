/*
   testtrain.cpp

   Part of CS70 Homework 4. This file may NOT be shared with anyone
   other than the author(s) and the current semester's CS70 staff
   without explicit written permission from one of the CS70 instructors.

   This program uses the CS 70 Tesing Library, which is documented here:

       https://www.cs.hmc.edu/cs70/sakai/Help_Pages_The_CS_70_Testing_Library

   It must be linked with:

       -ltestinglogger
 */

#include "car.hpp"
#include "train.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <cs70/testinglogger.hpp>

///////////////////////////
// Car Testing Functions //
///////////////////////////

// Expected output: no output, just don't cause memory errors
bool testDeclareCar() {
    TestingLogger log("01 test declare car");

    Car c;  // Constuct an empty train car

    // Also, test jnformational functions
    affirm(c.isEmpty());
    affirm(!c.isFull());
    affirm_expected(c.getUsage(), 0);

    return log.summarize();
}  // Destructor should be called here

// Expected output: [_][_][_][_]~
bool testOutputEmptyCar() {
    TestingLogger log("02 test output empty car");

    Car c;
    std::stringstream ss;
    ss << c;
    affirm_expected(ss.str(), "[_][_][_][_]~");

    return log.summarize();
}

// Expected output: no output, just don't cause memory errors
bool testAddPackage_1() {
    TestingLogger log("03 test add package #1");

    Car c;
    c.addPackage();

    affirm(!c.isEmpty());
    affirm(!c.isFull());
    affirm_expected(c.getUsage(), 1);

    return log.summarize();
}

// Expected output: no output, just don't cause memory errors
bool testAddPackage_2() {
    TestingLogger log("04 test add package #2");

    Car c;
    c.addPackage();
    c.addPackage();

    affirm(!c.isEmpty());
    affirm(!c.isFull());
    affirm_expected(c.getUsage(), 2);

    return log.summarize();
}

// Expected output: no output, just don't cause memory errors
bool testAddPackage_3() {
    TestingLogger log("05 test add package #3");

    Car c;
    c.addPackage();
    c.addPackage();
    c.addPackage();

    affirm(!c.isEmpty());
    affirm(!c.isFull());
    affirm_expected(c.getUsage(), 3);

    return log.summarize();
}

// Expected output: no output, just don't cause memory errors
bool testAddPackage_4() {
    TestingLogger log("06 test add package #4");

    Car c;
    c.addPackage();
    c.addPackage();
    c.addPackage();
    c.addPackage();

    affirm(!c.isEmpty());
    affirm(c.isFull());
    affirm_expected(c.getUsage(), 4);

    return log.summarize();
}

// Expected output: [x][_][_][_]~
bool testAddPackageAndOutput_1() {
    TestingLogger log("07 test add package and output #1");

    Car c;
    c.addPackage();

    std::stringstream ss;
    ss << c;
    affirm_expected(ss.str(), "[x][_][_][_]~");

    return log.summarize();
}

// Expected output: [x][x][_][_]~
bool testAddPackageAndOutput_2() {
    TestingLogger log("08 test add package and output #2");

    Car c;
    c.addPackage();
    c.addPackage();

    std::stringstream ss;
    ss << c;
    affirm_expected(ss.str(), "[x][x][_][_]~");

    return log.summarize();
}

// Expected output: [x][x][x][x]~
bool testAddPackageAndOutput_4() {
    TestingLogger log("09 test add package and output #4");

    Car c;
    c.addPackage();
    c.addPackage();
    c.addPackage();
    c.addPackage();

    std::stringstream ss;
    ss << c;
    affirm_expected(ss.str(), "[x][x][x][x]~");

    return log.summarize();
}

// Expected output: [_][_][_][_]~
bool testAddRemovePackages_1() {
    TestingLogger log("10 test add remove packages #1");

    Car c;
    c.addPackage();
    c.removePackage();

    std::stringstream ss;
    ss << c;
    affirm_expected(ss.str(), "[_][_][_][_]~");

    return log.summarize();
}

// Expected output: [x][_][_][_]~
bool testAddRemovePackages_2() {
    TestingLogger log("11 test add remove packages #2");

    Car c;
    c.addPackage();
    c.addPackage();
    c.removePackage();

    std::stringstream ss;
    ss << c;
    affirm_expected(ss.str(), "[x][_][_][_]~");

    return log.summarize();
}

// Expected output: [_][_][_][_]~
bool testAddRemovePackages_3() {
    TestingLogger log("12 test add remove packages #3");

    Car c;
    c.addPackage();
    c.addPackage();
    c.removePackage();
    c.removePackage();

    std::stringstream ss;
    ss << c;
    affirm_expected(ss.str(), "[_][_][_][_]~");

    return log.summarize();
}

// Expected output: [x][x][_][_]~
bool testAddRemovePackages_4() {
    TestingLogger log("13 test add remove packages #4");

    Car c;
    c.addPackage();
    c.removePackage();
    c.addPackage();
    c.addPackage();
    c.removePackage();
    c.addPackage();

    std::stringstream ss;
    ss << c;
    affirm_expected(ss.str(), "[x][x][_][_]~");

    return log.summarize();
}

// Expected output: progressive filling up and removing
bool testAddRemovePackages_5() {
    TestingLogger log("14 test add remove packages #5");

    const char* expected_outputs[] = {
        "[_][_][_][_]~", "[x][_][_][_]~", "[x][x][_][_]~",
        "[x][x][x][_]~", "[x][x][x][x]~", "[x][x][x][_]~",
        "[x][x][_][_]~", "[x][_][_][_]~", "[_][_][_][_]~"};

    Car c;
    size_t out = 0;
    std::stringstream ss;
    for (size_t i = 0; i < Car::CAPACITY; ++i) {
        ss << c;
        affirm_expected(ss.str(), expected_outputs[out++]);
        ss.str("");  // Reset the stringstream.
        c.addPackage();
    }

    for (size_t i = 0; i < Car::CAPACITY; ++i) {
        ss << c;
        affirm_expected(ss.str(), expected_outputs[out++]);
        ss.str("");  // Reset the stringstream.
        c.removePackage();
    }

    ss << c;
    affirm_expected(ss.str(), expected_outputs[out++]);

    return log.summarize();
}

/////////////////////////////
// Train Testing Functions //
/////////////////////////////

// Expected output: no output, just don't cause memory errors
bool testCreateTrain() {
    TestingLogger log("15 test create train");

    Train t(BASIC);  // constructor called here

    return log.summarize();
}  // destructor called here

// Expected output: (0, 0) [_][_][_][_]~
bool testOutputTrain_01() {
    TestingLogger log("16 test output train #1");

    Train t(BASIC);

    std::stringstream ss;
    ss << t;
    affirm_expected(ss.str(), "(0, 0) [_][_][_][_]~");

    return log.summarize();
}

// Expected output: (0, 0) [_][_][_][_]~
bool testOutputTrain_02() {
    TestingLogger log("17 test output train #2");

    Train t(SMART);
    std::stringstream ss;
    ss << t;
    affirm_expected(ss.str(), "(0, 0) [_][_][_][_]~");

    return log.summarize();
}

// Expected output: (4, 1) [x][_][_][_]~
bool testTrainAddAndOutput_01() {
    TestingLogger log("18 test train add and output #1");

    Train t(BASIC);
    t.addPackage();

    std::stringstream ss;
    ss << t;
    affirm_expected(ss.str(), "(4, 1) [x][_][_][_]~");

    return log.summarize();
}

// Expected output: (8, 2) [x][x][_][_]~
bool testTrainAddAndOutput_02() {
    TestingLogger log("19 test train add and output #2");

    Train t(BASIC);
    t.addPackage();
    t.addPackage();

    std::stringstream ss;
    ss << t;
    affirm_expected(ss.str(), "(8, 2) [x][x][_][_]~");

    return log.summarize();
}

// Expected output: (12, 3) [x][x][x][_]~
bool testTrainAddAndOutput_03() {
    TestingLogger log("20 test train add and output #3");

    Train t(BASIC);
    t.addPackage();
    t.addPackage();
    t.addPackage();

    std::stringstream ss;
    ss << t;
    affirm_expected(ss.str(), "(12, 3) [x][x][x][_]~");

    return log.summarize();
}

// Expected output:
// (4, 1) [x][_][_][_]~
// (4, 1) [_][_][_][_]~
bool testTrainAddRemoveAndOutput_01() {
    TestingLogger log("21 test train add remove and output #1");

    Train t(BASIC);
    t.addPackage();

    std::stringstream ss;
    ss << t;
    affirm_expected(ss.str(), "(4, 1) [x][_][_][_]~");
    ss.str("");  // Reset the stringstream

    t.removePackage();

    ss << t;
    affirm_expected(ss.str(), "(4, 1) [_][_][_][_]~");

    return log.summarize();
}

// Expected output:
// (4, 1) [x][_][_][_]~
// (8, 2) [x][x][_][_]~
// (8, 2) [x][_][_][_]~
// (8, 2) [_][_][_][_]~
bool testTrainAddRemoveAndOutput_02() {
    TestingLogger log("22 test train add remove and output #2");

    Train t(BASIC);
    t.addPackage();

    std::stringstream ss;
    ss << t;

    affirm_expected(ss.str(), "(4, 1) [x][_][_][_]~");
    ss.str("");  // Reset the stringstream

    t.addPackage();

    ss << t;
    affirm_expected(ss.str(), "(8, 2) [x][x][_][_]~");
    ss.str("");  // Reset the stringstream

    t.removePackage();

    ss << t;
    affirm_expected(ss.str(), "(8, 2) [x][_][_][_]~");
    ss.str("");  // Reset the stringstream

    t.removePackage();

    ss << t;
    affirm_expected(ss.str(), "(8, 2) [_][_][_][_]~");

    return log.summarize();
}

// Expected output:
// (12, 3) [x][x][x][_]~
// (12, 3) [x][x][_][_]~
// (16, 4) [x][x][x][_]~
bool testTrainAddRemoveAndOutput_03() {
    TestingLogger log("23 test train add remove and output #3");

    Train t(BASIC);
    t.addPackage();
    t.addPackage();
    t.addPackage();

    std::stringstream ss;
    ss << t;
    affirm_expected(ss.str(), "(12, 3) [x][x][x][_]~");
    ss.str("");  // Reset the stringstream

    t.removePackage();

    ss << t;
    affirm_expected(ss.str(), "(12, 3) [x][x][_][_]~");
    ss.str("");  // Reset the stringstream

    t.addPackage();

    ss << t;
    affirm_expected(ss.str(), "(16, 4) [x][x][x][_]~");

    return log.summarize();
}

// Expected output: (28, 11) [x][x][x][x]~[x][x][x][_]~
bool testBasicUpsize_01() {
    TestingLogger log("24 test basic upsize #1");

    Train t(BASIC);

    for (size_t i = 0; i < 7; ++i) {
        t.addPackage();
    }

    std::stringstream ss;
    ss << t;
    affirm_expected(ss.str(), "(28, 11) [x][x][x][x]~[x][x][x][_]~");

    return log.summarize();
}

// Expected output: (68, 57) [x][x][x][x]~(x4)[x][_][_][_]~
bool testBasicUpsize_02() {
    TestingLogger log("25 test basic upsize #2");

    Train t(BASIC);
    for (size_t i = 0; i < 17; ++i) {
        t.addPackage();
    }

    std::stringstream ss;
    ss << t;
    affirm_expected(ss.str(),
                    "(68, 57) [x][x][x][x]~[x][x][x][x]~"
                    "[x][x][x][x]~[x][x][x][x]~[x][_][_][_]~");

    return log.summarize();
}

// Expected output: (28, 11) [x][x][x][x]~[x][x][x][_]~
bool testSmartUpsize_01() {
    TestingLogger log("26 test smart upsize #1");

    Train t(SMART);
    for (size_t i = 0; i < 7; ++i) {
        t.addPackage();
    }

    std::stringstream ss;
    ss << t;
    affirm_expected(ss.str(), "(28, 11) [x][x][x][x]~[x][x][x][_]~");

    return log.summarize();
}

// Expected output: (92, 51) [x][x][x][x]~(x5)[x][x][x][_]~[_][_][_][_]~(x2)
bool testSmartUpsize_02() {
    TestingLogger log("27 test smart upsize #2");

    Train t(SMART);
    for (size_t i = 0; i < 23; ++i) {
        t.addPackage();
    }

    std::stringstream ss;
    ss << t;
    affirm_expected(ss.str(),
                    "(92, 51) [x][x][x][x]~[x][x][x][x]~[x][x][x][x]~"
                    "[x][x][x][x]~[x][x][x][x]~[x][x][x][_]~"
                    "[_][_][_][_]~[_][_][_][_]~");

    return log.summarize();
}

// Expected output:
// (28, 11) [x][x][x][x]~[x][x][x][_]~
// (28, 15) [_][_][_][_]~
bool testBasicDownsize_01() {
    TestingLogger log("28 test basic downsize #1");

    Train t(BASIC);
    for (size_t i = 0; i < 7; ++i) {
        t.addPackage();
    }

    std::stringstream ss;
    ss << t;
    affirm_expected(ss.str(), "(28, 11) [x][x][x][x]~[x][x][x][_]~");
    ss.str("");  // Reset the stringstream

    for (size_t i = 0; i < 7; ++i) {
        t.removePackage();
    }

    ss << t;
    affirm_expected(ss.str(), "(28, 15) [_][_][_][_]~");

    return log.summarize();
}

// Expected output:
// (68, 57) [x][x][x][x]~(x4)[x][_][_][_]~
// (68, 97) [_][_][_][_]~
bool testBasicDownsize_02() {
    TestingLogger log("29 test basic downsize #2");

    Train t(BASIC);
    for (size_t i = 0; i < 17; ++i) {
        t.addPackage();
    }

    std::stringstream ss;
    ss << t;
    affirm_expected(ss.str(),
                    "(68, 57) [x][x][x][x]~[x][x][x][x]~[x][x][x][x]~"
                    "[x][x][x][x]~[x][_][_][_]~");
    ss.str("");  // Reset the stringstream

    for (size_t i = 0; i < 17; ++i) {
        t.removePackage();
    }

    ss << t;
    affirm_expected(ss.str(), "(68, 97) [_][_][_][_]~");

    return log.summarize();
}

// Expected output:
// (28, 11) [x][x][x][x]~[x][x][x][_]~
// (28, 13) [_][_][_][_]~
bool testSmartDownsize_01() {
    TestingLogger log("30 test smart downsize #1");

    Train t(SMART);
    for (size_t i = 0; i < 7; ++i) {
        t.addPackage();
    }

    std::stringstream ss;
    ss << t;

    affirm_expected(ss.str(), "(28, 11) [x][x][x][x]~[x][x][x][_]~");
    ss.str("");  // Reset the stringstream
    for (size_t i = 0; i < 7; ++i) {
        t.removePackage();
    }

    ss << t;
    affirm_expected(ss.str(), "(28, 13) [_][_][_][_]~");

    return log.summarize();
}

// Expected output:
// (92, 51) [x][x][x][x]~(x5)[x][x][x][_]~[_][_][_][_]~(x2)
// (92, 51) [x][x][x][x]~(x2)[x][x][_][_]~[_][_][_][_]~(x5)
bool testSmartDownsize_02() {
    TestingLogger log("31 test smart downsize #2");

    Train t(SMART);
    for (size_t i = 0; i < 23; ++i) {
        t.addPackage();
    }

    std::stringstream ss;
    ss << t;
    affirm_expected(ss.str(),
                    "(92, 51) [x][x][x][x]~[x][x][x][x]~[x][x][x][x]~"
                    "[x][x][x][x]~[x][x][x][x]~[x][x][x][_]~"
                    "[_][_][_][_]~[_][_][_][_]~");

    for (size_t i = 0; i < 13; ++i) {
        t.removePackage();
    }

    std::stringstream ss2;
    ss2 << t;
    affirm_expected(ss2.str(),
                    "(92, 51) [x][x][x][x]~[x][x][x][x]~"
                    "[x][x][_][_]~[_][_][_][_]~[_][_][_][_]~"
                    "[_][_][_][_]~[_][_][_][_]~[_][_][_][_]~");

    return log.summarize();
}

void interact(traintype ttype) {
    Train t(ttype);

    while (true) {
        char action;
        std::cin >> action;

        if (action == ';') {
            return;
        } else if (!std::cin.good()) {
            std::cerr << "Error reading input, exiting." << std::endl;
            return;
        } else if (action == 's') {
            t.addPackage();
        } else if (action == 'r') {
            t.removePackage();
        } else {
            std::cerr << "Unrecognized action '" << action << "'" << std::endl;
            continue;
        }
        std::cout << t << std::endl;
    }
}

int runTests() {
    TestingLogger log("all tests");

    ///////////////////////////////////
    // Car testing functions
    //
    /*
    testDeclareCar();
    testOutputEmptyCar();
    testAddPackage_1();
    testAddPackage_2();
    testAddPackage_3();
    testAddPackage_4();
    testAddPackageAndOutput_1();
    testAddPackageAndOutput_2();
    testAddPackageAndOutput_4();
    testAddRemovePackages_1();
    testAddRemovePackages_2();
    testAddRemovePackages_3();
    testAddRemovePackages_4();
    testAddRemovePackages_5();
    */

    ////////////////////////////////////
    // Train testing functions
    //
    // testCreateTrain();
    // testOutputTrain_01();
    // testOutputTrain_02();
    // testTrainAddAndOutput_01();
    // testTrainAddAndOutput_02();
    // testTrainAddAndOutput_03();
    // testTrainAddRemoveAndOutput_01();
    // testTrainAddRemoveAndOutput_02();
    // testTrainAddRemoveAndOutput_03();
    // testBasicUpsize_01();
    // testBasicUpsize_02();
    // testSmartUpsize_01();
    // testSmartUpsize_02();
    // testBasicDownsize_01();
    // testBasicDownsize_02();
    // testSmartDownsize_01();
    // testSmartDownsize_02();

    if (log.summarize(true)) {
        return 0;
    } else {
        return 1;
    }
}

int main(int argc, const char** argv) {
    if (argc != 2) {
        std::cout << "Expecting only one command line argument: [T|S|B]"
                  << std::endl;
        return 1;
    }

    std::string mode = argv[1];

    if (mode == "T") {
        return runTests();
    } else if (mode == "S") {
        interact(SMART);
    } else if (mode == "B") {
        interact(BASIC);
    } else {
        std::cerr << "Unknown mode, '" << mode << "'" << std::endl;
        return 1;
    }

    return 0;
}
