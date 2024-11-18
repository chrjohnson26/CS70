/**
 * stringhash.cpp
 * Authors: Christian Johnson and Olivia Schleifer

 * Part of CS70 Homework 8. This file may NOT be
 * shared with anyone other than the author(s) and
 * the current semester's CS70 staff without
 * explicit written permission from one of the
 * CS70 instructors.

 *
 */

#include <cs70/stringhash.hpp>

using std::string;

// Hash Function Gallery
//
// These are the hash functions our group has examined, one of them is used
// as myhash (see later code in the file)
//
// All the code below is in an anonymous namespace, so these function names
// are hidden from other code.
namespace {

/**
 * This function iterates over each character in the string and updates its
 * hash value by multiplying by a prime (131) and adding a pointer to a
 * character
 */
size_t updateHash(const std::string& str) {
    const char* c_str = str.c_str();
    size_t hash = 0;

    while (*c_str) {
        hash = (hash * 131) + *c_str;
        // 131 is a prime number often used in hash functions
        ++c_str;
    }

    return hash;
}

/**
 * This function updates the hash values using a series of bitwise and
 * arithmetic operations. The specific constants are chosen to provide good
 * mixing properties
 */
size_t jenkinsOneAtATimeHash(const std::string& key) {
    size_t hash = 0;
    size_t i = 0;

    while (i < key.length()) {
        hash += key[i++];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

/**
 * The djb2Hash function iterates through the input string and updates the has
 * value using multiplication and the exclusive or (XOR) operation
 *
 */
size_t djb2Hash(const std::string& str) {
    size_t hash = 5381;  // Initial hash value

    for (char ch : str) {
        hash = (hash * 33) ^ static_cast<size_t>(ch);
    }

    return hash;
}

}  // end of anonymous namespace

/* Hash Function Choice
 * The updateHash function iterates over each character in the string and
 * updates its hash value by multiplying by a prime (131) and adding a pointer
 * to a character
 *
 * The jenkinsOneAtATimeHash function updates the hash values using a series of
 * bitwise and arithmetic operations. The specific constants are chosen to
 * provide good mixing properties
 *
 * The djb2Hash function iterates through the input string and updates the has
 * value using multiplication and the exclusive or (XOR) operation
 *
 */

size_t myhash(const string& str) {
    updateHash(str);
    jenkinsOneAtATimeHash(str);
    return djb2Hash(str);
}

// You don't have to fully understand this code, but it is used to provide a
// table used by stringhash-test.cpp, all you need to do is list the name
// of your hash function (for printing) and the actual function name from
// above.
// TODO(Students): Update this block with the names of your hash functions
std::initializer_list<HashFunctionInfo> hashInfo = {
    {"Update", updateHash},
    {"Jenkins One At A Time", jenkinsOneAtATimeHash},
    {"DJB2", djb2Hash}  // No comma for last one
};
