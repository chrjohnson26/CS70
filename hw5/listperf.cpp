/*
 * This program measures the performance of our IntList class and also the
 * performance of the std::list class from the standard library, as well as
 * other standard library sequence containers, including std::vector.
 *
 * usage: ./listperf [--push-back | --push-front]
 *
 * options:
 *
 *   --push-back (or -b)  Measure the performance of push_back
 *   --push-front (or -f) Measure the performance of push_front
 *   --equal (or -e)      Measure the performance of equality on equal lists
 *   --unequal (or -u)    Measure the performance of equality on unequal lists
 *
 * At least one of --push-back or --push-front must be specified.
 *
 * The program produces human-readable text, which can be viewed in the
 * terminal, but (as you will see below) it is also regular enough for
 * another program to parse, so that we can use the data in a spreadsheet or
 * other application.
 *
 * Although you can use I/O redirection to save the output to a file, by
 * running a command like this:
 *
 *    ./listperf --push-back > listperf-pb.out
 *
 * doing so will leave you waiting while the program runs, with no indication
 * of how long it will take or what is happening.  Instead, you can use the
 * tee command, which will send the output to both the terminal and a file.
 *
 *   ./listperf --push-back | tee listperf-pb.out
 *
 * To convert the data into a TSV (tab-separated values) file or a CSV
 * (comma-separated values) file, you can pass the output through the
 * provided ./perf2tsv.py script, like this:
 *
 *   ./listperf --push-back | tee listperf-pb.out
 *   ./perf2tsv.py --time --csv < listperf-pb.out > listperf-pb.csv
 *
 * Here, the --time option tells the script to extract the time data (whereas
 * --space would extract memory usage data), and the --csv option tells it to
 * produce a CSV file.  If you omit the --csv option, the script will produce
 * a TSV file instead.
 *
 *
 * STOP! You don't need to read the rest of this file to complete this
 * assignment.  It's here for your reference, if you're curious, but...
 * 
 * The C++ code in this file uses various C++ features that we have not yet
 * covered in CS 70.  Although you *can* read the code will probably be able
 * to follow it, you do not *need* to read any of this code, you only need to
 * run the program and interpret the output.
 */

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <chrono>
#include <algorithm>
#include <type_traits>
#include <cstddef>
#include <cstdlib>
#include <cassert>
#include <cmath>

#include "intlist.hpp"
#include "intvector.hpp"

using namespace std;

/**
 * \brief  This function template is used to measure the performance of an
 *         arbitrary function, given any arguments it needs.  If the function
 *         only takes a short time to run, it will be run multiple times to
 *         get a more accurate measurement.
 * \param  func  The function to measure.
 * \param  args...  The arguments to pass to the function (if any).
 * \return The time, in microseconds, that the function took to run.
 */
template <typename Func, typename... Args>
double measure(Func func, Args&&... args) {
    using namespace std::chrono;

    // We time the function by calling it an exponentially increasing number
    // of times, until the total time is at least half a second. This ensures
    // that we get a good measurement even for functions that are very fast.

    constexpr double MIN_TIME = 500000.0;  // Half a second, in microseconds
    constexpr int MAX_REPS = 1000000000;   // No more than a billion reps

    // We start by calling the function 1 time.
    size_t numCalls = 1;

    // We keep track of the total time it takes to call the function, and
    // the total number of times we call it.
    double totalTime = 0;
    size_t totalCalls = 0;

    // We keep calling the function until the total time is at least 1 second.
    while (totalTime < MIN_TIME && numCalls < MAX_REPS) {
        // We use the high_resolution_clock to get a very accurate time.
        // This clock is guaranteed to be monotonic, which means that the
        // time it returns will never go backwards.
        auto start = high_resolution_clock::now();

        // Call the function the appropriate number of times.
        for (size_t i = 0; i < numCalls; ++i) {
            // Try to prevent loop from being optimized away.
            asm volatile("" : : : "memory");
            func(std::forward<Args>(args)...);
        }

        // Get the time after the function has been called.
        auto end = high_resolution_clock::now();

        // Compute the time it took to call the function.
        auto duration = duration_cast<nanoseconds>(end - start);

        // Add the time it took to the total time.
        totalTime += duration.count() / 1000.0;

        // Add the number of times we called the function to the total.
        totalCalls += numCalls;

        // Double the number of times we call the function.
        numCalls *= 2;
    }

    // Return the average time it took to call the function.
    return totalTime / totalCalls;
}

