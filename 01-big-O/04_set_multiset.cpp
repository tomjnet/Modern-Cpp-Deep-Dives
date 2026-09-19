// std::set / std::multiset (C++98) - ordered, red-black tree, one node per element
//   insert / find / erase(key)   O(log n)        lower_bound / upper_bound   O(log n)
//   in-order iteration           O(n)            multiset: count(key) O(log n + k), equal_range O(log n)
//   space: n * (sizeof(T) + 3 pointers + colour) in separate nodes
#include "bigo.h"
#include <set>

int main() {
    bigo::header("std::set / std::multiset", "balanced tree: every keyed operation is O(log n), iteration is sorted");

    auto make = [](std::size_t n) { std::set<int> s; for (std::size_t i = 0; i < n; ++i) s.insert(int(i * 2)); return s; };

    bigo::scale("find(key)", "O(log n)", make, [](std::set<int>& s) { return std::size_t(s.find(int(s.size())) != s.end()); });
    bigo::scale("insert + erase(key)", "O(log n)", make, [](std::set<int>& s) { s.insert(-1); s.erase(-1); return s.size(); });
    bigo::scale("lower_bound", "O(log n)", make, [](std::set<int>& s) { return std::size_t(*s.lower_bound(int(s.size()))); });
    bigo::scale("in-order iteration", "O(n)", make, [](std::set<int>& s) { std::size_t c = 0; for (int x : s) c += std::size_t(x); return c; },
                20'000, 20);

    auto make_multi = [](std::size_t n) { std::multiset<int> m; for (std::size_t i = 0; i < n; ++i) m.insert(int(i % 100)); return m; };
    // count is O(log n + k) with k = matches; here k = n/100 grows 10x with n, so the row behaves like O(n)
    bigo::scale("multiset count, k = n/100", "O(n)", make_multi, [](std::multiset<int>& m) { return m.count(42); }, 20'000, 20);
    return 0;
}
