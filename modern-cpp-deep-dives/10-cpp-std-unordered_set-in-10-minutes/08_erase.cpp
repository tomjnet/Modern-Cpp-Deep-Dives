// std::unordered_set in 10 Minutes - slide 8: erase and extract
// Build: make 08_erase
#include <cstddef>
#include <iostream>
#include <unordered_set>
#include <utility>

static void show(const char* label, const std::unordered_set<int>& s) {
    std::cout << label << ": size " << s.size() << ", keys {";
    for (int k : s) std::cout << ' ' << k;
    std::cout << " }\n";
}

int main() {
    std::unordered_set<int> s{10, 20, 30, 40, 50};
    show("start", s);
    std::size_t buckets_before = s.bucket_count();

    std::size_t gone = s.erase(30);   // by key, O(1) avg: 1 or 0 removed
    auto it = s.find(40);
    s.erase(it);                      // by iterator, O(1): unlink one node
    show("erase(30), erase(find(40))", s);
    std::cout << "erase(30) removed " << gone << ", erase(99) removes " << s.erase(99) << '\n';

    std::erase_if(s, [](int x) { return x < 20; });  // C++20, O(n)
    show("erase_if(x < 20)", s);

    auto node = s.extract(50);        // C++17: unlink, keep the node
    std::cout << "extracted " << node.value() << ", s.size() now " << s.size() << '\n';
    std::unordered_set<int> t;
    t.insert(std::move(node));        // move it to another set, no copy
    show("s", s);
    show("t", t);

    // erasing never shrinks the bucket array; only a rehash changes it
    std::cout << "bucket_count before " << buckets_before << ", after erasing " << s.bucket_count() << '\n';
    return 0;
}
