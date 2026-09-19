// std::valarray (C++98) - contiguous numeric array with element-wise operators
//   index            O(1)        whole-array arithmetic (a + b, a * 2, apply)   O(n), vectorizable
//   sum / min / max  O(n)        slices and masks build views without copying   O(1) to create
//   space: n * sizeof(T) contiguous, like vector but no push_back
#include "bigo.h"
#include <valarray>

int main() {
    bigo::header("std::valarray", "contiguous numbers with element-wise math: everything whole-array is O(n)");

    auto make = [](std::size_t n) { std::valarray<double> a(1.0, n); return a; };

    bigo::scale("a[i]", "O(1)", make, [](std::valarray<double>& a) { return std::size_t(a[a.size() / 2]); });
    bigo::scale("a.sum()", "O(n)", make, [](std::valarray<double>& a) { return std::size_t(a.sum()); });
    bigo::scale("a *= 1.0001 (in place)", "O(n)", make, [](std::valarray<double>& a) { a *= 1.0001; return a.size(); });
    // b = a + a allocates a fresh array every time: past the allocator's large-block threshold each call is an OS
    // request plus page faults, so the ratio comes out far above 10 even though the arithmetic itself is O(n)
    bigo::scale("b = a + a (allocates)", "O(n)", make, [](std::valarray<double>& a) { std::valarray<double> b = a + a; return b.size(); }, 20'000, 50);
    bigo::scale("b = a + a (preallocated)", "O(n)", make,
                [](std::valarray<double>& a) { static std::valarray<double> b; if (b.size() != a.size()) b.resize(a.size()); b = a + a; return b.size(); }, 20'000, 50);
    bigo::scale("slice view a[slice]", "O(1)", make,
                [](std::valarray<double>& a) { std::slice_array<double> s = a[std::slice(0, 4, 1)]; return std::size_t(std::valarray<double>(s)[0]); });
    return 0;
}
