// std::unordered_set in 10 Minutes - slide 6: lookup with find, contains and count
// Build: make 06_lookup
#include <cstddef>
#include <functional>
#include <iostream>
#include <unordered_set>

static void use(int x) { std::cout << "found " << x << '\n'; }

int main() {
    std::unordered_set<int> s{10, 20, 30, 40};

    bool has = s.contains(30);      // C++20, O(1) avg: hash, bucket, chain
    auto it = s.find(20);           // iterator or s.end(), O(1) avg
    if (it != s.end()) use(*it);    // *it is const: keys never change
    std::size_t n = s.count(99);    // 0 or 1 in a set

    std::size_t bk = s.bucket(30);          // which bucket holds 30
    std::size_t len = s.bucket_size(bk);    // chain length: usually 1

    std::cout << std::boolalpha;
    std::cout << "contains(30) = " << has << '\n';
    std::cout << "count(99)    = " << n << '\n';
    std::cout << "bucket(30)   = " << bk << " of " << s.bucket_count() << ", chain length " << len << '\n';
    // *it = 21;   // does not compile: the key is const, a new value would need a new bucket

    // every key: hash, bucket, chain length (std::hash<int> is the identity in libstdc++)
    for (int k : s)
        std::cout << "key " << k << ": hash " << std::hash<int>{}(k) << " -> bucket " << s.bucket(k)
                  << " (chain " << s.bucket_size(s.bucket(k)) << ")\n";
    return 0;
}
