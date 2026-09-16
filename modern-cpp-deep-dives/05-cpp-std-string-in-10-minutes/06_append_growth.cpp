// std::string in 10 Minutes - slide 6: push_back, append and growth
// Build: make 06_append_growth
#include <iostream>
#include <string>

static void show(const char* label, const std::string& s) {
    std::cout << label << ": size " << s.size() << ", capacity " << s.capacity()
              << ", chars at " << static_cast<const void*>(s.data()) << '\n';
}

int main() {
    std::string s = "hello";     // size 5, capacity 15: inside the object
    show("start               ", s);

    s.push_back('!');            // O(1): next free slot, no allocation
    show("push_back('!')      ", s);                 // same pointer
    s += " world";               // O(k): 12 chars, still fits in 15
    show("+= \" world\"          ", s);              // same pointer
    s.append(", C++");           // 17 > 15: allocate 30, copy 15, point
    show("append(\", C++\")     ", s);                // pointer moved to the heap

    const char* p = s.data();
    s += " again and again";     // 33 > 30: allocate 60, copy 30, free
                                 // p is dangling now: the chars moved
    show("+= \" again and again\"", s);
    std::cout << "old pointer " << static_cast<const void*>(p) << " vs new "
              << static_cast<const void*>(s.data()) << ": p is dangling, only its value is printed\n";
    std::cout << "s = \"" << s << "\"\n";

    // watch the geometric growth: capacity only changes when the size catches up with it
    std::string g;
    std::size_t last = g.capacity();
    std::size_t copies = 0;                          // chars copied by reallocations
    std::cout << "empty string: capacity " << last << '\n';
    for (int i = 0; i < 1000; ++i) {
        g.push_back('a');
        if (g.capacity() != last) {
            copies += g.size() - 1;                  // the old contents were moved
            last = g.capacity();
            std::cout << "reallocation at size " << g.size() << " -> capacity " << last << '\n';
        }
    }
    std::cout << "1000 push_backs copied " << copies << " chars in total (under 2n = 2000): amortized O(1)\n";
    return 0;
}
