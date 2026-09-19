// std::multiset, std::multimap, equal_range in 10 Minutes - slide 6: equal_range: the group in one call
// Build: make 06_equal_range
#include <iostream>
#include <iterator>
#include <set>

static void use(int x) { std::cout << ' ' << x; }

int main() {
    std::multiset<int> ms{1, 3, 5, 5, 5, 9};
    auto [lo, hi] = ms.equal_range(5);         // O(log n): one descent
    // lo == lower_bound(5): first element >= 5
    // hi == upper_bound(5): first element  > 5
    std::cout << "equal_range(5):";
    for (auto it = lo; it != hi; ++it) use(*it);   // the three 5s: O(k)
    std::cout << '\n';
    auto [a, b] = ms.equal_range(4);           // a == b: empty range, no 4
    std::size_t k = std::distance(lo, hi);     // 3, O(k): no random access
    // equal_range beats lower_bound + upper_bound: one search, not two

    std::cout << std::boolalpha;
    std::cout << "lo == lower_bound(5): " << (lo == ms.lower_bound(5)) << '\n';
    std::cout << "hi == upper_bound(5): " << (hi == ms.upper_bound(5)) << ", *hi = " << *hi << '\n';
    std::cout << "equal_range(4) is empty: " << (a == b) << ", both point at " << *a
              << " (where a 4 would be inserted)\n";
    std::cout << "std::distance(lo, hi) = " << k << '\n';
    return 0;
}
