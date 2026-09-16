// std::map in 10 Minutes - slide 7: lookup and ranges
// Build: make 07_lookup
//
// contains, count and find cost O(log n). lower_bound and upper_bound turn the sorted keys into
// range queries: every key in [a, b] in O(log n + k).
#include <iostream>
#include <map>

static void use(int key, char value) { std::cout << "  " << key << " -> " << value << '\n'; }

int main() {
    std::map<int, char> m{{10, 'a'}, {20, 'b'}, {30, 'c'},
                          {40, 'd'}, {50, 'e'}, {60, 'f'}};

    bool has = m.contains(30);          // O(log n), C++20
    std::size_t n = m.count(25);        // 0 or 1 in a map, O(log n)

    auto lo = m.lower_bound(25);        // first key >= 25: 30
    auto hi = m.upper_bound(45);        // first key >  45: 50
    std::cout << "contains(30) = " << std::boolalpha << has << ", count(25) = " << n << '\n';
    std::cout << "lower_bound(25) -> " << lo->first << ", upper_bound(45) -> " << hi->first << '\n';
    std::cout << "keys in [25, 45]:\n";
    for (auto it = lo; it != hi; ++it)  // keys in [25, 45]: 30, 40
        use(it->first, it->second);

    auto [f, l] = m.equal_range(20);    // [20, 30): one element
    std::cout << "equal_range(20) = [" << f->first << ", " << l->first << "): "
              << std::distance(f, l) << " element\n";

    // the neighbours of a key that is not there: nothing a hash map can answer
    auto above = m.lower_bound(33);
    auto below = std::prev(above);
    std::cout << "nearest keys around 33: " << below->first << " below, " << above->first << " above\n";
    std::cout << "smallest key " << m.begin()->first << ", largest key " << m.rbegin()->first << '\n';
    return 0;
}
