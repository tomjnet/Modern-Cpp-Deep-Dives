// std::string in 10 Minutes - slide 11: build and convert
// Build: make 11_build_convert
#include <charconv>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>

int main() {
    std::string a = "one ", b = "two ", c = "three";

    std::string n = std::to_string(42);       // "42": O(digits)
    int k = std::stoi("123");                 // 123: throws on garbage

    std::string s = "77";
    int v = 0;
    std::from_chars(s.data(), s.data() + s.size(), v);  // no throw, no heap

    std::string msg = std::format("{} items in {:.2f} s", k, 0.5);  // C++20
    std::string big = a + b + c;   // two temporaries: reserve and append

    std::cout << "to_string(42) = \"" << n << "\", stoi(\"123\") = " << k << ", from_chars(\"77\") = " << v << '\n';
    std::cout << "format: \"" << msg << "\"\n";
    std::cout << "a + b + c = \"" << big << "\"\n";

    // stoi throws, from_chars reports an error code instead
    try {
        int never = std::stoi("abc");
        std::cout << "not reached: " << never << '\n';
    } catch (const std::invalid_argument&) {
        std::cout << "stoi(\"abc\") threw std::invalid_argument\n";
    }
    std::string bad = "abc";
    int w = 0;
    auto res = std::from_chars(bad.data(), bad.data() + bad.size(), w);
    std::cout << "from_chars(\"abc\") failed: " << std::boolalpha << (res.ec != std::errc()) << ", no exception\n";

    // building a long string: chained plus vs reserve and append
    std::string piece(20, 'p');
    std::string chained;
    std::size_t reallocations = 0;
    std::size_t last = chained.capacity();
    for (int i = 0; i < 50; ++i) {
        chained = chained + piece;                  // a temporary per plus, then a copy
        if (chained.capacity() != last) { last = chained.capacity(); ++reallocations; }
    }
    std::string reserved;
    reserved.reserve(50 * piece.size());            // one allocation
    const char* before = reserved.data();
    for (int i = 0; i < 50; ++i) reserved += piece;
    std::cout << "50 pieces of 20 chars: chained plus reallocated " << reallocations
              << " times; reserve + append kept one buffer: " << (reserved.data() == before) << '\n';
    return 0;
}
