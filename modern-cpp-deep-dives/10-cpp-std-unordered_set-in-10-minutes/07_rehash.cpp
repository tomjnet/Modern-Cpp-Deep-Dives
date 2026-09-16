// std::unordered_set in 10 Minutes - slide 7: rehash and growth
// Build: make 07_rehash
#include <cstddef>
#include <iostream>
#include <unordered_set>

int main() {
    std::unordered_set<int> s;
    s.max_load_factor(1.0f);       // default: size / bucket_count <= 1

    for (int i = 0; i < 1000; ++i) s.insert(i);
    // each time load > max: rehash, O(n), bucket_count grows,
    // every node is relinked, no key is copied or moved
    std::cout << "1000 inserts: size " << s.size() << ", bucket_count " << s.bucket_count()
              << ", load_factor " << s.load_factor() << '\n';

    s.reserve(100000);             // buckets for 100000 keys: one rehash
    std::cout << "reserve(100000): bucket_count " << s.bucket_count() << '\n';
    s.rehash(64);                  // at least 64 buckets
    std::cout << "rehash(64): bucket_count " << s.bucket_count()
              << " (never below size / max_load_factor)\n";

    float lf = s.load_factor();    // size() / bucket_count()
    std::cout << "load_factor " << lf << '\n';

    // watch the rehashes: bucket_count jumps, the node that holds key 0 never moves
    std::unordered_set<int> g;
    g.insert(0);
    const int* node0 = &*g.find(0);
    std::size_t last = g.bucket_count();
    for (int i = 1; i < 1000; ++i) {
        g.insert(i);
        if (g.bucket_count() != last) {
            last = g.bucket_count();
            std::cout << "rehash at size " << g.size() << " -> bucket_count " << last
                      << ", key 0 at " << static_cast<const void*>(&*g.find(0))
                      << (node0 == &*g.find(0) ? " (same node)" : " (moved!)") << '\n';
        }
    }
    return 0;
}
