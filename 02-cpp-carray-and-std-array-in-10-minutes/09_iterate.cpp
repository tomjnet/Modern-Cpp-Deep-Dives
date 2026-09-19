// C Array and std::array in 10 Minutes - slide 9: iteration and algorithms
// Build: make 09_iterate
#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>

static void use(int x) { std::cout << ' ' << x; }

int main() {
    int c[4] = {1, 2, 3, 4};
    std::array<int, 4> a = {4, 3, 2, 1};
    std::cout << "range for on c:";
    for (int x : c) use(x);              // O(n): N comes from the type
    std::cout << "\nrange for on a:";
    for (int x : a) use(x);              // O(n): begin() and end()
    std::cout << "\nstd::size(c) = " << std::size(c) << '\n';  // 4 (C++17); std::ssize in C++20
    std::sort(std::begin(c), std::end(c));   // O(n log n)
    std::sort(a.begin(), a.end());           // O(n log n)
    std::ranges::sort(a);                    // C++20: any range, also c
    auto it = std::ranges::find(c, 3);       // O(n): a pointer into c
    std::cout << "a after sort:";
    for (int x : a) use(x);
    std::cout << "\na backwards:";
    for (auto r = a.rbegin(); r != a.rend(); ++r) use(*r);  // backwards
    std::cout << "\nstd::ranges::find(c, 3) found " << *it << " at index " << (it - std::begin(c)) << '\n';
    std::cout << "std::ssize(c) = " << std::ssize(c) << ", std::size(a) = " << std::size(a) << '\n';
    return 0;
}
