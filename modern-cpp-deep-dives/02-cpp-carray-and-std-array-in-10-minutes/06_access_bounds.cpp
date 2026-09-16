// C Array and std::array in 10 Minutes - slide 6: access and bounds
// Build: make 06_access_bounds
#include <array>
#include <cstdint>
#include <iostream>
#include <stdexcept>

int main() {
    int c[4] = {10, 20, 30, 40};
    std::array<int, 4> a = {10, 20, 30, 40};
    c[2] = 31;               // O(1): base + 2 * sizeof(int), no check
    a[2] = 31;               // O(1): the same instruction, no check
    try {
        a.at(9) = 0;         // O(1): throws std::out_of_range
    } catch (const std::out_of_range& ex) {
        std::cout << "a.at(9) threw std::out_of_range: " << ex.what() << '\n';
    }
    // c[9] = 0;             // undefined behaviour: writes past the end (kept as a comment)
    a.front() = 1;           // a[0]
    a.back() = 4;            // a[N - 1]
    int* p = a.data();       // pointer to the first element

    std::cout << "c = " << c[0] << ' ' << c[1] << ' ' << c[2] << ' ' << c[3] << '\n';
    std::cout << "a = " << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << a[3] << '\n';
    std::cout << "a.data() == &a[0]: " << (p == &a[0] ? "yes" : "no") << '\n';

    // the address arithmetic is identical on both, and c[9] would land 20 B past the end
    auto cb = reinterpret_cast<std::uintptr_t>(c);
    auto ab = reinterpret_cast<std::uintptr_t>(a.data());
    std::cout << "&c[2] - &c[0] = " << reinterpret_cast<std::uintptr_t>(&c[2]) - cb << " B\n";
    std::cout << "&a[2] - &a[0] = " << reinterpret_cast<std::uintptr_t>(&a[2]) - ab << " B\n";
    std::cout << "c[9] would touch base + " << 9 * sizeof(int) << " B, the array ends at base + "
              << sizeof(c) << " B: " << 9 * sizeof(int) - sizeof(c) << " B past the end\n";
    return 0;
}
