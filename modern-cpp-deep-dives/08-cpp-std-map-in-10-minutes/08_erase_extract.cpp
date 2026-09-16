// std::map in 10 Minutes - slide 8: erase, extract and merge
// Build: make 08_erase_extract
//
// erase(key) is O(log n), erase(iterator) is amortized O(1). extract (C++17) unlinks a node without
// copying or freeing it, so a key can be changed and the same node inserted back.
#include <iostream>
#include <map>
#include <utility>

static void print(const char* label, const std::map<int, int>& m) {
    std::cout << label << ':';
    for (const auto& [key, value] : m) std::cout << ' ' << key << '=' << value;
    std::cout << '\n';
}

int main() {
    std::map<int, int> m{{1, 1}, {2, 4}, {3, 9}, {4, 16}, {5, 25}};
    print("start", m);

    m.erase(3);                    // O(log n): find, unlink, rebalance
    print("erase(3)", m);
    m.erase(m.begin());            // amortized O(1) with an iterator
    print("erase(begin())", m);
    m.erase(m.find(4), m.end());   // range [4, end): O(k) amortized
    print("erase(find(4), end())", m);

    auto node = m.extract(2);      // C++17: unlink, no copy, no free
    const int* where = &node.mapped();
    node.key() = 20;               // the key is mutable here
    m.insert(std::move(node));     // same node, new place: O(log n)
    print("extract(2), key = 20, insert", m);
    std::cout << "value address before and after the reinsert: "
              << (where == &m.at(20) ? "same node" : "different node") << '\n';

    m.insert({{7, 49}, {8, 64}, {9, 3}});
    std::erase_if(m, [](auto& kv) { return kv.second > 10; }); // C++20
    print("erase_if(value > 10)", m);

    std::map<int, int> other{{9, 81}, {10, 100}};
    m.merge(other);                // moves the nodes that do not collide
    print("after merge", m);
    print("left in other (key 9 collided)", other);
    return 0;
}
