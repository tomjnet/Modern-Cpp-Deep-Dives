// std::multiset, std::multimap, equal_range in 10 Minutes - slide 7: count, contains, find and the bounds
// Build: make 07_count_find
#include <chrono>
#include <iostream>
#include <set>

template <class F>
static double ms(F&& f) {
    auto t0 = std::chrono::steady_clock::now();
    f();
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
}

int main() {
    std::multiset<int> ms{1, 3, 5, 5, 5, 9};
    std::size_t c = ms.count(5);       // 3: O(log n + k), walks the group
    bool has = ms.contains(5);         // C++20: O(log n), stops at one
    auto any = ms.find(5);             // O(log n): SOME 5, the standard
                                       // does not promise the first one
    auto first = ms.lower_bound(5);    // the first 5, guaranteed
    auto after = ms.upper_bound(5);    // the 9: first element > 5
    // count is the trap: with a million equal keys it walks a million
    // nodes. Ask contains() when the answer you need is yes or no.

    std::cout << std::boolalpha;
    std::cout << "count(5) = " << c << ", contains(5) = " << has << '\n';
    std::cout << "find(5) -> " << *any << ", lower_bound(5) -> " << *first
              << ", upper_bound(5) -> " << *after << '\n';
    std::cout << "find(5) == lower_bound(5) here: " << (any == first)
              << " (true in libstdc++ and MSVC, but not guaranteed)\n";

    // the trap, measured: count walks every copy, contains stops at the first one
    const int copies = 200000;
    std::multiset<int> big;
    for (int i = 0; i < copies; ++i) big.insert(big.end(), 7);
    std::size_t seen = 0;
    bool found = false;
    double t_count = ::ms([&] { seen = big.count(7); });
    double t_contains = ::ms([&] { found = big.contains(7); });
    std::cout << "count(7) over " << seen << " copies: " << t_count << " ms\n";
    std::cout << "contains(7): " << found << " in " << t_contains << " ms\n";
    return 0;
}
