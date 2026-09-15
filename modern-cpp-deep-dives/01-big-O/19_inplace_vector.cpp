// std::inplace_vector<T, N> (C++26) - vector interface, storage inside the object, capacity fixed at N
//   index / push_back / pop_back   O(1) (push_back never reallocates: it throws bad_alloc when full)
//   insert / erase middle          O(n)      try_push_back / unchecked_push_back for no-throw code
//   space: N * sizeof(T) + a size field, no heap at all; ideal for embedded and hot stack buffers
//
// Without <inplace_vector> the same shape is a std::array plus a count, written by hand below.
#include "bigo.h"
#include <cstdio>
#include <version>

#if defined(__cpp_lib_inplace_vector)
#include <inplace_vector>
template <std::size_t N> using Buf = std::inplace_vector<int, N>;
static const char* impl = "std::inplace_vector (library)";
#else
#include <array>
#include <cstddef>
template <std::size_t N>
struct Buf {                                    // minimal stand-in: fixed storage + count
    std::array<int, N> data{};
    std::size_t n = 0;
    std::size_t size() const { return n; }
    static constexpr std::size_t capacity() { return N; }
    void push_back(int x) { data[n++] = x; }
    void pop_back() { --n; }
    int& operator[](std::size_t i) { return data[i]; }
    int& back() { return data[n - 1]; }
};
static const char* impl = "hand-rolled array + count (no <inplace_vector> in this standard library)";
#endif

int main() {
    std::printf("std::inplace_vector<T, N>\nvector operations without a heap: the object holds the storage\n");
    std::printf("implementation: %s\n\n", impl);

    Buf<8> small;
    for (int i = 0; i < 5; ++i) small.push_back(i * 10);
    std::printf("size %zu of capacity %zu, sizeof = %zu bytes (8 ints + size), back = %d, no allocation happened\n",
                small.size(), small.capacity(), sizeof(small), small.back());

    // push/pop cost does not depend on N: the storage is already there. One slot is left free, because
    // push_back on a full inplace_vector throws std::bad_alloc (use try_push_back for a no-throw variant).
    static Buf<20'000> a;   static Buf<200'000> b;   // ~80 KB and ~800 KB: static, they would not fit a small stack
    for (std::size_t i = 0; i + 1 < a.capacity(); ++i) a.push_back(int(i));
    for (std::size_t i = 0; i + 1 < b.capacity(); ++i) b.push_back(int(i));
    const int reps = 20'000;
    double ta = bigo::ms([&] { for (int r = 0; r < reps; ++r) { a.push_back(1); a.pop_back(); bigo::sink = bigo::sink + a.size(); } });
    double tb = bigo::ms([&] { for (int r = 0; r < reps; ++r) { b.push_back(1); b.pop_back(); bigo::sink = bigo::sink + b.size(); } });
    std::printf("\npush_back + pop_back x %d: N=20000 %.3f ms, N=200000 %.3f ms, ratio %.1f (expected ~1, O(1))\n",
                reps, ta, tb, tb / (ta > 0 ? ta : 1e-9));
    double ia = bigo::ms([&] { for (int r = 0; r < reps; ++r) bigo::sink = bigo::sink + std::size_t(a[a.size() / 2]); });
    double ib = bigo::ms([&] { for (int r = 0; r < reps; ++r) bigo::sink = bigo::sink + std::size_t(b[b.size() / 2]); });
    std::printf("v[i]                x %d: N=20000 %.3f ms, N=200000 %.3f ms, ratio %.1f (expected ~1, O(1))\n",
                reps, ia, ib, ib / (ia > 0 ? ia : 1e-9));
    return 0;
}
