/*
 * A tiny example of code that uses our IntVector class.
 */

#include "intvector.hpp"

#include <iostream>

using namespace std;

int main() {
    IntVector vec{4};   // Create a vector with capacity 4, so it won't
                        // need to resize in this example.

    cout << "Pushing 3 items to the back: 54, 42, 7" << endl;
    vec.push_back(54);
    vec.push_back(42);
    vec.push_back(7);

    // Remove front item and print it
    cout << "Popping first item: " << vec.pop_front() << endl;

    // Create an iterator to the first item
    IntVector::iterator it = vec.begin();

    // <-- Draw a memory diagram at this point.

    cout << "Front item: " << *it << endl;

    vec.push_back(3);       // Add another item to the vector

    cout << "Contents after pushing 3 to the back: ";
    bool needsComma = false;
    for (int elem : vec) {  // Print all items in the vector
        if (needsComma) {
            cout << ", ";
        }
        cout << elem;
        needsComma = true;
    }
    cout << endl;

    return 0;
}
