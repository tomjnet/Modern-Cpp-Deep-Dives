// std::string (C++98) - a vector of char with small-string optimization (SSO)
//   index / size / push_back      O(1) / amortized O(1)     append(str)     O(len(str)) amortized
//   find(substr)                  O(n * m) worst case        substr(pos, k)  O(k) (it copies)
//   compare                       O(common prefix)           space: SSO buffer (15-22 chars) or heap block
#include "bigo.h"
#include <string>

int main() {
    bigo::header("std::string", "contiguous chars like vector; short strings live inside the object (SSO)");

    auto make = [](std::size_t n) { return std::string(n, 'a'); };

    bigo::scale("s[i]", "O(1)", make, [](std::string& s) { return std::size_t(s[s.size() / 2]); });
    bigo::scale("push_back + pop_back", "O(1)", make, [](std::string& s) { s.push_back('b'); s.pop_back(); return s.size(); });
    bigo::scale("find(\"b\") miss", "O(n)", make, [](std::string& s) { return s.find('b'); });
    bigo::scale("compare equal-length", "O(n)", make, [](std::string& s) { std::string t = s; return std::size_t(s == t); });
    bigo::scale("substr(0, 8)", "O(1)", make, [](std::string& s) { return s.substr(0, 8).size(); });   // O(k) with k fixed
    bigo::scale("insert + erase at front", "O(n)", make, [](std::string& s) { s.insert(0, 1, 'z'); s.erase(0, 1); return s.size(); });

    std::string small = "short";
    std::string big(100, 'x');
    std::printf("\nsizeof(std::string) = %zu bytes; capacity of a 5-char string = %zu (SSO, no heap), of 100 chars = %zu\n",
                sizeof(std::string), small.capacity(), big.capacity());
    return 0;
}
