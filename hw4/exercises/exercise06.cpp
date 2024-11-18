#include <iostream>

using std::cout;
using std::endl;

int main() {
    const int NUM_VALUES = 2;
    int values[NUM_VALUES] = {70, 70};
    int* valuesPointer = values;

    for (size_t i = 0; i < NUM_VALUES; ++i) {
        cout << values[i] << endl;
    }

    delete[] valuesPointer;

    return 0;
}
