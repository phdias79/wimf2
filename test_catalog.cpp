#include "catalog.hpp"
#include <iostream>
#include <string>
#include <bitset>

void test_1() {

    DynamicBank bank;
    for (int i = 0; i < 100; i++) {
        std::string filename = std::string("File_") + std::to_string(i);
        bank.add_filename(filename.c_str());
    }
    std::cout << "SIZE:" << bank.size << "\n";

}


int main() {
    test_1();
    std::cout << "A:" << std::bitset<8>('A') << "\n";
    std::cout << "Z:" << std::bitset<8>('Z') << "\n";
    std::cout << "a:" << std::bitset<8>('a') << "\n";
    std::cout << "z:" << std::bitset<8>('z') << "\n";
    std::cout << "_:" << std::bitset<8>('_') << "\n";
    std::cout << "-:" << std::bitset<8>('-') << "\n";

}