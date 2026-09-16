// C Array and std::array in 10 Minutes - slide 5: create and initialize
// Build: make 05_create_init
#include <array>
#include <cstddef>
#include <iostream>
#include <type_traits>

template <class A>
static void print(const char* name, const A& a) {
    std::cout << "  " << name << " =";
    for (const auto& x : a) std::cout << ' ' << x;
    std::cout << "  (" << sizeof(a) << " B)\n";
}

int main() {
    int c[4] = {1, 2, 3, 4};             // C array: 16 B in the frame
    int z[4] = {};                       // all zero; "int u[4];" is garbage
    std::array<int, 4> a = {1, 2, 3, 4}; // aggregate: same 16 B, same place
    std::array<int, 4> e{};              // value-initialized: all zero
    std::array b = {1, 2, 3, 4};         // CTAD, C++17: std::array<int, 4>
    auto t = std::to_array("hi");        // C++20: std::array<char, 3>
    int n[] = {1, 2, 3};                 // size deduced: 3
    std::array<int, 3> f;                // indeterminate, like a C array
    f.fill(7);                           // O(n): every element set to 7

    std::cout << "C array and std::array are both aggregates:\n";
    print("c", c);
    print("z", z);
    print("a", a);
    print("e", e);
    print("b", b);
    std::cout << "  t = {'" << t[0] << "', '" << t[1] << "', '\\0'}  (" << sizeof(t) << " B, "
              << t.size() << " elements including the terminator)\n";
    print("n", n);
    print("f", f);

    static_assert(sizeof(c) == sizeof(a), "same bytes");
    static_assert(std::is_same_v<decltype(b), std::array<int, 4>>, "CTAD deduced N = 4");
    static_assert(sizeof(n) / sizeof(n[0]) == 3, "N deduced from the initializer");
    std::cout << "  sizeof(int[4]) == sizeof(std::array<int, 4>) == " << sizeof(a) << " B\n";
    return 0;
}
