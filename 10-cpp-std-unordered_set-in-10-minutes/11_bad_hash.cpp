// std::unordered_set in 10 Minutes - slide 11: bad hashes and the worst case
// Build: make 11_bad_hash
#include <chrono>
#include <cstddef>
#include <iostream>
#include <unordered_set>

struct BadHash {                       // every key -> bucket 0
    std::size_t operator()(int) const noexcept { return 0; }
};

template <class Set>
static double time_lookups(const Set& s, int n) {
    auto t0 = std::chrono::steady_clock::now();
    long long hits = 0;
    for (int i = 0; i < n; ++i) hits += s.contains(i) ? 1 : 0;
    auto t1 = std::chrono::steady_clock::now();
    if (hits != n) std::cout << "unexpected miss\n";
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

int main() {
    std::unordered_set<int, BadHash> worst{1, 2, 3, 4, 5};
    worst.find(5);          // walks one chain of n nodes: O(n)

    std::unordered_set<int> good{1, 2, 3, 4, 5};
    good.find(5);           // std::hash<int> spreads keys: O(1)

    // worst case of every operation is O(n): a bad hash or an
    // attacker who crafts colliding keys turns the set into a list
    std::cout << "worst: bucket_size(0) = " << worst.bucket_size(0) << " of " << worst.size() << " keys\n";
    std::cout << "good:  bucket_size(bucket(5)) = " << good.bucket_size(good.bucket(5)) << '\n';

    // measure: n keys, n lookups; the constant hash walks one chain of n nodes per lookup
    const int n = 10000;
    std::unordered_set<int, BadHash> w;
    std::unordered_set<int> g;
    for (int i = 0; i < n; ++i) { w.insert(i); g.insert(i); }
    std::cout << n << " lookups, BadHash:        " << time_lookups(w, n) << " ms (one chain of "
              << w.bucket_size(0) << ")\n";
    std::cout << n << " lookups, std::hash<int>: " << time_lookups(g, n) << " ms\n";
    return 0;
}
