// std::unordered_map in 10 Minutes - slide 7: insert, load factor and rehash
// Build: make 07_insert_rehash
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> m;
    m.reserve(1000);                  // buckets for 1000 keys, no rehash
    size_t reserved = m.bucket_count();

    auto [it, ok] = m.insert({"ana", 31});  // ok == false if key exists
    m.emplace("bo", 27);                    // builds the node in place
    m.try_emplace("ana", 99);               // no-op: "ana" already there
    m.insert_or_assign("ana", 32);          // overwrite instead

    // size / bucket_count > max_load_factor (1.0) triggers a rehash:
    // O(n) once, amortized O(1) per insert, like vector growth

    std::cout << std::boolalpha << "insert(\"ana\"): new = " << ok << ", it->second now = " << it->second
              << " (try_emplace ignored 99, insert_or_assign wrote 32)\n";
    std::cout << "reserve(1000): bucket_count = " << reserved << ", max_load_factor = " << m.max_load_factor() << '\n';
    for (int i = 0; i < 998; ++i) m.emplace("key" + std::to_string(i), i);
    std::cout << "after 1000 elements: bucket_count = " << m.bucket_count() << " (unchanged: no rehash), load_factor = "
              << m.load_factor() << '\n';

    std::unordered_map<int, int> g;   // no reserve: watch the bucket array grow
    size_t last = g.bucket_count();
    int rehashes = 0;
    std::cout << "unreserved map, bucket_count: " << last;
    for (int i = 0; i < 100000; ++i) {
        g.emplace(i, i);
        if (g.bucket_count() != last) { last = g.bucket_count(); ++rehashes; std::cout << " -> " << last; }
    }
    std::cout << '\n' << rehashes << " rehashes for 100000 inserts: each is O(n), so O(1) amortized per insert\n";
    return 0;
}