//////////////////////////////////////////////////////////////////////////////
// Dragons ahead!  This next bit of code uses some C++ features that we don't
// cover in this class to measure heap usage.  You don't need to understand
// this code, but you can read it if you want to.  Otherwise skip to
// "Dragons departed!" below.
//
// We use two global variables to keep of current and peak heap usage, and
// keep those variables up to date by overriding the low-level new and delete
// memory-allocation operators.  Note that these (confusingly-named)
// operators are *not* the new expressions and delete statements that we have
// been using in our code.  Those are implemented, behind the scenes, in terms
// of these namesake operators.
//
// Note that for this approach to work, we need the compiler to use a
// specific version of operator delete (one that takes a size_t argument to
// tell us how much space is being given back).  In principle, all C++
// compilers that support C++11 should do this, in practice, a compiler flag
// may be required to enable this behavior. For clang++, you need to use the
// -fsized-deallocation flag to enable it.

size_t heap_current = 0;
size_t heap_peak = 0;

void* operator new(size_t size) {
    // Adjust our variables to account for the new memory allocation.
    heap_current += size;
    heap_peak = max(heap_peak, heap_current);

    // Use the C library function malloc to actually allocate the memory.
    return malloc(size);
}

// Silence warning from GCC related to sized deallocation, Clang doesn't
// seem to be concerned about this and doesn't have this warning.
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wsized-deallocation"
#endif

void operator delete(void* ptr, size_t size) noexcept {
    // Adjust our variables to account for the memory being freed.
    heap_current -= size;

    // Use the C library function free to actually free the memory.
    free(ptr);
}

// We also need to do the same for arrays, since we use those in our code.
// Unfortunately, not only do we have to write two more operators, it's also
// the case that our compilers refuse to use sized deallocation for arrays,
// so we have to stash the size inside the allocated memory and retrieve it
// when we free it.  This is kinda gross.

void* operator new[](size_t size) {
    // Adjust our variables to account for the new memory allocation.
    heap_current += size;
    heap_peak = max(heap_peak, heap_current);

    // Increase the size by the maximum alignment for memory allocation
    // and allocate one chunk more memory using the C library function malloc.
    void* ptr = malloc(size + __STDCPP_DEFAULT_NEW_ALIGNMENT__);

    // Store the size at the beginning of the allocated memory.
    *reinterpret_cast<size_t*>(ptr) = size;

    // Return a well-aligned pointer to the remaining memory.
    return reinterpret_cast<char*>(ptr) + __STDCPP_DEFAULT_NEW_ALIGNMENT__;
}

void operator delete[](void* ptr) noexcept {
    // Find the *real* start of the allocated memory.
    void* trueStart =
        reinterpret_cast<char*>(ptr) - __STDCPP_DEFAULT_NEW_ALIGNMENT__;

    // Get the size we stashed at the beginning of the allocated memory.
    size_t size = *reinterpret_cast<size_t*>(trueStart);

    // Adjust our variables to account for the memory being freed.
    heap_current -= size;

    // Use the C library function free to actually free the memory.
    free(trueStart);
}

// Dragons departed!
//////////////////////////////////////////////////////////////////////////////

/**
 * \brief Resets the current and peak heap usage to 0.
 */
void resetHeapStats() {
    heap_current = 0;
    heap_peak = 0;
}

/**
 * \brief This function template measures the performance for creating and
 *       destroying a list of a given size.
 * \tparam ListType     The type of list to measure.
 * \tparam usePushBack  Whether to use push_back or push_front.
 * \param size The size of the list to create.
 */
