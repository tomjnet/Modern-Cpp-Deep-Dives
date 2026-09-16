// std::string in 10 Minutes - slide 10: invalidation and string_view
// Build: make 10_invalidation_views
// Dangling pointers and views are only printed as addresses here, never read.
#include <iostream>
#include <string>
#include <string_view>

int main() {
    std::string s = "hello world";
    char& r = s[0];
    const char* p = s.data();
    std::cout << "before reserve: r = '" << r << "', chars at " << static_cast<const void*>(p) << '\n';

    s.reserve(64);               // reallocates: r and p are dangling
                                 // r = 'H' here is undefined behaviour
    std::cout << "after reserve(64): chars at " << static_cast<const void*>(s.data())
              << ", old pointer " << static_cast<const void*>(p) << " is dangling\n";

    std::string_view v = s;                 // O(1): pointer + size, no copy
    std::string_view w = v.substr(6, 5);    // "world": O(1), no copy
    std::cout << "v = \"" << v << "\", w = \"" << w << "\", sizeof(string_view) = " << sizeof v
              << ", w points into s: " << std::boolalpha << (w.data() == s.data() + 6) << '\n';

    s += "!!!";                  // 14 < 64: no reallocation, v and w live
    std::cout << "after += \"!!!\": v = \"" << v << "\", w = \"" << w << "\" (still valid, same buffer)\n";
    s.append(100, 'x');          // 114 > 64: reallocates, v and w dangle
    std::cout << "after append(100, 'x'): chars moved to " << static_cast<const void*>(s.data())
              << ", v and w still point at " << static_cast<const void*>(v.data()) << ": dangling\n";
    v = s;                       // rebind the view to the live buffer before using it again
    std::cout << "rebound view: size " << v.size() << ", first 14 chars \"" << v.substr(0, 14) << "\"\n";

    // a view of a literal: no string object at all
    std::string_view lit = "static text";
    std::cout << "view of a literal: \"" << lit << "\", size " << lit.size() << '\n';
    return 0;
}
