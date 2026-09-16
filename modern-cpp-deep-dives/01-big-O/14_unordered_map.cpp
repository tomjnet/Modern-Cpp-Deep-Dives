// std::unordered_map / unordered_multimap (C++11) - hash table of key -> value
//   operator[] / find / insert / erase(key)   average O(1), worst O(n)
//   hashing a string key costs O(length): the "constant" includes the key size
//   space: one node per pair plus the bucket array; reserve(n) avoids rehashes during a fill
#include "bigo.h"
#include <cstdio>
#include <string>
#include <unordered_map>

int main() {
    bigo::header("std::unordered_map", "hash table keyed by hash(key): average O(1), the key size is inside the constant");

    auto make = [](std::size_t n) { std::unordered_map<int, int> m; for (std::size_t i = 0; i < n; ++i) m[int(i)] = int(i); return m; };

    bigo::scale("m[key] lookup", "O(1)", make, [](std::unordered_map<int, int>& m) { return std::size_t(m[int(m.size() / 2)]); });
    bigo::scale("find(key) miss", "O(1)", make, [](std::unordered_map<int, int>& m) { return std::size_t(m.find(-1) != m.end()); });
    bigo::scale("insert + erase(key)", "O(1)", make, [](std::unordered_map<int, int>& m) { m.emplace(-1, 0); m.erase(-1); return m.size(); });
    bigo::scale("iteration", "O(n)", make,
                [](std::unordered_map<int, int>& m) { std::size_t s = 0; for (auto& [k, v] : m) s += std::size_t(v); return s; }, 20'000, 20);

    // string keys: same O(1) in n, but every lookup pays O(len) to hash and O(len) to compare on a hit
    auto make_str = [](std::size_t n) { std::unordered_map<std::string, int> m; for (std::size_t i = 0; i < n; ++i) m["key-" + std::to_string(i)] = 1; return m; };
    bigo::scale("string key find", "O(1)", make_str, [](std::unordered_map<std::string, int>& m) { return std::size_t(m.find("key-1") != m.end()); });

    // fill with and without reserve: the same n inserts, minus the rehashes
    auto empty = [](std::size_t n) { return n; };
    bigo::scale("fill n (no reserve)", "O(n)", empty,
                [](std::size_t n) { std::unordered_map<int, int> m; for (std::size_t i = 0; i < n; ++i) m[int(i)] = 1; return m.size(); }, 20'000, 3);
    bigo::scale("fill n (reserve first)", "O(n)", empty,
                [](std::size_t n) { std::unordered_map<int, int> m; m.reserve(n); for (std::size_t i = 0; i < n; ++i) m[int(i)] = 1; return m.size(); }, 20'000, 3);
    return 0;
}
