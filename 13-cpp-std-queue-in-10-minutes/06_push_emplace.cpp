// std::queue in 10 Minutes - slide 6: push, emplace and growth
// Build: make 06_push_emplace
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::queue<int> q;

    q.push(10);          // c.push_back(10): O(1)
    q.push(20);
    q.emplace(30);       // c.emplace_back(30): built in place

    int& newest = q.back();   // 30
    q.push(40);          // newest still valid: a deque never moves
                         // its elements, it adds a block instead

    std::cout << "front " << q.front() << ", back " << q.back() << ", size " << q.size() << '\n';
    std::cout << "newest = " << newest << " at " << static_cast<const void*>(&newest) << '\n';

    // keep pushing across many block boundaries (128 ints per block in libstdc++):
    // the reference taken before still points at the same int, at the same address
    const std::uintptr_t before = reinterpret_cast<std::uintptr_t>(&newest);
    for (int i = 0; i < 100000; ++i) q.push(i);
    const std::uintptr_t after = reinterpret_cast<std::uintptr_t>(&newest);
    std::cout << "after 100000 more pushes: newest = " << newest << ", address "
              << (before == after ? "unchanged" : "changed") << ", size " << q.size() << '\n';

    // the same experiment on std::vector: push_back reallocates and moves every element
    std::vector<int> v{10, 20, 30};
    const std::uintptr_t vbefore = reinterpret_cast<std::uintptr_t>(v.data());
    for (int i = 0; i < 100000; ++i) v.push_back(i);
    const std::uintptr_t vafter = reinterpret_cast<std::uintptr_t>(v.data());
    std::cout << "std::vector after 100000 push_back: data pointer "
              << (vbefore == vafter ? "unchanged" : "changed, old references are dangling") << '\n';
    return 0;
}
