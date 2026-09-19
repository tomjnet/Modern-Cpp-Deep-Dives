// std::map in 10 Minutes - slide 5: create and access
// Build: make 05_create_access
//
// operator[] inserts a default value when the key is missing; at() throws; find() returns end().
// Every one of them is a walk from the root: O(log n).
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

static void print(const char* label, const std::map<std::string, int>& m) {
    std::cout << label << " size " << m.size() << ':';
    for (const auto& [key, value] : m) std::cout << ' ' << key << '=' << value;
    std::cout << '\n';
}

int main() {
    std::map<std::string, int> a;                     // empty: header only
    std::map<std::string, int> b{{"bob", 3}, {"amy", 5}};  // amy, bob
    print("a", a);
    print("b", b);                                        // sorted: amy before bob

    int x = b["amy"];         // O(log n): 5
    int y = b["zoe"];         // O(log n): inserts {"zoe", 0}, returns 0
    int z = b.at("bob");      // O(log n): 3, throws std::out_of_range
    auto it = b.find("cat");  // O(log n): b.end() when missing
    // keys are const: it->first cannot change, it->second can

    std::cout << "b[\"amy\"] = " << x << ", b[\"zoe\"] = " << y << ", b.at(\"bob\") = " << z << '\n';
    std::cout << "find(\"cat\") == end(): " << std::boolalpha << (it == b.end()) << '\n';
    print("b after b[\"zoe\"]", b);                       // zoe was inserted by operator[]

    try {
        static_cast<void>(b.at("cat"));   // the value is never reached: at() throws first
    } catch (const std::out_of_range& e) {
        std::cout << "at(\"cat\") threw std::out_of_range: " << e.what() << '\n';
    }

    auto amy = b.find("amy");
    amy->second = 6;          // the value is mutable through an iterator
    // amy->first = "ann";    // does not compile: the key is const inside the pair
    print("b after amy->second = 6", b);
    return 0;
}
