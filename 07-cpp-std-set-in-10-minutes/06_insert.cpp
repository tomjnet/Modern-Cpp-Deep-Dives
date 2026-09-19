// std::set in 10 Minutes - slide 6: insert, emplace and rebalancing
// Build: make 06_insert
//
// After the slide's lines, a measurement: inserting sorted keys with a correct hint (end()) is
// amortized O(1) per key, while the plain insert walks O(log n) from the root every time.
#include <chrono>
#include <iostream>
#include <set>

static void print(const char* name, const std::set<int>& s) {
    std::cout << name << " = {";
    for (int x : s) std::cout << ' ' << x;
    std::cout << " }\n";
}

int main() {
    std::set<int> s{10, 20, 30};

    auto [it, ok] = s.insert(25);   // O(log n): walk down, link a red
                                    // leaf, recolor or rotate upward
    auto [it2, dup] = s.insert(20); // dup == false: nothing changes
    s.emplace(40);                  // builds the key inside the node

    auto hint = s.end();            // hint just after the position:
    s.insert(hint, 50);             // amortized O(1), not O(log n)

    std::cout << std::boolalpha;
    std::cout << "insert(25): *it = " << *it << ", inserted = " << ok << '\n';
    std::cout << "insert(20): *it2 = " << *it2 << ", inserted = " << dup << "  (already there)\n";
    print("s", s);

    // measurement: sorted bulk load, with and without a hint
    using clock = std::chrono::steady_clock;
    const long long n = 2'000'000;

    std::set<long long> plain;
    auto t0 = clock::now();
    for (long long i = 0; i < n; ++i) plain.insert(i);            // O(log n) each
    auto t1 = clock::now();

    std::set<long long> hinted;
    for (long long i = 0; i < n; ++i) hinted.insert(hinted.end(), i);  // amortized O(1) each
    auto t2 = clock::now();

    auto ms = [](auto a, auto b) { return std::chrono::duration<double, std::milli>(b - a).count(); };
    std::cout << "\n" << n << " sorted keys\n";
    std::cout << "  insert(key):        " << ms(t0, t1) << " ms\n";
    std::cout << "  insert(end(), key): " << ms(t1, t2) << " ms  (correct hint: no walk from the root)\n";
    std::cout << "  both sets equal: " << (plain == hinted) << '\n';
    std::cout << "  the gap is the O(log n) walk; the node allocation, paid by both, dominates the rest\n";
    return 0;
}
