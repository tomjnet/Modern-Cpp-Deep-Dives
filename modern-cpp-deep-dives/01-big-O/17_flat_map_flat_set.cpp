// std::flat_map / std::flat_set (C++23) - sorted vectors behind a map / set interface
//   find / lower_bound   O(log n) binary search on contiguous memory (fewer cache misses than a tree)
//   insert / erase       O(n): elements after the position shift, like vector
//   iteration            O(n), sorted, and fast: no pointer chasing
//   space: two vectors (keys, values), no per-element nodes; bulk build from sorted input is O(n)
//
// If the standard library does not ship <flat_map> yet, the same structure is built by hand below:
// a sorted vector of pairs plus lower_bound is exactly what flat_map is.
#include "bigo.h"
#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>
#include <version>

#if defined(__cpp_lib_flat_map)
#include <flat_map>
#include <flat_set>
using Map = std::flat_map<int, int>;
static const char* impl = "std::flat_map (library)";
#else
struct Map {                                     // minimal stand-in with the same complexity
    std::vector<std::pair<int, int>> kv;         // kept sorted by key
    std::size_t size() const { return kv.size(); }
    auto lower_bound(int k) { return std::lower_bound(kv.begin(), kv.end(), k, [](auto& p, int key) { return p.first < key; }); }
    auto find(int k) { auto it = lower_bound(k); return (it != kv.end() && it->first == k) ? it : kv.end(); }
    auto end() { return kv.end(); }
    void emplace(int k, int v) { auto it = lower_bound(k); if (it == kv.end() || it->first != k) kv.insert(it, {k, v}); }
    void erase(int k) { auto it = find(k); if (it != kv.end()) kv.erase(it); }
};
static const char* impl = "hand-rolled sorted vector (no <flat_map> in this standard library)";
#endif

int main() {
    bigo::header("std::flat_map / std::flat_set", "sorted vector: O(log n) lookup with cache-friendly memory, O(n) insert");
    std::printf("implementation: %s\n\n", impl);

    auto make = [](std::size_t n) { Map m; for (std::size_t i = 0; i < n; ++i) m.emplace(int(n - 1 - i) * 2, int(i)); return m; };
    // (inserting in descending order is the worst case for a flat map: every insert shifts everything; a real
    //  program builds from sorted input or with insert(sorted_unique, ...) in O(n))

    bigo::scale("find(key)", "O(log n)", make, [](Map& m) { return std::size_t(m.find(int(m.size())) != m.end()); });
    bigo::scale("lower_bound", "O(log n)", make, [](Map& m) { return std::size_t(m.lower_bound(int(m.size())) != m.end()); });
    bigo::scale("emplace(front) + erase", "O(n)", make, [](Map& m) { m.emplace(-1, 0); m.erase(-1); return m.size(); });
    bigo::scale("emplace(back) + erase", "O(log n)", make, [](Map& m) { int k = int(m.size()) * 4; m.emplace(k, 0); m.erase(k); return m.size(); });
    return 0;
}
