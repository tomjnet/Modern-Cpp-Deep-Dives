// C Array and std::array in 10 Minutes - slide 12: two dimensions and c interop
// Build: make 12_multi_interop
#include <array>
#include <cstdint>
#include <iostream>

// A real C API lives in another translation unit and sees only a pointer; NOINLINE keeps it
// that way here, so the optimizer cannot fold the call and second-guess the pointer's origin.
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif

NOINLINE void c_api(int* p, int rows, int cols) {   // a C function: one pointer, row major
    long long total = 0;
    for (int i = 0; i < rows * cols; ++i) total += p[i];
    std::cout << "  c_api saw " << rows << "x" << cols << " ints, sum = " << total
              << ", p[1 * cols + 2] = " << p[1 * cols + 2] << '\n';
}

int main() {
    int m[3][4] = {};                          // 48 B, row major, one block
    std::array<std::array<int, 4>, 3> g = {};  // identical bytes
    m[1][2] = 5;                               // base + (1 * 4 + 2) * 4
    g[1][2] = 5;                               // same address arithmetic
    static_assert(sizeof(g) == sizeof(m));     // 48 == 48
    void c_api(int* p, int rows, int cols);
    c_api(&m[0][0], 3, 4);                     // contiguous: fine
    c_api(g[0].data(), 3, 4);                  // contiguous too: fine

    auto mb = reinterpret_cast<std::uintptr_t>(&m[0][0]);
    auto gb = reinterpret_cast<std::uintptr_t>(g[0].data());
    std::cout << "sizeof(m) = " << sizeof(m) << " B, sizeof(g) = " << sizeof(g) << " B\n";
    std::cout << "&m[1][2] - &m[0][0] = " << reinterpret_cast<std::uintptr_t>(&m[1][2]) - mb
              << " B = (1 * 4 + 2) * " << sizeof(int) << '\n';
    std::cout << "&g[1][2] - &g[0][0] = " << reinterpret_cast<std::uintptr_t>(&g[1][2]) - gb
              << " B: the same arithmetic\n";
    std::cout << "row 1 starts " << reinterpret_cast<std::uintptr_t>(g[1].data()) - gb
              << " B after row 0 in the nested std::array: no padding between rows\n";

    std::array<std::array<int, 4>, 3> copy = g;       // a nested std::array copies and compares
    std::cout << "copy == g: " << (copy == g ? "true" : "false") << " (a C matrix cannot do this)\n";
    return 0;
}
