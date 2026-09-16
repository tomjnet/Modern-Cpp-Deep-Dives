// std::map in 10 Minutes - slide 6: insert, emplace and rebalancing
// Build: make 06_insert
//
// Every insert walks down from the root in O(log n) and attaches a red leaf; the fix-up is O(1)
// amortized. A correct hint (an iterator right after the new key) makes the insert amortized O(1).
#include <chrono>
#include <iostream>
#include <map>
#include <string>

static void print(const char* label, const std::map<int, std::string>& m) {
    std::cout << label << ':';
    for (const auto& [key, value] : m) std::cout << ' ' << key << '=' << value;
    std::cout << '\n';
}

int main() {
    std::map<int, std::string> m;

    m.insert({40, "d"});          // O(log n) walk, new red leaf, rebalance
    m.emplace(20, "b");           // builds the node in place
    auto [it, ok] = m.insert({40, "x"});  // ok == false: 40 already there
    m.try_emplace(60, "f");       // no temporary when the key exists
    m.insert_or_assign(40, "D");  // update in place, no second lookup

    auto hint = m.end();
    m.insert(hint, {70, "g"});    // correct hint: amortized O(1)

    std::cout << "insert({40, \"x\"}) -> ok = " << std::boolalpha << ok << ", it->second = " << it->second << '\n';
    print("m", m);

    // measurement: appending ascending keys with hint = end() versus a plain insert
    constexpr int n = 1000000;
    std::map<int, int> plain, hinted;
    auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < n; ++i) plain.insert({i, i});
    auto t1 = std::chrono::steady_clock::now();
    for (int i = 0; i < n; ++i) hinted.insert(hinted.end(), {i, i});
    auto t2 = std::chrono::steady_clock::now();
    auto ms = [](auto a, auto b) { return std::chrono::duration<double, std::milli>(b - a).count(); };
    std::cout << n << " ascending inserts: plain " << ms(t0, t1) << " ms, hinted " << ms(t1, t2)
              << " ms (hint skips the O(log n) walk)\n";
    return 0;
}
