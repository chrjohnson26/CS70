#include <cs70/stringhash.hpp>
#include "hashset.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <stdexcept>
#include <system_error>
#include <limits>
#include <cerrno>
#include <chrono>
#include <random>
#include <cstddef>

/**
 * \brief Fill a std::vector of words using content from a file.
 * \param words The vector to fill.
 * \param filename The file to read.
 * \param maxwords Maximum number of words to read
 */
void readWords(std::vector<std::string>& words, std::string filename,
               size_t maxwords) {
    std::cerr << "Reading words from " << filename << "...";
    try {
        std::ifstream in;
        in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        in.open(filename);
        in.exceptions(std::ifstream::badbit);
        std::string word;
        for (size_t i = 0; i < maxwords; ++i) {
            in >> word;
            if (!in.good()) {
                break;
            }
            words.push_back(word);
        }
        std::cerr << " done!\n";
    } catch (std::system_error& e) {
        // The error exceptions thrown by our standard library aren't very
        // meaningful, so we catch them and rethrow them with more information.
        throw std::system_error(
            std::make_error_code(std::errc(errno)),
            "Error reading '" + filename + "' (" + e.code().message() + +")");
    }
}

/**
 * \brief Fill a HashSet<std::string> using content from a vector of words.
 *        The order that the words are inserted is exactly the order in the
 *        vector.  The vector is emptied of words as part of this process.
 * \param dict The HashSet<std::string> to insert into.
 * \param words The vector from which the words will be taken.
 */
void insertAsRead(HashSet<std::string>& dict, std::vector<std::string>& words) {
    for (const auto& word : words) {
        dict.insert(word);
    }
    words.clear();
}

/**
 * \brief Fill a HashSet<std::string> using content from a vector of words.
 *        The words are inserted in a random order.  The vector is emptied of
 *        words as part of this process.
 * \param dict The HashSet<std::string> to insert into.
 * \param words The vector from which the words will be taken.
 */
void insertShuffled(HashSet<std::string>& dict,
                    std::vector<std::string>& words) {
    std::random_device rdev;
    std::mt19937 prng{rdev()};  // This is only a 32-bit seed (weak!), but meh.
    std::shuffle(words.begin(), words.end(), prng);
    insertAsRead(dict, words);
}

constexpr const char* DICT_FILE = "/home/student/data/smalldict.words";
constexpr const char* CHECK_FILE = "/home/student/data/ispell.words";

/**
 * \brief Print usage information for this program.
 * \param progname The name of the program.
 */
void usage(const char* progname) {
    std::cerr << "Usage: " << progname << " [options] [file-to-check ...]\n"
              << "Options:\n"
              << "  -h, --help             Print this message and exit.\n"
              << "  -f, --file-order       Insert words in the order they "
                 "appear (default).\n"
              << "  -r, --random-order     Insert words in random order,"
                 " by shuffling the input.\n"
              << "  -b, --num-buckets      Size of the hash table to use.\n"
              << "  -l, --load-factor      Max load factor to use.\n"
              << "  -n, --num-dict-words   Number of words to read from the "
                 "dictionary.\n"
              << "  -m, --num-check-words  Number of words to check for "
                 "spelling.\n"
              << "  -d, --dict-file        Use a different dictionary file.\n"
              << "  -p, --print-dict       Print the dictionary after "
                 "insertion.\n";
    std::cerr << "\nDefault dictionary file: " << DICT_FILE << std::endl;
    std::cerr << "Default file to check:   " << CHECK_FILE << std::endl;
}
/**
 * \brief Main program,
 */
