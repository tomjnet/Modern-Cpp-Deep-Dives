// std::set in 10 Minutes - slide 5: create, find and contains
// Build: make 05_create_find
#include <cstddef>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

static void print(const char* name, const std::set<int>& s) {
    std::cout << name << " = {";
    for (int x : s) std::cout << ' ' << x;
    std::cout << " }  size " << s.size() << '\n';
}

int main() {
    std::vector<int> v{5, 1, 3, 1, 5, 2};    // any range, duplicates included

    std::set<int> a;                     // empty: header node only
    std::set<int> b{30, 10, 20, 10};     // {10, 20, 30}: sorted, unique
    std::set<int> c(v.begin(), v.end()); // from any range: O(n log n)

    auto it = b.find(20);        // O(log n): iterator, or b.end()
    bool has = b.contains(20);   // O(log n), C++20
    std::size_t k = b.count(10); // 0 or 1: keys are unique
    int lo = *b.begin();         // 10, the minimum: O(1)
    int hi = *b.rbegin();        // 30, the maximum: O(1)
    // no b[i], no b.at(i): there is no index, only order

    print("a", a);
    print("b", b);
    print("c", c);
    std::cout << "b.find(20): " << (it != b.end() ? "found" : "end()") << '\n';
    std::cout << "b.find(99): " << (b.find(99) != b.end() ? "found" : "end()") << '\n';
    std::cout << "b.contains(20): " << std::boolalpha << has << '\n';
    std::cout << "b.count(10): " << k << "   (never more than 1)\n";
    std::cout << "min *b.begin(): " << lo << "   max *b.rbegin(): " << hi << '\n';

    // the k-th smallest key has no shortcut: walk k steps from begin, O(k)
    auto third = std::next(c.begin(), 2);
    std::cout << "3rd smallest of c: " << *third << " (reached by walking 2 steps)\n";
    return 0;
}