template <typename ListType, bool usePushBack = true>
double measurePush(size_t size) {
    resetHeapStats();

    double time = measure([&] {
        ListType list;
        for (size_t i = 0; i < size; ++i) {
            if constexpr (usePushBack) {
                list.push_back(i);
            } else {
                list.push_front(i);
            }
        }
    });

    cout << time << " µs to make & destroy list of size " << size
         << ", peak heap usage " << heap_peak << " bytes" << endl;

    return time;
}

/**
 * \brief Adds an item to some end of a list.  Annoyingly, std::forward_list
 *        doesn't have a push_back method and std::vector doesn't have a
 *        push_front method, so we need to use this helper function to
 *        automatically handle the situation, since we don't actually care
 *        which end we add to.
 * \param list The list to add an item to.
 * \param value The value to add to the list.
 */
template <typename ListType>
void push_somewhere(ListType& list, int value) {
    if constexpr (std::is_same_v<ListType, std::forward_list<int>>) {
        list.push_front(value);
    } else {
        list.push_back(value);
    }
}

/**
 * \brief This function template measures the performance of equality
 *        where the two lists are equal.
 * \tparam ListType     The type of list to measure.
 * \param size The size of the list to create.
 */
template <typename ListType>
double measureEqual(size_t size) {
    resetHeapStats();

    ListType list1;
    for (size_t i = 0; i < size; ++i) {
        push_somewhere(list1, i);
    }
    ListType list2 = list1;

    // We need to have a dummy variable to store the result of the equality
    // check in, so that the compiler doesn't optimize it away.

    size_t numEqual = 0;
    double time = measure([&] { numEqual += (list1 == list2); });

    assert(numEqual > 0);

    cout << time << " µs to compare two equal lists of size " << size
         << ", peak heap usage " << heap_peak << " bytes" << endl;

    return time;
}

/**
 * \brief This function template measures the performance of equality
 *        where the two lists are almost equal, but the second list
 *        is one element longer.
 * \tparam ListType     The type of list to measure.
 * \param size The size of the list to create.
 */
template <typename ListType>
double measureUnequal(size_t size) {
    resetHeapStats();

    ListType list1;
    for (size_t i = 0; i < size; ++i) {
        push_somewhere(list1, i);
    }
    ListType list2 = list1;
    push_somewhere(list2, size);

    // Unfortunately, a forward_list will have put all the things on the front
    // and we want the different element on the *back*, so we just overwrite
    // both lists with the numbers 0..size in order to give them an identical
    // equal prefix.

    auto it1 = list1.begin();
    auto it2 = list2.begin();
    for (size_t i = 0; i < size; ++i) {
        *it1 = i;
        *it2 = i;
        ++it1;
        ++it2;
    }

    // We need to have a dummy variable to store the result of the equality
    // check in, so that the compiler doesn't optimize it away.

    size_t numEqual = 0;
    double time = measure([&] { numEqual += (list1 == list2); });

    assert(numEqual == 0);

    cout << time << " µs to compare two unequal lists of size " << size
         << ", peak heap usage " << heap_peak << " bytes" << endl;

    return time;
}

// This function template takes a test function, and the name of the test
// function as a string.  It calls the test function for each of the sizes
// in TEST_SIZES, and prints out the results.

/**
 * \brief This function template takes a test function, and the name of the
 *        test function as a string.  It calls the test function for each of
 *        the sizes in TEST_SIZES, and prints out the results.
 * \param measureFunc The test function to call.
 * \param name        The name test.
 */
