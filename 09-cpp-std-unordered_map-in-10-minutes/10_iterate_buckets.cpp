// std::unordered_map in 10 Minutes - slide 10: iterate and inspect the buckets
// Build: make 10_iterate_buckets
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

static void use(const std::string& key, int val) { std::cout << "  " << key << " -> " << val << '\n'; }

int main() {
    std::unordered_map<std::string, int> m{{"ana", 31}, {"bo", 27}};

    for (auto& [key, val] : m) use(key, val); // O(n), unspecified order

    size_t b  = m.bucket("ana");     // which bucket holds "ana"
    size_t n  = m.bucket_count();    // a prime (libstdc++) or power of 2
    float  lf = m.load_factor();     // size / bucket_count
    m.max_load_factor(0.5f);         // rehash sooner: shorter chains

    // sorted output? copy to a vector and std::sort: O(n log n)

    std::cout << "bucket(\"ana\") = " << b << ", bucket_count = " << n << ", load_factor = " << lf << '\n';
    m.rehash(0);   // apply the new max_load_factor right away
    std::cout << "after max_load_factor(0.5): bucket_count = " << m.bucket_count()
              << ", load_factor = " << m.load_factor() << '\n';

    for (int i = 0; i < 6; ++i) m.emplace("k" + std::to_string(i), i);
    std::cout << "bucket order after more inserts (not sorted):";
    for (auto& [key, val] : m) std::cout << ' ' << key << '=' << val;
    std::vector<std::pair<std::string, int>> sorted(m.begin(), m.end());
    std::sort(sorted.begin(), sorted.end());   // O(n log n)
    std::cout << "\nsorted copy:                                ";
    for (auto& [key, val] : sorted) std::cout << ' ' << key << '=' << val;
    std::cout << '\n';
    return 0;
}
