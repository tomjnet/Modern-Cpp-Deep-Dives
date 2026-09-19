// std::list in 10 Minutes - slide 9: splice and merge, O(1) moves between lists
// Build: make 09_splice
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>

static void print(const char* label, const std::list<int>& l) {
    std::cout << label << ':';
    for (int v : l) std::cout << ' ' << v;
    std::cout << '\n';
}

int main() {
    std::list<int> a{1, 2, 3};
    std::list<int> b{7, 8, 9};
    const int* addr7 = &b.front();

    a.splice(a.end(), b);         // O(1): all of b moves to the end of a
                                  // no copy, no allocation, b is empty
    print("a after splice(a.end(), b)", a);
    std::cout << "b.size() = " << b.size() << ", the node of 7 kept its address: "
              << (addr7 == &*std::next(a.begin(), 3) ? "yes" : "no") << '\n';

    auto it = std::next(a.begin(), 3);       // node 7
    a.splice(a.begin(), a, it);   // O(1): one node moves to the front
    print("a after moving node 7 to the front", a);
    std::cout << "it still points at " << *it << ", now the first element\n";

    std::list<int> c{4, 5};       // both sorted first
    a.sort();
    a.merge(c);                   // O(n): relinks nodes, c is empty
    print("a after sort and merge(c)", a);
    std::cout << "c.size() = " << c.size() << '\n';

    // the measurement: moving 1,000,000 nodes between lists costs the same as moving one
    constexpr int n = 1'000'000;
    using clock = std::chrono::steady_clock;
    auto us = [](auto d) { return std::chrono::duration<double, std::micro>(d).count(); };
    std::list<int> big(n, 1);
    std::list<int> target;
    auto t0 = clock::now();
    target.splice(target.begin(), big);          // whole list: O(1)
    auto t1 = clock::now();
    big.splice(big.begin(), target, target.begin());   // one node: O(1)
    auto t2 = clock::now();
    std::cout << "splice of " << n << " nodes: " << us(t1 - t0) << " us, splice of one node: " << us(t2 - t1)
              << " us (target.size() = " << target.size() << ", big.size() = " << big.size() << ")\n";

    // a range from another list is linear in the range: the size has to be recounted
    auto first = std::next(target.begin(), 1000);
    auto last = std::next(first, n / 2);
    auto t3 = clock::now();
    big.splice(big.end(), target, first, last);
    auto t4 = clock::now();
    std::cout << "splice of a " << n / 2 << " node range from another list: " << us(t4 - t3)
              << " us (big.size() = " << big.size() << ")\n";
    return 0;
}
