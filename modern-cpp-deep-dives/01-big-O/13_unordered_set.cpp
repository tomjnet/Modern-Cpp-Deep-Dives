// std::unordered_set / unordered_multiset (C++11) - hash table with separate chaining
//   insert / find / erase(key)   average O(1), worst O(n) (all keys in one bucket)
//   iteration                    O(n + buckets), in no particular order
//   rehash when load_factor > max_load_factor: O(n), invalidates iterators (not references)
//   space: n nodes + bucket array; the cost of the key is the cost of hash(key) plus compares on collision
#include "bigo.h"
#include <cstdio>
#include <unordered_set>

int main() {
    bigo::header("std::unordered_set", "hash table: average O(1) per key, order undefined, rehash is O(n)");

    auto make = [](std::size_t n) { std::unordered_set<int> s; for (std::size_t i = 0; i < n; ++i) s.insert(int(i)); return s; };

    bigo::scale("find(key) hit", "O(1)", make, [](std::unordered_set<int>& s) { return std::size_t(s.find(int(s.size() / 2)) != s.end()); });
    bigo::scale("find(key) miss", "O(1)", make, [](std::unordered_set<int>& s) { return std::size_t(s.find(-1) != s.end()); });
    bigo::scale("insert + erase(key)", "O(1)", make, [](std::unordered_set<int>& s) { s.insert(-1); s.erase(-1); return s.size(); });
    bigo::scale("iteration", "O(n)", make,
                [](std::unordered_set<int>& s) { std::size_t c = 0; for (int x : s) c += std::size_t(x); return c; }, 20'000, 20);
    // grow the bucket array, then let rehash(0) shrink it back, so repeated calls keep the same size
    bigo::scale("rehash up + rehash back", "O(n)", make,
                [](std::unordered_set<int>& s) { s.rehash(s.bucket_count() * 2); s.rehash(0); return s.bucket_count(); }, 20'000, 2);

    std::unordered_set<int> s = make(200'000);
    std::printf("\n200000 keys: buckets %zu, load_factor %.2f, max_load_factor %.2f\n", s.bucket_count(), s.load_factor(),
                s.max_load_factor());
    return 0;
}
