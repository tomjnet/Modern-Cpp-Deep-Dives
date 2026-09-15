// std::mdspan (C++23) - a non-owning multidimensional view over contiguous memory
//   construct / element access m[i, j]   O(1): index arithmetic, no copy
//   the layout (row-major by default, column-major, strided) is a compile-time policy
//   iteration order matters: walking rows of a row-major view is sequential memory, walking columns is not
//
// Without <mdspan> the same view is written by hand: an (pointer, rows, cols) triple with i * cols + j.
#include "bigo.h"
#include <cstdio>
#include <vector>
#include <version>

#if defined(__cpp_lib_mdspan)
#include <mdspan>
using View = std::mdspan<int, std::dextents<std::size_t, 2>>;
static View view(std::vector<int>& v, std::size_t rows, std::size_t cols) { return View(v.data(), rows, cols); }
static int& at(View& m, std::size_t i, std::size_t j) { return m[i, j]; }
static const char* impl = "std::mdspan (library)";
#else
struct View { int* p; std::size_t rows, cols; std::size_t extent(int d) const { return d == 0 ? rows : cols; } };
static View view(std::vector<int>& v, std::size_t rows, std::size_t cols) { return View{v.data(), rows, cols}; }
static int& at(View& m, std::size_t i, std::size_t j) { return m.p[i * m.cols + j]; }
static const char* impl = "hand-rolled row-major view (no <mdspan> in this standard library)";
#endif

int main() {
    std::printf("std::mdspan\n2-D view over one contiguous block: access is O(1) arithmetic, the walk order decides the speed\n");
    std::printf("implementation: %s\n\n", impl);

    const std::size_t n = 2000;                   // 2000 x 2000 ints = 16 MB, bigger than the caches
    std::vector<int> storage(n * n, 1);
    View m = view(storage, n, n);

    std::printf("m[3, 4] = %d, extents %zu x %zu, sizeof(view) = %zu bytes\n", at(m, 3, 4), m.extent(0), m.extent(1), sizeof(View));

    const int reps = 3;
    double row_major = bigo::ms([&] {
        for (int r = 0; r < reps; ++r) { std::size_t s = 0; for (std::size_t i = 0; i < n; ++i) for (std::size_t j = 0; j < n; ++j) s += std::size_t(at(m, i, j)); bigo::sink = bigo::sink + s; }
    });
    double col_major = bigo::ms([&] {
        for (int r = 0; r < reps; ++r) { std::size_t s = 0; for (std::size_t j = 0; j < n; ++j) for (std::size_t i = 0; i < n; ++i) s += std::size_t(at(m, i, j)); bigo::sink = bigo::sink + s; }
    });
    std::printf("\nsum of %zu elements, both O(n):\n  rows outer, cols inner (sequential memory) %.1f ms\n"
                "  cols outer, rows inner (stride %zu ints)     %.1f ms  -> %.1fx slower for the same Big-O\n",
                n * n, row_major, n, col_major, col_major / (row_major > 0 ? row_major : 1e-9));
    return 0;
}
