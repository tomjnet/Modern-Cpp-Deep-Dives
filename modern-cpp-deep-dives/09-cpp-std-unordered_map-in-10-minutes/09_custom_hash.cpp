// std::unordered_map in 10 Minutes - slide 9: collisions and a custom hash
// Build: make 09_custom_hash
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <unordered_map>

struct Point {
    int x, y;
    bool operator==(const Point&) const = default;   // C++20
};
struct PointHash {
    size_t operator()(const Point& p) const noexcept {
        return std::hash<int>{}(p.x) ^ (std::hash<int>{}(p.y) << 1);
    }
};
struct BadHash {   // hashes only x: every point on the same column lands in one bucket
    size_t operator()(const Point& p) const noexcept { return std::hash<int>{}(p.x); }
};

template <class Map> static size_t longest_chain(const Map& m) {
    size_t longest = 0;
    for (size_t b = 0; b < m.bucket_count(); ++b) longest = std::max(longest, m.bucket_size(b));
    return longest;
}

int main() {
    std::unordered_map<Point, int, PointHash> grid;
    grid[{3, 4}] = 1;   // hash -> bucket; collisions chain in the bucket
    // a poor hash puts every key in one bucket: O(1) becomes O(n)

    grid[{3, 5}] = 2;
    grid[{4, 4}] = 3;
    std::cout << "grid[{3,4}] = " << grid[{3, 4}] << ", grid.size() = " << grid.size()
              << ", bucket_count = " << grid.bucket_count() << '\n'
              << "bucket of {3,4}: " << grid.bucket({3, 4}) << ", {3,5}: " << grid.bucket({3, 5})
              << ", {4,4}: " << grid.bucket({4, 4}) << '\n';

    std::unordered_map<Point, int, PointHash> good;
    std::unordered_map<Point, int, BadHash> bad;
    for (int i = 0; i < 1000; ++i) { good[{7, i}] = i; bad[{7, i}] = i; }
    std::cout << "1000 points with x = 7:\n"
              << "  PointHash: longest chain = " << longest_chain(good) << " over " << good.bucket_count()
              << " buckets (find stays O(1))\n"
              << "  BadHash:   longest chain = " << longest_chain(bad) << " over " << bad.bucket_count()
              << " buckets (one chain: find is O(n))\n";
    return 0;
}
