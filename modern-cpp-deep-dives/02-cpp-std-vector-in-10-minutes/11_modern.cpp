// std::vector in 10 Minutes - slide 11: emplace_back, moves and modern helpers
// Build: make 11_modern   (needs C++20 for std::erase_if)
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
    std::string tmp = "Bjarne";
    std::vector<std::string> names;
    names.emplace_back("Ada", 3);          // constructs in place: "Ada"
    names.push_back(std::move(tmp));       // moves, no copy
    std::cout << "names: " << names[0] << ", " << names[1] << "  (tmp after move: \"" << tmp << "\")\n";

    std::vector<int> v{1, 2, 3, 4, 5, 6};
    std::erase_if(v, [](int x) { return x % 2 == 0; });   // C++20
    // pre-C++20: v.erase(std::remove_if(...), v.end());
    std::cout << "erase_if evens: ";
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';

    std::vector<bool> flags(8);     // packed bits, not a real bool*
    // bool& ref = flags[0];        // does not compile: operator[] returns a proxy, not a bool&
    auto proxy = flags[0];          // this is what you get instead
    proxy = true;
    std::cout << "vector<bool>: flags[0] = " << flags[0] << ", the proxy object is " << sizeof(proxy)
              << " bytes (not a bool&), and the 8 flags share one byte of storage\n";

    std::vector<char> real(8, 0);   // real bytes, real references, real pointers from data()
    char& r = real[0];
    r = 1;
    std::cout << "vector<char>: real[0] = " << static_cast<int>(real[0]) << ", data() = "
              << static_cast<const void*>(real.data()) << '\n';
    return 0;
}