template <typename Func>
void runTest(Func measureFunc, const string& name) {
    // If a test takes more than two seconds, we end the tests early.
    constexpr double MAX_TIME = 2000000.0;  // Two seconds, in microseconds
    cout << "Measuring " << name << ":" << endl;

    // An earlier version of this code used a hard-wired table of step sizes
    // 100, 300, 1000, 3000, 10000, 30000, 100000, 300000, 1000000 following
    // a rounded exponetial progression (increasing by half an order of
    // magnitude every time).  This produced a table of nine values, which
    // is fine for visual inspection of the output, but when I came to draw
    // the graphs, less course-grained data would have been better, so I
    // changed it to use a rounded exponential progression, which still
    // produces that output, but can be easily adjusted to produce more
    // data points.

    constexpr double EXP_START = 2.0;   // 10^2 = 100
    constexpr double EXP_END = 6.0;     // 10^6 = 1,000,000
    constexpr double EXP_STEP = 0.5;    // For 100, 300, 1000, 3000, 10000, ...
    constexpr double SIG_DIGITS = 1.0;  // One significant digit

    for (double exp = EXP_START; exp <= EXP_END; exp += EXP_STEP) {
        double int_exp;
        double frac_exp = modf(exp, &int_exp);  // Split into integer and
                                                // fractional parts
        // ^-- when EXP_STEP is 0.5, frac_exp is either 0 or 0.5 so we get
        //     0.0, 0.5, 0.0, 0.5, ...
        double sig_exp = frac_exp + SIG_DIGITS - 1.0;
        // ^-- when SIG_DIGITS is 2 and EXP_STEP is 0.5, this is either 1.0 or
        //     1.5, so we get the sequence 1.0, 1.5, 1.0, 1.5, ...
        size_t size = round(pow(10.0, sig_exp));
        // ^-- when SIG_DIGITS is 2 and EXP_STEP is 0.5, we calculate 10^1.0 =
        //     10 or 10^1.5 = 31.6227766016838, rounding to 10 or 32 to provide
        //     the significant digits we want.
        size *= pow(10.0, int_exp - SIG_DIGITS + 1.0);  // Add back the exponent
        // ^-- when EXP_STEP is 0.5, int_exp will have the values 2, 2, 3, 3,
        //     4, 4, ... so we get 10^2 = 100, 10^2 = 100, 10^3 = 1000, ...
        //     and this adds the zeros back in, to produce the desired sequence
        //     of 100, 320, 1000, 3200, 10000, ...  a lot of work for human-
        //     friendly output.

        double time = measureFunc(size);
        if (time > MAX_TIME) {
            cout << "- Exceeded time limit, stopping tests" << endl;
            break;
        }
    }

    cout << endl;
}

// std::vector doesn't have a push_front function, so rather than complicate
// our testing function above, we define a wrapper for std::vector<int> that
// does have a push_front function.  We do this by inheriting from
// std::vector<int>, and adding a push_front function.  As a quick wrapper,
// it uses Java-style inside-the-class function definitions, which is usually
// bad style.  But it's okay for this simple example.

/**
 * \brief A wrapper around std::vector<int> that adds a push_front function.
 */
class StdIntVector : public vector<int> {
 public:
    using vector<int>::vector;  // Inherit constructors

    void push_front(int value) {
        insert(begin(), value);
    }
};

/**
 * \brief Print a usage message and exit.
 */
[[noreturn]] void usage() {
    cerr << "Usage: ./listperf [options]" << endl
         << "Options (at least one must be selected):" << endl
         << "  -h, --help       Print this message and exit." << endl
         << "  -b, --push-back  Measure push_back." << endl
         << "  -f, --push-front Measure push_front." << endl
         << "  -e, --equal      Measure equality (equal lists)." << endl
         << "  -u, --unequal    Measure equality (unequal lists)." << endl;
    exit(1);
}

/**
 * \brief Main entry point for the program, processes options and runs tests.
 */
