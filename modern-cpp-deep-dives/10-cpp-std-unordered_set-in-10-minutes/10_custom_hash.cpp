// std::unordered_set in 10 Minutes - slide 10: custom hash and equality
// Build: make 10_custom_hash
#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_set>

struct Point {
    int x, y;
    bool operator==(const Point&) const = default;   // C++20
};
struct PointHash {
    std::size_t operator()(const Point& p) const noexcept {
        std::size_t h = std::hash<int>{}(p.x);
        return h ^ (std::hash<int>{}(p.y) + 0x9e3779b9 + (h << 6));
    }
};

// a naive hash that only adds the fields: (1, 2) and (2, 1) collide
struct SumHash {
    std::size_t operator()(const Point& p) const noexcept {
        return std::hash<int>{}(p.x) + std::hash<int>{}(p.y);
    }
};

// heterogeneous lookup: find a std::string key with a string_view, no temporary string
struct StringHash {
    using is_transparent = void;
    std::size_t operator()(std::string_view sv) const noexcept { return std::hash<std::string_view>{}(sv); }
};

int main() {
    std::unordered_set<Point, PointHash> pts;
    pts.insert({1, 2});                 // hash(1, 2) picks the bucket
    pts.insert({2, 1});
    pts.insert({1, 2});                 // duplicate: rejected by operator==
    std::cout << std::boolalpha;
    std::cout << "pts.size() = " << pts.size() << ", contains({2, 1}) = " << pts.contains({2, 1}) << '\n';
    std::cout << "PointHash(1, 2) = " << PointHash{}({1, 2}) << ", PointHash(2, 1) = " << PointHash{}({2, 1}) << '\n';
    std::cout << "SumHash(1, 2)   = " << SumHash{}({1, 2}) << ", SumHash(2, 1)   = " << SumHash{}({2, 1})
              << " (collision)\n";

    std::unordered_set<std::string, StringHash, std::equal_to<>> words{"alpha", "beta"};
    std::string_view probe = "beta";
    std::cout << "words.contains(string_view) = " << words.contains(probe) << '\n';   // C++20, no std::string built
    return 0;
}
