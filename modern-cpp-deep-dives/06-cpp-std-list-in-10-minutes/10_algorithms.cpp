// std::list in 10 Minutes - slide 10: sort, unique, remove and reverse
// Build: make 10_algorithms
#include <algorithm>
#include <chrono>
#include <iostream>
#include <list>
#include <random>
#include <vector>

static void print(const char* label, const std::list<int>& l) {
    std::cout << label << ':';
    for (int v : l) std::cout << ' ' << v;
    std::cout << '\n';
}

int main() {
    std::list<int> l{40, 10, 30, 10, 20};

    l.sort();            // O(n log n): merge sort on links, stable
    print("after sort", l);
    l.unique();          // O(n): drops adjacent duplicates
    print("after unique", l);
    l.remove(30);        // O(n): erases every 30, relinks around it
    l.remove_if([](int x) { return x > 35; });
    print("after remove(30) and remove_if(> 35)", l);
    l.reverse();         // O(n): swaps prev and next in every node
    print("after reverse", l);

    // std::sort(l.begin(), l.end()) does not compile:
    // bidirectional iterators, no random access
    auto it = std::find(l.begin(), l.end(), 20);   // O(n)
    std::cout << "std::find(20): " << (it != l.end() ? "found" : "not found") << '\n';

    // the measurement: the same n log n sort and the same linear scan on a list and on a vector
    constexpr int n = 1'000'000;
    std::mt19937 rng(42);
    std::vector<int> vec(n);
    for (int& v : vec) v = static_cast<int>(rng() % 1'000'000);
    std::list<int> big(vec.begin(), vec.end());

    using clock = std::chrono::steady_clock;
    auto ms = [](auto d) { return std::chrono::duration<double, std::milli>(d).count(); };
    auto t0 = clock::now();
    big.sort();
    auto t1 = clock::now();
    std::sort(vec.begin(), vec.end());
    auto t2 = clock::now();
    std::cout << "sort " << n << " ints: list.sort() " << ms(t1 - t0) << " ms, std::sort on vector " << ms(t2 - t1) << " ms\n";

    auto t3 = clock::now();
    auto f1 = std::find(big.begin(), big.end(), -1);   // absent: full scan, cache miss per node
    auto t4 = clock::now();
    auto f2 = std::find(vec.begin(), vec.end(), -1);   // absent: full scan, contiguous
    auto t5 = clock::now();
    std::cout << "std::find over " << n << " ints: list " << ms(t4 - t3) << " ms, vector " << ms(t5 - t4) << " ms"
              << (f1 == big.end() && f2 == vec.end() ? " (both scanned everything)" : "") << '\n';
    return 0;
}
