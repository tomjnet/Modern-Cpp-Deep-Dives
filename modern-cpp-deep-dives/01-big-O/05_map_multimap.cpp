// std::map / std::multimap (C++98) - ordered key -> value, red-black tree
//   operator[] / find / insert / erase(key)   O(log n)      iteration in key order   O(n)
//   emplace_hint with a correct hint          amortized O(1)
//   space: one node per pair, key and value stored together in the node
#include "bigo.h"
#include <map>
#include <string>

int main() {
    bigo::header("std::map / std::multimap", "tree keyed by comparison: O(log n) everywhere, keys stay sorted");

    auto make = [](std::size_t n) { std::map<int, int> m; for (std::size_t i = 0; i < n; ++i) m[int(i)] = int(i); return m; };

    bigo::scale("m[key] lookup", "O(log n)", make, [](std::map<int, int>& m) { return std::size_t(m[int(m.size() / 2)]); });
    bigo::scale("find(key)", "O(log n)", make, [](std::map<int, int>& m) { return std::size_t(m.find(7) != m.end()); });
    bigo::scale("insert + erase(key)", "O(log n)", make, [](std::map<int, int>& m) { m.emplace(-1, 0); m.erase(-1); return m.size(); });
    bigo::scale("emplace_hint(end())", "O(1)", make,
                [](std::map<int, int>& m) { int k = int(m.size()); m.emplace_hint(m.end(), k, k); m.erase(k); return m.size(); });
    bigo::scale("iteration", "O(n)", make,
                [](std::map<int, int>& m) { std::size_t s = 0; for (auto& [k, v] : m) s += std::size_t(v); return s; }, 20'000, 20);

    // string keys: every comparison costs O(common prefix), so the log n steps get more expensive
    auto make_str = [](std::size_t n) { std::map<std::string, int> m; for (std::size_t i = 0; i < n; ++i) m["key-" + std::to_string(i)] = 1; return m; };
    bigo::scale("string key find", "O(log n)", make_str, [](std::map<std::string, int>& m) { return std::size_t(m.find("key-1") != m.end()); });
    return 0;
}
