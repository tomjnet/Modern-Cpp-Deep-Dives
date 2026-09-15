// std::vector (C++98) - contiguous dynamic array, the default container
//   index / front / back   O(1)          push_back  amortized O(1) (O(n) on reallocation)
//   insert / erase middle  O(n)          find       O(n), sorted + binary_search O(log n)
//   space: n * sizeof(T) + spare capacity, object = 3 pointers
#include "bigo.h"
#include <algorithm>
#include <vector>

int main() {
    bigo::header("std::vector", "contiguous block, three pointers; indexing is arithmetic, middle insert shifts");

    auto make = [](std::size_t n) { std::vector<int> v(n); for (std::size_t i = 0; i < n; ++i) v[i] = int(i); return v; };

    bigo::scale("v[i]", "O(1)", make, [](std::vector<int>& v) { return std::size_t(v[v.size() / 2]); });
    bigo::scale("push_back + pop_back", "O(1)", make, [](std::vector<int>& v) { v.push_back(1); v.pop_back(); return v.size(); });
    bigo::scale("insert + erase at begin()", "O(n)", make, [](std::vector<int>& v) { v.insert(v.begin(), 1); v.erase(v.begin()); return v.size(); });
    bigo::scale("insert + erase in middle", "O(n)", make,
                [](std::vector<int>& v) { auto mid = v.begin() + std::ptrdiff_t(v.size() / 2); v.erase(v.insert(mid, 1)); return v.size(); });
    bigo::scale("std::find (unsorted)", "O(n)", make,
                [](std::vector<int>& v) { return std::size_t(std::find(v.begin(), v.end(), -1) - v.begin()); });
    bigo::scale("binary_search (sorted)", "O(log n)", make,
                [](std::vector<int>& v) { return std::size_t(std::binary_search(v.begin(), v.end(), int(v.size() - 1))); });
    bigo::scale("range-for sum", "O(n)", make, [](std::vector<int>& v) { std::size_t s = 0; for (int x : v) s += x; return s; });
    return 0;
}
