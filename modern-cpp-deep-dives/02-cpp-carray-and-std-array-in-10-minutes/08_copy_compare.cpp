// C Array and std::array in 10 Minutes - slide 8: copy, compare and return
// Build: make 08_copy_compare
#include <algorithm>
#include <array>
#include <compare>
#include <iostream>
#include <iterator>

static std::array<int, 4> make() {       // returned by value: built in the caller's frame
    return {5, 6, 7, 8};
}

template <class A>
static void print(const char* name, const A& a) {
    std::cout << "  " << name << " =";
    for (const auto& x : a) std::cout << ' ' << x;
    std::cout << '\n';
}

int main() {
    int c[4] = {1, 2, 3, 4};
    int d[4];
    // d = c;                        // error: arrays are not assignable
    // c == d;                       // compares two pointers, not contents
    std::copy(std::begin(c), std::end(c), d);   // O(n): the C way
    std::array<int, 4> a = {1, 2, 3, 4};
    std::array<int, 4> b = a;        // O(n): copies 16 B, no heap
    bool same = (a == b);            // O(n): element by element
    auto order = a <=> b;            // C++20: lexicographic, O(n)
    std::array<int, 4> r = make();   // returned by value: no copy (RVO)

    std::cout << "C arrays: copy with std::copy, compare with std::equal\n";
    print("c", c);
    print("d", d);
    std::cout << "  std::equal(c, d): " << (std::equal(std::begin(c), std::end(c), d) ? "equal" : "different") << '\n';
    std::cout << "  &c == &d as pointers: " << (static_cast<int*>(c) == static_cast<int*>(d) ? "same" : "different")
              << " (what c == d would have compared)\n";

    std::cout << "std::array: value semantics\n";
    print("a", a);
    print("b", b);
    std::cout << "  a == b: " << (same ? "true" : "false") << '\n';
    std::cout << "  a <=> b: " << (order == 0 ? "equal" : order < 0 ? "less" : "greater") << '\n';
    b[3] = 9;
    std::cout << "  after b[3] = 9, a <=> b: " << ((a <=> b) < 0 ? "less" : "not less") << '\n';
    print("r", r);
    std::cout << "  make() returned " << sizeof(r) << " B by value with no copy on the way out\n";
    return 0;
}
