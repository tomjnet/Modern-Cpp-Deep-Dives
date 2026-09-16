// std::multiset, std::multimap, equal_range in 10 Minutes - slide 8: erase: by key, by iterator, by range
// Build: make 08_erase
#include <iostream>
#include <iterator>
#include <set>

static void print(const char* name, const std::multiset<int>& c) {
    std::cout << name << ":";
    for (int x : c) std::cout << ' ' << x;
    std::cout << "  (size " << c.size() << ")\n";
}

int main() {
    std::multiset<int> ms{1, 3, 5, 5, 5, 9};
    print("start", ms);
    std::size_t n = ms.erase(5);       // ALL the 5s: O(log n + k), n == 3
    std::cout << "erase(5) removed " << n << " elements\n";
    print("after erase(5)", ms);
    ms.insert({5, 5, 5});
    print("after insert({5, 5, 5})", ms);
    ms.erase(ms.find(5));              // ONE 5: O(1) amortized, one node
    print("after erase(find(5))", ms);
    auto [lo, hi] = ms.equal_range(5);
    ms.erase(lo, hi);                  // the rest of the group: O(k)
    print("after erase(equal_range(5))", ms);
    // erase(key) is the trap: "remove one 5" written as ms.erase(5)
    // deletes every 5. Pass an iterator when you mean one element.
    ms.insert({5, 5});
    std::erase_if(ms, [](int x) { return x > 4; });   // C++20: O(n)
    print("after erase_if(x > 4)", ms);
    ms.clear();                        // O(n): one free per node
    print("after clear()", ms);

    // removing the last inserted copy: the element before upper_bound
    std::multiset<int> t{5, 5, 5};
    auto last = std::prev(t.upper_bound(5));
    t.erase(last);
    print("three 5s minus the last one", t);
    return 0;
}
