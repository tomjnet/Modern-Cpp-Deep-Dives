// std::multiset, std::multimap, equal_range in 10 Minutes - slide 10: walking group by group
// Build: make 10_groups
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>

int main() {
    std::multimap<std::string, int> mm{{"ana", 90}, {"ana", 75}, {"bob", 60},
                                       {"cid", 10}, {"cid", 20}, {"cid", 30}};

    // walk a multimap group by group: O(g log n + n), g distinct keys
    for (auto it = mm.begin(); it != mm.end();) {
        auto [lo, hi] = mm.equal_range(it->first);   // O(log n) per group
        int sum = 0;
        for (auto e = lo; e != hi; ++e) sum += e->second;   // O(k)
        std::cout << it->first << ": " << sum << '\n';
        it = hi;                                     // jump over the group
    }
    // the same trick on a multiset: it = ms.upper_bound(*it)
    // a plain map<K, vector<V>> hands you the group for free: pick it
    // when the group is the unit of work, the multimap when the pair is

    std::multiset<int> ms{1, 3, 3, 5, 5, 5, 9};
    std::cout << "multiset groups:";
    for (auto it = ms.begin(); it != ms.end();) {
        auto hi = ms.upper_bound(*it);
        std::cout << ' ' << *it << 'x' << std::distance(it, hi);
        it = hi;
    }
    std::cout << '\n';
    return 0;
}
