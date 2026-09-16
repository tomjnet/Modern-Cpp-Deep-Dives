// std::unordered_map in 10 Minutes - slide 8: erase and iterator invalidation
// Build: make 08_erase_invalidation
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<int, std::string> m{{1, "a"}, {2, "b"}, {3, "c"}};

    m.erase(2);                     // O(1) avg: by key, returns 0 or 1
    std::cout << "erase(2): size = " << m.size() << ", erase(2) again returns " << m.erase(2) << '\n';
    auto it = m.find(1);
    std::string& ref = it->second;
    const void* node = &ref;        // address of the heap node that holds key 1

    m.erase(m.find(3));             // only that iterator dies
    size_t before = m.bucket_count();
    m.insert({4, "d"});             // rehash? every iterator is invalid
                                    // ref and pointers to nodes survive
    for (int i = 5; i <= 64; ++i) m.emplace(i, "z");   // enough inserts to force at least one rehash
    std::cout << "bucket_count " << before << " -> " << m.bucket_count()
              << ": rehashed, so the iterator 'it' is now invalid (not used again)\n"
              << "ref still reads \"" << ref << "\" at " << node << ", &m[1] = " << static_cast<const void*>(&m[1])
              << " (same node: nothing moved)\n";

    std::erase_if(m, [](auto& kv) { return kv.first % 2; });  // C++20

    bool all_even = true;
    for (const auto& kv : m) all_even = all_even && kv.first % 2 == 0;
    std::cout << std::boolalpha << "erase_if(odd keys): size = " << m.size() << ", every remaining key is even: " << all_even << '\n';
    return 0;
}
