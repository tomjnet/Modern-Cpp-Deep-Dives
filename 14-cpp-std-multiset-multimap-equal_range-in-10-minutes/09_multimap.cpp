// std::multiset, std::multimap, equal_range in 10 Minutes - slide 9: std::multimap: one key, many values
// Build: make 09_multimap
#include <algorithm>
#include <iostream>
#include <map>
#include <string>

int main() {
    std::multimap<std::string, int> scores;    // one key, many values
    scores.emplace("ana", 90);
    scores.emplace("ana", 75);                 // keeps both, in this order
    scores.emplace("bob", 60);
    auto [lo, hi] = scores.equal_range("ana"); // O(log n)
    std::cout << "ana:";
    for (auto it = lo; it != hi; ++it)
        std::cout << ' ' << it->second;        // 90 75: insertion order
    std::cout << '\n';
    int best = std::max_element(lo, hi, [](auto& a, auto& b) {
        return a.second < b.second; })->second; // 90, O(k)
    // keys are const; values are not: it->second = 100 is fine

    std::cout << "best score of ana: " << best << '\n';
    lo->second = 100;                          // the value is mutable
    // lo->first = "eve";   // does not compile: the key is const
    std::cout << "after lo->second = 100:";
    for (const auto& [name, score] : scores) std::cout << ' ' << name << ':' << score;
    std::cout << '\n';
    std::cout << "count(\"ana\") = " << scores.count("ana")
              << ", count(\"eve\") = " << scores.count("eve") << '\n';
    // scores["ana"];   // does not compile: no operator[] on std::multimap
    return 0;
}
