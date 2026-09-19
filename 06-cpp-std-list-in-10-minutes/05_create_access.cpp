// std::list in 10 Minutes - slide 5: create and access
// Build: make 05_create_access
#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>

int main() {
    std::list<int> a;                  // empty: sentinel only, no nodes
    std::list<int> b(4, 7);            // {7, 7, 7, 7}: four allocations
    std::list<int> c{10, 20, 30, 40};  // initializer list, one node each

    int f = c.front();   // 10: O(1), sentinel.next
    int l = c.back();    // 40: O(1), sentinel.prev
    // no c[i], no c.at(i), no c.data(): walk the links instead
    int x = *std::next(c.begin(), 2);  // 30: O(i), two hops

    std::cout << "a.size() = " << a.size() << ", b.size() = " << b.size() << ", c.size() = " << c.size() << '\n';
    std::cout << "c.front() = " << f << ", c.back() = " << l << ", *std::next(c.begin(), 2) = " << x << '\n';
    std::cout << "sizeof(std::list<int>) = " << sizeof(std::list<int>)
              << " bytes: the object is only the sentinel links plus the size\n";

    // reaching position i costs i hops, so a full walk is n hops
    std::size_t hops = 0;
    for (auto it = c.begin(); it != c.end(); ++it) ++hops;
    std::cout << "walking all of c: " << hops << " hops for " << c.size() << " elements\n";

    // every node is a separate heap allocation: the values are not 4 bytes apart
    std::cout << "node addresses:";
    const char* prev = nullptr;
    for (const int& v : c) {
        const char* here = reinterpret_cast<const char*>(&v);
        std::cout << ' ' << static_cast<const void*>(here);
        if (prev) std::cout << " (gap " << (here - prev) << " B)";
        prev = here;
    }
    std::cout << "\n(a vector would show a gap of exactly 4 B between neighbours)\n";
    return 0;
}
