// C Array and std::array in 10 Minutes - slide 11: passing arrays around: std::span
// Build: make 11_span
#include <array>
#include <cstddef>
#include <iostream>
#include <span>
#include <vector>

void sum(std::span<const int> s) {             // one function for every contiguous int range
    long long total = 0;
    for (int x : s) total += x;
    std::cout << "  sum of " << s.size() << " ints = " << total << '\n';
}

void old_api(const int* p, std::size_t n) {    // the C shape: pointer and count
    std::cout << "  old_api got " << n << " ints starting at " << p[0] << '\n';
}

int main() {
    void sum(std::span<const int> s);   // C++20: pointer + size, 16 B
    int c[8] = {};
    std::array<int, 8> a = {};
    std::vector<int> v(8);
    for (int i = 0; i < 8; ++i) { c[i] = i; a[static_cast<std::size_t>(i)] = i; v[static_cast<std::size_t>(i)] = i; }
    std::cout << "c, a and v hold 0..7; sum takes all three:\n";
    sum(c);                             // no decay: N read from the type
    sum(a);                             // same function, same cost
    sum(v);                             // and the vector too
    sum({a.data() + 2, 4});             // a window: a[2] to a[5], O(1)
    void old_api(const int* p, std::size_t n);
    old_api(a.data(), a.size());        // the C interface is still there

    std::cout << "sizeof(std::span<const int>) = " << sizeof(std::span<const int>) << " B (a pointer and a size)\n";
    std::span<int, 8> fixed = a;        // a static extent: the size is in the type again
    std::cout << "sizeof(std::span<int, 8>) = " << sizeof(fixed) << " B (a pointer only, N is a constant)\n";
    return 0;
}
