#include <iostream>
#include <vector>
#include "printvector.hpp"

int main() {
    std::vector<int> countdown;
    countdown.push_back(10);
    countdown.push_back(9);
    countdown.push_back(8);
    countdown.push_back(7);
    countdown.push_back(6);
    countdown.push_back(5);
    countdown.push_back(4);
    countdown.push_back(3);
    countdown.push_back(2);
    countdown.push_back(1);

    printVector(countdown);
    std::cout << "Blast off!" << std::endl;
}
