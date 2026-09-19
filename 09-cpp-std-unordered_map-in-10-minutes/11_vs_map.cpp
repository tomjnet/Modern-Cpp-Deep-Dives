// std::unordered_map in 10 Minutes - slide 11: unordered_map vs std::map
// Build: make 11_vs_map
#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

int main() {
    std::map<std::string, int> tree;            // red-black tree, sorted
    std::unordered_map<std::string, int> hash;  // buckets, no order

    tree.find("k");   // O(log n): ~20 string compares for a million keys
    hash.find("k");   // O(1) avg: one hash, one bucket, ~1 compare

    tree.lower_bound("k");  // range queries, ordered walk: map only
    // hash: no order, no lower_bound, needs std::hash for the key type
    // hash: more memory per node and O(n) rehash pauses

    const int n = 200000;
    for (int i = 0; i < n; ++i) {
        std::string key = "key" + std::to_string(static_cast<long long>(i) * 7919 % n);   // scrambled order
        tree.emplace(key, i);
        hash.emplace(key, i);
    }
    using clock = std::chrono::steady_clock;
    long long sum = 0;
    auto t0 = clock::now();
    for (int i = 0; i < n; ++i) sum += tree.find("key" + std::to_string(i))->second;
    auto t1 = clock::now();
    for (int i = 0; i < n; ++i) sum += hash.find("key" + std::to_string(i))->second;
    auto t2 = clock::now();
    auto ms = [](auto a, auto b) { return std::chrono::duration<double, std::milli>(b - a).count(); };
    std::cout << n << " lookups (checksum " << sum << ")\n"
              << "  std::map       " << ms(t0, t1) << " ms  (O(log n) string compares)\n"
              << "  unordered_map  " << ms(t1, t2) << " ms  (one hash, about one compare)\n";

    std::cout << "ordered walk, map only: three keys from lower_bound(\"key1000\"):";
    int shown = 0;
    for (auto it = tree.lower_bound("key1000"); it != tree.end() && shown < 3; ++it, ++shown) std::cout << ' ' << it->first;
    std::cout << "\nunordered_map begin() is whatever bucket comes first: " << hash.begin()->first << '\n';
    return 0;
}
