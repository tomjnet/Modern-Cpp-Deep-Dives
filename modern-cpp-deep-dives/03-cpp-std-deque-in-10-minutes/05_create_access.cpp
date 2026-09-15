// std::deque in 10 Minutes - slide 5: create and access
// Build: make 05_create_access   (or: g++ -std=c++20 -Wall -O2 05_create_access.cpp -o 05_create_access)
#include <deque>
#include <iostream>
#include <stdexcept>

int main() {
    std::deque<int> a;                  // empty: no blocks yet
    std::deque<int> b(4, 7);            // {7, 7, 7, 7}
    std::deque<int> c{10, 20, 30, 40};  // initializer list

    int x = c[1];        // 20: block = map[i / B], slot = i % B
    int y = c.at(3);     // 40, throws std::out_of_range
    int f = c.front();   // 10
    int l = c.back();    // 40
    // no c.data(): the elements are not one contiguous block

    std::cout << "a.size()  = " << a.size() << " (default constructed, no blocks)\n";
    std::cout << "b         = ";
    for (int v : b) std::cout << v << ' ';
    std::cout << "\nc[1]      = " << x << "\nc.at(3)   = " << y << "\nc.front() = " << f << "\nc.back()  = " << l << '\n';

    // elements of a deque are not contiguous: the address gap between neighbours is not always sizeof(int)
    std::deque<int> big;
    for (int i = 0; i < 2000; ++i) big.push_back(i);
    int jumps = 0;
    for (std::size_t i = 1; i < big.size(); ++i)
        if (&big[i] != &big[i - 1] + 1) ++jumps;
    std::cout << "2000 elements: " << jumps << " block boundaries where &d[i] != &d[i-1] + 1 (a vector would have 0)\n";

    try {
        int bad = c.at(10);   // bounds checked: throws instead of reading garbage
        std::cout << "not reached: " << bad << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "c.at(10) threw std::out_of_range: " << e.what() << '\n';
    }
    return 0;
}
