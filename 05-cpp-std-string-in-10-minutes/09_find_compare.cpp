// std::string in 10 Minutes - slide 9: find and compare
// Build: make 09_find_compare
#include <compare>
#include <iostream>
#include <string>

int main() {
    std::string s = "the quick brown fox";

    std::size_t i = s.find("brown");    // 10: O(n * m) worst, memchr fast
    std::size_t j = s.rfind('o');       // 17: scans from the back
    bool none = s.find("cat") == std::string::npos;   // npos: not found

    bool a = s.starts_with("the");      // C++20, O(m)
    bool b = s.ends_with("fox");        // C++20, O(m)
                                        // C++23 adds s.contains("quick")

    bool eq = (s == "the quick brown fox");   // O(min(n, m)), size first
    auto ord = s <=> "zebra";           // C++20: std::strong_ordering::less

    std::cout << std::boolalpha;
    std::cout << "s = \"" << s << "\"\n";
    std::cout << "find(\"brown\")  = " << i << '\n';
    std::cout << "rfind('o')     = " << j << '\n';
    std::cout << "find(\"cat\") == npos: " << none << "  (npos = " << std::string::npos << ")\n";
    std::cout << "starts_with(\"the\") = " << a << ", ends_with(\"fox\") = " << b << '\n';
    std::cout << "s == \"the quick brown fox\": " << eq << '\n';
    std::cout << "s <=> \"zebra\" is less: " << (ord == std::strong_ordering::less) << '\n';

    // equality checks the size first: different lengths are decided without touching the bytes
    std::string x(1000000, 'a');
    std::string y(1000001, 'a');
    std::cout << "1000000 a vs 1000001 a: equal " << (x == y) << " (sizes differ, decided in O(1))\n";

    // comparison is by char value, not by locale and not case aware
    std::cout << "\"Zebra\" < \"apple\": " << (std::string("Zebra") < "apple") << " ('Z' is 90, 'a' is 97)\n";
    return 0;
}
