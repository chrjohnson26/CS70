#include <iostream>

using std::cout;
using std::endl;

int main() {
    const int NUM_VALUES = 2;
    int* values = new int[NUM_VALUES];

    for (size_t i = 0; i < NUM_VALUES; ++i) {
        values[i] = 70;
    }

    for (size_t i = 0; i < NUM_VALUES; ++i) {
        cout << values[i] << endl;
    }

    delete[] values;
    delete[] values;

    return 0;
}
