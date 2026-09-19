// std::string in 10 Minutes - slide 8: insert, erase, replace and substr
// Build: make 08_insert_erase
#include <iostream>
#include <string>

static void show(const char* label, const std::string& s) {
    std::cout << label << ": \"" << s << "\" size " << s.size() << ", capacity " << s.capacity() << '\n';
}

int main() {
    std::string s = "abcdef";
    show("start                ", s);

    s.insert(2, "XY");           // "abXYcdef": tail shifts right, O(n - i)
    show("insert(2, \"XY\")      ", s);
    s.erase(2, 2);               // "abcdef": tail shifts left, O(n - i)
    show("erase(2, 2)          ", s);
    s.replace(0, 2, "AB");       // "ABcdef": same length, nothing shifts
    show("replace(0, 2, \"AB\")  ", s);

    std::string t = s.substr(2, 3);   // "cde": copies 3 chars, O(k)
    show("t = substr(2, 3)     ", t);
    std::cout << "t has its own chars: " << std::boolalpha << (t.data() != s.data() + 2) << '\n';

    s.insert(s.size(), "!");     // at the end: same as append, O(1)
    show("insert at the end    ", s);
    s.erase(s.size() - 1);       // at the end: same as pop_back, O(1)
    show("erase at the end     ", s);

    // no reallocation happened above: everything fit in the small buffer
    // count what a middle insert really moves: the tail after the position
    std::string big(20, '.');
    big.reserve(64);                                 // spare room, so only the shift is measured
    const char* before = big.data();
    big.insert(5, "XYZ");                            // 15 tail chars shift right by 3
    std::cout << "insert(5, \"XYZ\") into 20 dots: " << big << " (moved " << 20 - 5
              << " tail chars, pointer unchanged: " << (big.data() == before) << ")\n";
    return 0;
}
