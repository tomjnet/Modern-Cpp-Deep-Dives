// C Array and std::array in 10 Minutes - slide 10: compile time and templates
// Build: make 10_constexpr
#include <array>
#include <cstddef>
#include <iostream>

// The two templates of the slide live at namespace scope (a template cannot be defined inside main).
template <typename T, std::size_t N>
constexpr std::size_t count(const std::array<T, N>&) { return N; }
template <typename T, std::size_t N>
constexpr std::size_t count(const T (&)[N]) { return N; }

static constexpr int sum_of(std::array<int, 4> t) {   // a constexpr loop over the table
    int s = 0;
    for (int v : t) s += v;
    return s;
}

int main() {
    constexpr std::array<int, 4> sq = {0, 1, 4, 9};   // lives in .rodata
    static_assert(sq[2] == 4);                        // O(1), compile time
    static_assert(sq.size() == 4);                    // N is a constant
    auto [x, y, z, w] = sq;                    // structured bindings
    int third = std::get<2>(sq);               // tuple interface, O(1)

    constexpr int c[3] = {7, 8, 9};
    static_assert(count(sq) == 4, "N deduced from std::array<int, 4>");
    static_assert(count(c) == 3, "N deduced from int[3]");

    std::cout << "sq = " << x << ' ' << y << ' ' << z << ' ' << w << " (structured bindings)\n";
    std::cout << "std::get<2>(sq) = " << third << '\n';
    std::cout << "count(sq) = " << count(sq) << ", count(c) = " << count(c) << ", both folded at compile time\n";

    // every element is usable in a constant expression, even through a loop
    constexpr int sum = sum_of(sq);
    static_assert(sum == 14);
    std::cout << "sum of sq, computed by the compiler: " << sum << '\n';
    return 0;
}
