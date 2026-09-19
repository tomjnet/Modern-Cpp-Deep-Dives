// std::map in 10 Minutes - slide 11: comparators, transparent lookup and multimap
// Build: make 11_comparator
//
// The third template argument orders the keys. std::less<> is the transparent comparator: find and
// contains accept a string_view or a string literal without building a temporary std::string.
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <string_view>

int main() {
    std::map<int, int, std::greater<int>> desc;   // largest key first
    desc.emplace(1, 10); desc.emplace(3, 30); desc.emplace(2, 20);
    std::cout << "std::greater order:";
    for (const auto& [k, v] : desc) std::cout << ' ' << k << '=' << v;
    std::cout << '\n';

    std::map<std::string, int, std::less<>> m;    // transparent compare
    m.emplace("key", 1);
    auto it = m.find(std::string_view{"key"});   // no temporary std::string
    bool has = m.contains("key");                 // const char* works too
    std::cout << "find(string_view) found " << it->first << " = " << it->second
              << ", contains(\"key\") = " << std::boolalpha << has << '\n';

    std::multimap<int, std::string> mm;           // duplicate keys allowed
    mm.emplace(1, "a"); mm.emplace(1, "b");       // both kept, in order
    mm.emplace(0, "z");
    auto [lo, hi] = mm.equal_range(1);            // both entries
    std::cout << "multimap count(1) = " << mm.count(1) << ", equal_range(1):";
    for (auto i = lo; i != hi; ++i) std::cout << ' ' << i->first << '=' << i->second;
    std::cout << '\n';

    // any strict weak ordering works: a lambda comparing by string length, then alphabetically
    auto by_len = [](const std::string& a, const std::string& b) {
        return a.size() != b.size() ? a.size() < b.size() : a < b;
    };
    std::map<std::string, int, decltype(by_len)> shortest(by_len);
    shortest.emplace("vector", 1); shortest.emplace("map", 2); shortest.emplace("set", 3);
    std::cout << "by length:";
    for (const auto& [k, v] : shortest) std::cout << ' ' << k;
    std::cout << '\n';
    return 0;
}
