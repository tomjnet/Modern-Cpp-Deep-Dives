// std::unordered_map in 10 Minutes - slide 6: lookup: find, contains, count
// Build: make 06_lookup
#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

static void use(int v) { std::cout << "  found value " << v << '\n'; }

// Transparent hash: together with std::equal_to<> it enables lookups by string_view (C++20),
// so find("literal") builds no temporary std::string.
struct StringHash {
    using is_transparent = void;
    size_t operator()(std::string_view s) const noexcept { return std::hash<std::string_view>{}(s); }
};

int main() {
    std::unordered_map<std::string, int> m{{"ana", 31}, {"bo", 27}};

    auto it = m.find("bo");             // O(1) avg: hash, bucket, compare
    if (it != m.end()) use(it->second); // it->first is the key

    bool has = m.contains("ana");       // C++20, O(1) avg
    size_t n = m.count("zed");          // 0 or 1: keys are unique

    // O(n) worst case: every key in one bucket (bad hash or attack)

    std::cout << std::boolalpha << "m.contains(\"ana\")        = " << has << "\nm.count(\"zed\")           = " << n
              << "\nm.find(\"zed\") == m.end() = " << (m.find("zed") == m.end())
              << "\nm.size()                 = " << m.size() << " (lookups never insert)\n";

    std::unordered_map<std::string, int, StringHash, std::equal_to<>> t{{"ana", 31}, {"bo", 27}};
    std::string_view key = "ana";
    std::cout << "heterogeneous lookup: t.find(string_view \"ana\")->second = " << t.find(key)->second
              << " (no temporary std::string built)\n";
    return 0;
}
