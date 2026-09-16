// std::multiset, std::multimap, equal_range in 10 Minutes - slide 5: create and insert: duplicates never fail
// Build: make 05_create_insert
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>

static void print(const char* name, const std::multiset<int>& c) {
    std::cout << name << ":";
    for (int x : c) std::cout << ' ' << x;
    std::cout << '\n';
}

static void print(const char* name, const std::multimap<std::string, int>& c) {
    std::cout << name << ":";
    for (const auto& [k, v] : c) std::cout << ' ' << k << ':' << v;
    std::cout << '\n';
}

int main() {
    std::multiset<int> ms{5, 1, 5, 3, 5};      // sorted: 1 3 5 5 5
    print("ms", ms);
    ms.insert(3);                              // O(log n): 1 3 3 5 5 5
    auto it = ms.insert(5);                    // never fails: an iterator,
                                               // not a pair<iterator, bool>
    ms.insert(ms.end(), 9);                    // right hint: O(1) amortized
    std::multimap<std::string, int> mm{{"a", 1}, {"a", 2}, {"b", 3}};
    mm.insert({"a", 0});                       // goes AFTER the other "a"
    mm.emplace("b", 4);                        // O(log n), in place
    // no operator[] and no at(): which of the "a" values would it pick?

    print("ms", ms);
    std::cout << "insert(5) returned an iterator to " << *it
              << ", the element after it is " << *std::next(it) << '\n';
    print("mm", mm);
    std::cout << "the new pair a:0 sits after a:1 and a:2 and before b:3\n";
    // mm["a"] = 5;   // does not compile: std::multimap has no operator[]
    return 0;
}
