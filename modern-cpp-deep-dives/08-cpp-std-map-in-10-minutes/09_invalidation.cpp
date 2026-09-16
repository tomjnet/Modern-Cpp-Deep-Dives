// std::map in 10 Minutes - slide 9: iterator invalidation rules
// Build: make 09_invalidation
//
// insert and emplace invalidate nothing: rebalancing rewires pointers, it never moves a node.
// erase invalidates only the erased element. The program proves it by comparing addresses.
#include <iostream>
#include <map>

int main() {
    std::map<int, int> m{{1, 10}, {2, 20}, {3, 30}};
    auto it  = m.find(2);
    int& ref = m[2];
    const int* before = &ref;

    m.insert({4, 40});   // nothing invalidated: nodes never move
    m.emplace(0, 0);     // same, even when the tree rebalances
    m.erase(1);          // only iterators and references to key 1

    // it and ref are still good: it->second == 20, ref == 20
    std::cout << "it->second = " << it->second << ", ref = " << ref << '\n';
    std::cout << "address of m[2] before: " << static_cast<const void*>(before)
              << ", after: " << static_cast<const void*>(&m[2])
              << (before == &m[2] ? "  (same node)" : "  (moved!)") << '\n';

    // many inserts, including ones that rebalance around key 2: the node stays where it is
    for (int i = 100; i < 100000; ++i) m.emplace(i, i);
    std::cout << "after 99900 more inserts: " << static_cast<const void*>(&m[2])
              << (before == &m[2] ? "  (still the same node)" : "  (moved!)") << '\n';

    std::map<int, int> copy = m;   // copy: new nodes, fresh iterators
    std::cout << "copy[2] lives at " << static_cast<const void*>(&copy[2])
              << (&copy[2] != before ? "  (a different node)" : "  (?)") << '\n';
    return 0;
}
