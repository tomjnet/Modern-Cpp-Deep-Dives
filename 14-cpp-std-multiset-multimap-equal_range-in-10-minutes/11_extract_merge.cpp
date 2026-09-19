// std::multiset, std::multimap, equal_range in 10 Minutes - slide 11: extract and merge: moving nodes, not values
// Build: make 11_extract_merge
#include <iostream>
#include <set>
#include <utility>

template <class C>
static void print(const char* name, const C& c) {
    std::cout << name << ":";
    for (int x : c) std::cout << ' ' << x;
    std::cout << "  (size " << c.size() << ")\n";
}

int main() {
    std::multiset<int> a{1, 5, 5, 9}, b{5, 7};
    print("a", a);
    print("b", b);
    auto node = a.extract(a.find(5));    // C++17: unlink, O(1) amortized
    const int* where = &node.value();    // the node keeps its allocation
    node.value() = 6;                    // edit the key without a copy
    a.insert(std::move(node));           // relink: O(log n), never fails
    print("a after extract, value() = 6, insert(node)", a);
    std::cout << std::boolalpha << "the 6 lives at the address the 5 had: "
              << (&*a.find(6) == where) << '\n';
    a.merge(b);                          // O(m log(n + m)): every node of
                                         // b moves over, duplicates welcome
    // b is now empty: a merge into a multi container leaves nothing behind
    print("a after merge(b)", a);
    print("b", b);
    std::set<int> s{5};
    a.merge(s);                          // a set can merge into a multiset
    // a node handle is the only way to change a key without reallocating
    print("a after merge(set{5})", a);
    print("s", s);
    return 0;
}
