// std::vector in 10 Minutes - slide 5: create and access
// Build: make 05_create_access   (or: g++ -std=c++20 -Wall -O2 05_create_access.cpp -o 05_create_access)
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    std::vector<int> a;                  // empty, no heap block yet
    std::vector<int> b(4, 7);            // {7, 7, 7, 7}
    std::vector<int> c{10, 20, 30, 40};  // initializer list

    int x = c[1];        // 20, no bounds check, O(1)
    int y = c.at(3);     // 40, throws std::out_of_range
    int f = c.front();   // 10
    int l = c.back();    // 40
    int* p = c.data();   // pointer to the contiguous block

    std::cout << "a.size()  = " << a.size() << " (default constructed, capacity " << a.capacity() << ")\n";
    std::cout << "b         = ";
    for (int v : b) std::cout << v << ' ';
    std::cout << "\nc[1]      = " << x << "\nc.at(3)   = " << y << "\nc.front() = " << f << "\nc.back()  = " << l
              << "\nc.data()  = " << static_cast<const void*>(p) << " (p[2] = " << p[2] << ")\n";

    try {
        int bad = c.at(10);   // bounds checked: throws instead of reading garbage
        std::cout << "not reached: " << bad << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "c.at(10) threw std::out_of_range: " << e.what() << '\n';
    }
    return 0;
}
