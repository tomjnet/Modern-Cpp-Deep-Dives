// std::span (C++20) - a non-owning (pointer, count) view over contiguous memory of any T
//   construct from array / vector / pointer+size     O(1)      subspan / first / last   O(1)
//   s[i]                                             O(1)      iteration                O(n)
//   space: 2 words (1 for a fixed-extent span); works for C arrays, std::array, vector, string, inplace_vector
#include "bigo.h"
#include <array>
#include <cstdio>
#include <span>
#include <vector>

static std::size_t sum(std::span<const int> s) {   // one function for every contiguous container
    std::size_t t = 0;
    for (int x : s) t += std::size_t(x);
    return t;
}

int main() {
    bigo::header("std::span", "view over contiguous memory: slicing O(1), the algorithm on top decides the rest");

    auto make = [](std::size_t n) { std::vector<int> v(n); for (std::size_t i = 0; i < n; ++i) v[i] = int(i); return v; };

    bigo::scale("span::subspan(n/4, n/2)", "O(1)", make,
                [](std::vector<int>& v) { std::span<int> s = v; return s.subspan(v.size() / 4, v.size() / 2).size(); });
    bigo::scale("vector copy of that range", "O(n)", make,
                [](std::vector<int>& v) { std::vector<int> c(v.begin() + std::ptrdiff_t(v.size() / 4), v.begin() + std::ptrdiff_t(3 * v.size() / 4)); return c.size(); }, 20'000, 50);
    bigo::scale("s[i]", "O(1)", make, [](std::vector<int>& v) { std::span<int> s = v; return std::size_t(s[s.size() / 2]); });
    bigo::scale("sum(span) over vector", "O(n)", make, [](std::vector<int>& v) { return sum(v); });

    int c_array[4] = {1, 2, 3, 4};
    std::array<int, 3> std_array{5, 6, 7};
    std::vector<int> vec{8, 9};
    std::printf("\nsum over C array %zu, std::array %zu, vector %zu: same function, no copies; sizeof(span<int>) = %zu\n",
                sum(c_array), sum(std_array), sum(vec), sizeof(std::span<int>));
    return 0;
}
