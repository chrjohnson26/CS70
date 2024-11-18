#include <iostream>
#include <vector>

void printVector(std::vector<int> v) {
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
    }
}
