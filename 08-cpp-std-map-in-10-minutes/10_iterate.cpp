// std::map in 10 Minutes - slide 10: iterate in order
// Build: make 10_iterate
//
// A range-for visits the pairs in ascending key order; ++it is amortized O(1), so a full traversal
// is O(n). begin() is the smallest key and prev(end()) the largest, both O(1).
#include <iostream>
#include <iterator>
#include <map>
#include <string>

static void use(const std::string& key, int value) { std::cout << "  " << key << " = " << value << '\n'; }
static void use(const std::string& key) { std::cout << "  " << key << '\n'; }

int main() {
    std::map<std::string, int> m{{"cpp", 3}, {"asm", 1}, {"rust", 2}};

    std::cout << "ascending:\n";
    for (const auto& [key, value] : m)   // in order: asm, cpp, rust
        use(key, value);                  // O(n) total, ++it amortized O(1)

    std::cout << "descending:\n";
    for (auto it = m.rbegin(); it != m.rend(); ++it)  // rust, cpp, asm
        use(it->first);

    auto first = m.begin()->first;           // smallest key: O(1)
    auto last  = std::prev(m.end())->first;  // largest key: O(1)
    // no std::sort here: the tree is sorted already and keys are const
    std::cout << "smallest key: " << first << ", largest key: " << last << '\n';

    // a full traversal of a large map is linear even though single steps vary in cost
    std::map<int, int> big;
    for (int i = 0; i < 1000000; ++i) big.emplace(i, i);
    long long sum = 0;
    for (const auto& [k, v] : big) sum += v;
    std::cout << "sum over 1000000 entries: " << sum << '\n';
    return 0;
}
