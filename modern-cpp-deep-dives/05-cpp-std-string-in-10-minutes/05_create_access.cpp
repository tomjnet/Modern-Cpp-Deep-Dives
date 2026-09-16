// std::string in 10 Minutes - slide 5: create and access
// Build: make 05_create_access
#include <iostream>
#include <stdexcept>
#include <string>

static void show(const char* label, const std::string& s) {
    std::cout << label << ": \"" << s << "\" size " << s.size() << ", capacity " << s.capacity()
              << ", chars at " << static_cast<const void*>(s.data()) << '\n';
}

int main() {
    std::string a;                    // empty: size 0, capacity 15, no heap
    std::string b(3, 'x');            // "xxx"
    std::string c = "hello";          // copies the 5 chars into the object
    std::string d{"hello world", 5};  // first 5 chars: "hello"

    char x = c[1];               // 'e': O(1), one pointer add, unchecked
    char y = c.at(4);            // 'o', throws std::out_of_range
    const char* p = c.c_str();   // O(1), same as data(), null terminated
    std::size_t n = c.size();    // 5, O(1); length() is the same count

    show("a", a);
    show("b", b);
    show("c", c);
    show("d", d);
    std::cout << "c[1] = " << x << ", c.at(4) = " << y << ", c.front() = " << c.front()
              << ", c.back() = " << c.back() << '\n';
    std::cout << "c.c_str() = \"" << p << "\", c.size() = " << n << ", c.length() = " << c.length() << '\n';
    std::cout << "c.c_str() == c.data(): " << std::boolalpha << (p == c.data()) << '\n';
    std::cout << "byte after the last char: " << static_cast<int>(p[n]) << " (always 0)\n";

    // the literal was copied: the string does not point at it
    const char* literal = "hello";
    std::cout << "c owns its chars: " << (c.data() != literal) << '\n';

    // small string optimization: the chars live inside the object itself
    const char* obj_begin = reinterpret_cast<const char*>(&c);
    const char* obj_end = obj_begin + sizeof(c);
    bool inside = c.data() >= obj_begin && c.data() < obj_end;
    std::cout << "sizeof(std::string) = " << sizeof(std::string) << ", \"hello\" stored inside the object: "
              << inside << '\n';

    // at() checks the bounds, operator[] does not
    try {
        char never = c.at(99);
        std::cout << "not reached: " << never << '\n';
    } catch (const std::out_of_range&) {
        std::cout << "c.at(99) threw std::out_of_range\n";
    }
    // char bad = c[99];   // compiles, undefined behaviour: no bounds check, so it is not executed here
    return 0;
}
