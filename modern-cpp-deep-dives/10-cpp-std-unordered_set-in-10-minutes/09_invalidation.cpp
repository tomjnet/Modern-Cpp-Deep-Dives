// std::unordered_set in 10 Minutes - slide 9: iterator invalidation rules
// Build: make 09_invalidation
#include <iostream>
#include <unordered_set>
#include <utility>

static void show(const char* label, const std::unordered_set<int>& s) {
    std::cout << label << ": keys {";
    for (int k : s) std::cout << ' ' << k;
    std::cout << " }\n";
}

int main() {
    std::unordered_set<int> s{1, 2, 3};
    const int& ref = *s.find(2);
    auto it = s.find(2);
    const void* before = &ref;
    std::cout << "before: key 2 at " << before << ", bucket_count " << s.bucket_count() << '\n';

    s.insert(4);        // may rehash: every iterator is invalid,
                        // ref is still valid, the node never moves
    s.reserve(1000);    // rehash for sure: same rule
    std::cout << "after reserve(1000): bucket_count " << s.bucket_count() << ", ref = " << ref
              << " at " << static_cast<const void*>(&ref) << (&ref == before ? " (same node)" : " (moved!)") << '\n';
    // std::cout << *it;   // undefined behaviour: it was invalidated by the rehash, never dereference it
    it = s.find(2);        // take a fresh iterator instead
    std::cout << "fresh iterator: *it = " << *it << '\n';

    s.erase(1);         // invalidates only iterators to 1
    std::cout << "after erase(1): *it = " << *it << ", ref = " << ref << " (both still valid)\n";

    // keys are const: to change one, extract, modify, insert
    // *it = 22;        // does not compile: the key is const
    auto node = s.extract(3);
    node.value() = 33;
    s.insert(std::move(node));
    show("after extract(3), value = 33, insert", s);
    return 0;
}