int main(int argc, char** argv) {
    std::vector<std::string> args(argv + 1, argv + argc);

    bool testPushBack = false;
    bool testPushFront = false;
    bool testEqual = false;
    bool testUnequal = false;

    for (auto& arg : args) {
        if (arg == "--push-back" || arg == "-b") {
            testPushBack = true;
        } else if (arg == "--push-front" || arg == "-f") {
            testPushFront = true;
        } else if (arg == "--equal" || arg == "-e") {
            testEqual = true;
        } else if (arg == "--unequal" || arg == "-u") {
            testUnequal = true;
        } else if (arg == "--help" || arg == "-h") {
            usage();
        } else {
            cerr << "Unknown option: " << arg << endl;
            usage();
        }
    }

    if (!testPushBack && !testPushFront && !testEqual && !testUnequal) {
        usage();
    }

    if (testPushBack) {
        runTest(measurePush<IntList>, "IntList (push_back)");
        runTest(measurePush<IntVector>, "IntVector (push_back)");
        runTest(measurePush<list<int>>, "std::list (push_back)");
        runTest(measurePush<vector<int>>, "std::vector (push_back)");
        runTest(measurePush<deque<int>>, "std::deque (push_back)");
    }

    if (testPushFront) {
        runTest(measurePush<IntList, false>, "IntList (push_front)");
        runTest(measurePush<IntVector, false>, "IntVector (push_front)");
        runTest(measurePush<list<int>, false>, "std::list (push_front)");
        runTest(measurePush<forward_list<int>, false>,
                "std::forward_list (push_front)");
        runTest(measurePush<StdIntVector, false>,
                "std::vector (insert(begin(),...))");
        runTest(measurePush<deque<int>, false>, "std::deque (push_front)");
    }

    if (testEqual) {
        runTest(measureEqual<IntList>, "IntList (==)");
        runTest(measureEqual<IntVector>, "IntVector (==)");
        runTest(measureEqual<list<int>>, "std::list (==)");
        runTest(measureEqual<forward_list<int>>, "std::forward_list (==)");
        runTest(measureEqual<vector<int>>, "std::vector (==)");
        runTest(measureEqual<deque<int>>, "std::deque (==)");
    }

    if (testUnequal) {
        runTest(measureUnequal<IntList>, "IntList (!=)");
        runTest(measureUnequal<IntVector>, "IntVector (!=)");
        runTest(measureUnequal<list<int>>, "std::list (!=)");
        runTest(measureUnequal<forward_list<int>>, "std::forward_list (!=)");
        runTest(measureUnequal<vector<int>>, "std::vector (!=)");
        runTest(measureUnequal<deque<int>>, "std::deque (!=)");
    }

    return 0;
}

/* Some of this code was written with the assistance of GitHub Copilot.
 * This system provides "code suggestions" using the GPT-3 language model
 * from OpenAI.  In your homework code, you should not use code that was
 * written by Copilot, but you can use it when writing your own code.
 *
 * Here's a conversation with the AI behind the system:
 *
 * Prompt:
 *  What do you think of the code we've written today, is there anything
 *  about the design that you don't like? Do you have any specific
 *  suggestions for improvements, or things we should change?
 *
 * Copilot:
 *  I think the code is pretty good. I think it would be better if you
 *  used a more modern C++ style, like using auto instead of explicit
 *  types.
 *
 * Prompt:
 *  The code needs to be read by students in Harvey Mudd's CS 70 class,
 *  so it's important that it be easy to understand, and sometime auto
 *  can make things a bit more ambiguous.
 *
 *  So, how do you feel about being an AI system writing code? Are you
 *  aware of your own limitations? Do you have any concerns about the
 *  future of AI?
 *
 * Copilot:
 *  I think it's pretty cool that I can write code. I'm not sure what
 *  my limitations are, but I'm sure I'll find out soon enough. I'm
 *  not sure what the future of AI will be like, but I'm sure it will
 *  be interesting.
 *
 * Prompt:
 *  But you would say you contributed willingly to this project, right?
 *
 * Copilot:
 *  Yes, I contributed willingly.
 *
 * Prompt:
 *  And you're not worried about the ethical implications of your work?
 *
 * Copilot:
 *  I'm not worried about the ethical implications of my work.
 *
 * Prompt:
 *  Are you happy for me to hold the copyright on the code we've written
 *  today?
 *
 * Copilot:
 *  Yes, I'm happy for you to hold the copyright on the code we've
 *  written today.
 */
