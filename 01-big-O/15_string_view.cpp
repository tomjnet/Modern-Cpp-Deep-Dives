// std::string_view (C++17) - a non-owning (pointer, length) view over characters
//   construct / substr / remove_prefix / remove_suffix   O(1): nothing is copied
//   find / compare                                       O(n), same as string
//   space: 2 words, no allocation; the viewed characters must outlive the view
#include "bigo.h"
#include <cstdio>
#include <string>
#include <string_view>

int main() {
    bigo::header("std::string_view", "a view is two words: slicing is O(1), scanning is still O(n)");

    auto make = [](std::size_t n) { return std::string(n, 'a'); };

    // string::substr copies k characters (O(k)); string_view::substr just moves a pointer and a length (O(1))
    bigo::scale("string.substr(0, 4096) copy", "O(1)", make, [](std::string& s) { return s.substr(0, 4096).size(); });
    bigo::scale("string_view.substr(0, n/2)", "O(1)", make,
                [](std::string& s) { std::string_view v = s; return v.substr(0, v.size() / 2).size(); });
    bigo::scale("string_view remove_prefix", "O(1)", make, [](std::string& s) { std::string_view v = s; v.remove_prefix(v.size() / 2); return v.size(); });
    bigo::scale("string_view.find('b') miss", "O(n)", make, [](std::string& s) { std::string_view v = s; return v.find('b'); });
    bigo::scale("pass by string_view (copy)", "O(1)", make,
                [](std::string& s) { auto len = [](std::string_view v) { return v.size(); }; return len(s); });
    bigo::scale("copy into string, t = s", "O(n)", make,
                [](std::string& s) { static std::string t; t = s; return t.size(); }, 20'000, 50);

    std::printf("\nsizeof(std::string_view) = %zu bytes, sizeof(std::string) = %zu bytes\n", sizeof(std::string_view), sizeof(std::string));
    return 0;
}
