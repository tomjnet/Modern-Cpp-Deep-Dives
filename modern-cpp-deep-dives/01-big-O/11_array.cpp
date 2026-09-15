// std::array<T, N> (C++11) - fixed-size contiguous array, size known at compile time, no heap
//   index / front / back   O(1)      fill    O(N)      swap    O(N) (it swaps every element, unlike vector)
//   no insert / erase / push_back: the size is part of the type
//   space: exactly N * sizeof(T), no pointers, no capacity; lives wherever you declare it (stack, member)
#include "bigo.h"
#include <algorithm>
#include <array>
#include <cstdio>

// static: an 800 KB array would overflow a 1 MB default stack (MSVC), so big std::arrays live in static or heap storage
template <std::size_t N>
std::array<int, N>& make_array() { static std::array<int, N> a{}; for (std::size_t i = 0; i < N; ++i) a[i] = int(i); return a; }

int main() {
    std::printf("std::array<T, N>\ncompile-time size, zero overhead: sizeof(array<int, 8>) = %zu = 8 * sizeof(int)\n\n",
                sizeof(std::array<int, 8>));

    // the sizes are template arguments, so the two containers are two different types
    auto& a1 = make_array<20'000>();
    auto& a2 = make_array<200'000>();
    auto row = [&](const char* name, const char* big_o, auto op) {
        bigo::sink = bigo::sink + op(a1) + op(a2);                       // warm-up
        int reps = 200;                                                  // calibrated on the small array, like bigo::scale
        double t1;
        for (;;) { t1 = bigo::ms([&] { for (int r = 0; r < reps; ++r) bigo::sink = bigo::sink + op(a1); }); if (t1 >= 1.0 || reps >= 20'000) break; reps *= 10; }
        double t2 = bigo::ms([&] { for (int r = 0; r < reps; ++r) bigo::sink = bigo::sink + op(a2); });
        std::printf("%-26s %10.3f ms %10.3f ms %8.1f   %-10s ratio %s\n", name, t1, t2, t2 / (t1 > 0 ? t1 : 1e-9),
                    big_o, bigo::expected_ratio(big_o));
    };
    std::printf("%-26s %13s %13s %8s   %s\n", "operation", "N=20000", "N=200000", "ratio", "expected");
    row("a[i]", "O(1)", [](auto& a) { return std::size_t(a[a.size() / 2]); });
    row("a.fill(7)", "O(n)", [](auto& a) { a.fill(7); return a.size(); });
    row("std::find (miss)", "O(n)", [](auto& a) { return std::size_t(std::find(a.begin(), a.end(), -1) - a.begin()); });
    row("range-for sum", "O(n)", [](auto& a) { std::size_t s = 0; for (int x : a) s += std::size_t(x); return s; });
    return 0;
}
