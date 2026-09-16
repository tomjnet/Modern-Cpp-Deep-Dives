// std::set in 10 Minutes - slide 10: iterate, merge and set algorithms
// Build: make 10_algorithms
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

static void use(int x) { std::cout << x << ' '; }

static void print(const char* name, const std::set<int>& s) {
    std::cout << name << " = {";
    for (int x : s) std::cout << ' ' << x;
    std::cout << " }\n";
}

int main() {
    std::set<int> a{1, 3, 5, 7}, b{3, 4, 5};

    std::cout << "a in order: ";
    for (int x : a) use(x);       // in order: O(n), ++it amortized O(1)
    std::cout << '\n';
    // no std::sort: the tree is the order, and keys are const

    std::vector<int> common;      // both inputs sorted: O(n + m)
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(),
                          std::back_inserter(common));   // {3, 5}
    std::cout << "set_intersection(a, b): ";
    for (int x : common) use(x);
    std::cout << '\n';

    std::vector<int> all, only_a;
    std::set_union(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(all));
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(only_a));
    std::cout << "set_union(a, b):        ";
    for (int x : all) use(x);
    std::cout << "\nset_difference(a, b):   ";
    for (int x : only_a) use(x);
    std::cout << '\n';

    a.merge(b);                   // relinks b's new keys into a, no copy
                                  // O(m log(n + m)); b keeps {3, 5}
    print("a after a.merge(b)", a);
    print("b after a.merge(b)", b);
    return 0;
}
