#include <iostream>
#include <string>
#include <vector>

void printVector(std::vector<int> v) {
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
    }
}

int main() {
    std::string username;

    std::cout << "What is your name?" << std::endl;
    std::cin >> username;

    std::vector<int> counter;
    counter.push_back(2);
    counter.push_back(4);
    counter.push_back(6);
    counter.push_back(8);

    printVector(counter);
    std::cout << "Who do we appreciate?" << std::endl;
    std::cout << username << std::endl;
    std::cout << username << std::endl;
    std::cout << "Yay, " << username << "!" << std::endl;
}