int main(int argc, const char** argv) {
    // Defaults
    enum { AS_READ, SHUFFLED } insertionOrder = AS_READ;
    size_t numBuckets = HashSet<std::string>::DEFAULT_NUM_BUCKETS;
    double loadFactor = HashSet<std::string>::DEFAULT_MAX_LOAD_FACTOR;

    std::string dictFile = DICT_FILE;
    std::string fileToCheck = CHECK_FILE;

    size_t maxDictWords = std::numeric_limits<size_t>::max();
    size_t maxCheckWords = std::numeric_limits<size_t>::max();

    bool printDict = false;

    // Process Options and command-line arguments
    std::list<std::string> args(argv + 1, argv + argc);
    while (!args.empty() && args.front()[0] == '-') {
        std::string option = args.front();
        if (option == "-f" || option == "--file-order") {
            insertionOrder = AS_READ;
        } else if (option == "-r" || option == "--random-order") {
            insertionOrder = SHUFFLED;
        } else if (option == "-b" || option == "--num-buckets" || option == "-l"
                   || option == "--load-factor" || option == "-n"
                   || option == "--num-dict-words" || option == "-m"
                   || option == "--num-check-words") {
            args.pop_front();
            if (args.empty()) {
                std::cerr << option << " expects a number\n";
                usage(argv[0]);
                return 1;
            }
            try {
                if (option == "-l" || option == "--load-factor") {
                    loadFactor = std::stod(args.front());
                } else {
                    size_t num = std::stoul(args.front());
                    if (option == "-b" || option == "--num-buckets") {
                        numBuckets = num;
                    } else if (option == "-n" || option == "--num-dict-words") {
                        maxDictWords = num;
                    } else if (option == "-m"
                               || option == "--num-check-words") {
                        maxCheckWords = num;
                    }
                }
            } catch (std::invalid_argument& e) {
                std::cerr << option << " expects a number\n";
                usage(argv[0]);
                return 1;
            }
        } else if (option == "-d" || option == "--dict-file") {
            args.pop_front();
            if (args.empty()) {
                std::cerr << option << " expects a filename\n";
                usage(argv[0]);
                return 1;
            }
            dictFile = args.front();
        } else if (option == "-p" || option == "--print-dict") {
            printDict = true;
        } else if (option == "-h" || option == "--help") {
            usage(argv[0]);
            return 0;
        } else {
            std::cerr << "Unknown option: " << option << std::endl;
            usage(argv[0]);
            return 1;
        }
        args.pop_front();
    }
    if (!args.empty()) {
        fileToCheck = args.front();
        args.pop_front();
        if (!args.empty()) {
            std::cerr << "extra argument(s), " << args.front() << std::endl;
            return 1;
        }
    }

    // Read the dictionary into a vector
    std::vector<std::string> words;
    readWords(words, dictFile, maxDictWords);

    // Create our search hash table (and time how long it all takes)
    std::cerr << "Inserting into dictionary ";

    // Initialize set to use the specified number of buckets and load factor
    HashSet<std::string> dict(numBuckets, loadFactor);

    auto startTime = std::chrono::high_resolution_clock::now();

    if (insertionOrder == AS_READ) {
        std::cerr << "(in order read)...";
        insertAsRead(dict, words);
    } else if (insertionOrder == SHUFFLED) {
        std::cerr << "(in shuffled order)...";
        insertShuffled(dict, words);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> secs = endTime - startTime;
    std::cerr << " done!\n";

    // Print some stats about the process

    std::cout << " - insertion took " << secs.count() << " seconds\n"
              << " - " << dict.size() << " words in " << dict.buckets()
              << " buckets\n - ";
    dict.showStatistics(std::cout);

    // Print the dictionary if requested and it isn't too big, using
    // the hashtable's << operator
    constexpr size_t MAX_BUCKETS = 127;
    if (printDict) {
        if (dict.buckets() > MAX_BUCKETS) {
            std::cout << "\nHash table too large to print!\n\n";
        } else {
            std::cout << "\nHash table for dictionary:\n" << dict << std::endl;
        }
    }

    // Read some words to check against our dictionary (and time it)

    readWords(words, fileToCheck, maxCheckWords);
    std::cerr << "Looking up these words in the dictionary...";
    size_t inDict = 0;
    startTime = std::chrono::high_resolution_clock::now();
    for (const auto& word : words) {
        if (dict.exists(word)) {
            ++inDict;
        }
    }

    endTime = std::chrono::high_resolution_clock::now();
    secs = endTime - startTime;
    std::cerr << " done!\n";

    // Show some stats

    std::cout << " - looking up took " << secs.count() << " seconds\n - ";
    std::cout << words.size() << " words read, " << inDict
              << " in dictionary\n\n";

    return 0;
}
