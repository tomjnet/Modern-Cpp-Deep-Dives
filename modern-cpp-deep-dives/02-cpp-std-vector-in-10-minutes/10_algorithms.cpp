// std::vector in 10 Minutes - slide 10: iterate, sort and search
// Build: make 10_algorithms
#include <algorithm>
#include <iostream>
#include <vector>

static void use(int x) { std::cout << x << ' '; }

int main() {
    std::vector<int> v{40, 10, 30, 20};

    std::cout << "scan: ";
    for (int x : v) use(x);                       // O(n) scan
    std::cout << '\n';

    auto it = std::find(v.begin(), v.end(), 30);  // O(n)
    std::cout << "find(30): index " << (it - v.begin()) << '\n';

    std::sort(v.begin(), v.end());                // O(n log n)
    bool hit = std::binary_search(v.begin(), v.end(), 30);  // O(log n)
    auto pos = std::lower_bound(v.begin(), v.end(), 25);    // O(log n)

    std::cout << "sorted: ";
    for (int x : v) use(x);
    std::cout << "\nbinary_search(30): " << (hit ? "found" : "missing")
              << "\nlower_bound(25): index " << (pos - v.begin()) << " (value " << *pos << ")\n";
    return 0;
}
