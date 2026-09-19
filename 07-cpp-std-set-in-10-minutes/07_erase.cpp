// std::set in 10 Minutes - slide 7: erase and releasing memory
// Build: make 07_erase
#include <cstddef>
#include <iostream>
#include <set>

static void print(const char* step, const std::set<int>& s) {
    std::cout << step << " -> {";
    for (int x : s) std::cout << ' ' << x;
    std::cout << " }  size " << s.size() << '\n';
}

int main() {
    std::set<int> s{10, 20, 30, 40, 50};
    print("start", s);

    std::size_t n = s.erase(30);    // by key: O(log n), returns 0 or 1
    std::cout << "erase(30) removed " << n << " key\n";
    print("erase(30)", s);
    std::cout << "erase(99) removed " << s.erase(99) << " keys (not present)\n";

    s.erase(s.find(10));            // by iterator: amortized O(1)
    print("erase(find(10))", s);

    s.erase(s.begin(), s.find(50)); // range: O(k) once found
    print("erase(begin, find(50))", s);

    s.insert({35, 45, 55, 65});
    print("insert {35, 45, 55, 65}", s);
    std::erase_if(s, [](int x) { return x > 40; });  // C++20, O(n)
    print("erase_if(x > 40)", s);

    s.clear();                      // frees every node: O(n)
    print("clear()", s);
    // no capacity, no reserve, no shrink_to_fit: one node per key
    std::cout << "empty: " << std::boolalpha << s.empty() << "  (no capacity to shrink: every node was freed)\n";
    return 0;
}
