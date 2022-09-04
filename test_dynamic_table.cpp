#include "dynamic_table.hpp"
#include <iostream>

void test_1() {

    #define SIZE1 5
    #define SIZE2 1800

    DynamicTable<int> d(SIZE1);
    for (int i = 0; i < SIZE2; i++) {
        std::cout << "SIZE:" << d.size << "\n";
        d.append(i*i);
    }
    std::cout << "SIZE:" << d.size << "\n";
    for (int i = 0; i < d.size; i++) {
        std::cout << "[" << i << "]= " << d[i] << "\n";
    }

    FixedTable<int> f = d.to_FixedTable();
    for (int i = 0; i < f.size; i++) {
        std::cout << "[#" << i << "]= " << f[i] << "\n";
    }

}


int main() {
    test_1();

}