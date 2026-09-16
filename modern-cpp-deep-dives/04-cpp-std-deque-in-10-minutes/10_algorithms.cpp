// std::deque in 10 Minutes - slide 10: iterate, sort and search
// Build: make 10_algorithms
#include <algorithm>
#include <chrono>
#include <deque>
#include <iostream>
#include <vector>

static void use(int x) { std::cout << x << ' '; }

int main() {
    std::deque<int> d{40, 10, 30, 20};

    std::cout << "scan: ";
    for (int x : d) use(x);                   // O(n), block by block
    std::cout << '\n';
    auto it = std::find(d.begin(), d.end(), 30);  // O(n)
    std::cout << "find(30): index " << (it - d.begin()) << '\n';

    std::sort(d.begin(), d.end());            // O(n log n)
    bool hit = std::binary_search(d.begin(), d.end(), 30);
    // O(log n) once sorted; d[i] is two hops, so scans and
    // sorts run slower than the same work on a vector
    std::cout << "sorted: ";
    for (int x : d) use(x);
    std::cout << "\nbinary_search(30): " << (hit ? "found" : "missing") << '\n';

    // same Big-O, different constant: sort 1M ints in a deque and in a vector
    const int n = 1'000'000;
    std::deque<int> dq;
    std::vector<int> vec;
    for (int i = 0; i < n; ++i) { int v = int((1LL * i * 7919) % n); dq.push_back(v); vec.push_back(v); }   // 64-bit product: no overflow
    auto time = [](auto& c) {
        auto t0 = std::chrono::steady_clock::now();
        std::sort(c.begin(), c.end());
        return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
    };
    double td = time(dq), tv = time(vec);
    std::cout << "std::sort of 1M ints: deque " << td << " ms, vector " << tv << " ms (" << td / tv << "x)\n";
    return 0;
}
