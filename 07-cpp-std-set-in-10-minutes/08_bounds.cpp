// std::set in 10 Minutes - slide 8: ordered queries with lower_bound and upper_bound
// Build: make 08_bounds
//
// After the slide's lines, a measurement: the member s.lower_bound walks the tree in O(log n);
// the free std::lower_bound only has bidirectional iterators here and degrades to O(n).
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <set>

static void use(int x) { std::cout << x << ' '; }

int main() {
    std::set<int> s{10, 20, 30, 40, 50};

    auto lo = s.lower_bound(25);  // first key >= 25: 30, O(log n)
    auto hi = s.upper_bound(40);  // first key >  40: 50, O(log n)
    std::cout << "lower_bound(25) = " << *lo << ", upper_bound(40) = " << *hi << '\n';
    std::cout << "keys in [25, 40]: ";
    for (auto it = lo; it != hi; ++it) use(*it);  // 30, 40: O(log n + k)
    std::cout << '\n';

    auto [a, b] = s.equal_range(30);  // [30, 40): at most one key
    std::cout << "equal_range(30) = [" << *a << ", " << *b << ")\n";

    auto below = std::prev(s.lower_bound(25));  // largest key < 25: 20
    std::cout << "largest key below 25: " << *below << '\n';
    // use s.lower_bound, never std::lower_bound: that one is O(n) here

    // measurement: 100 queries near the top of 100,000 keys
    using clock = std::chrono::steady_clock;
    std::set<long long> big;
    for (long long i = 0; i < 100'000; ++i) big.insert(big.end(), i * 2);

    const int queries = 100;
    long long checksum = 0;
    auto t0 = clock::now();
    for (int q = 0; q < queries; ++q)
        checksum += *big.lower_bound(199'000 - q);              // member: O(log n)
    auto t1 = clock::now();
    for (int q = 0; q < queries; ++q)
        checksum -= *std::lower_bound(big.begin(), big.end(), 199'000 - q);  // free: O(n)
    auto t2 = clock::now();

    auto ms = [](auto x, auto y) { return std::chrono::duration<double, std::milli>(y - x).count(); };
    std::cout << "\n" << queries << " queries on " << big.size() << " keys\n";
    std::cout << "  s.lower_bound(x):   " << ms(t0, t1) << " ms\n";
    std::cout << "  std::lower_bound(): " << ms(t1, t2) << " ms  (linear: one step per key)\n";
    std::cout << "  same answers: " << (checksum == 0 ? "yes" : "no") << '\n';
    return 0;
}
