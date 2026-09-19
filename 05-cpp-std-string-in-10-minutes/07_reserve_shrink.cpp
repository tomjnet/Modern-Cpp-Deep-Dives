// std::string in 10 Minutes - slide 7: reserve, resize and shrink
// Build: make 07_reserve_shrink
#include <iostream>
#include <string>

static void show(const char* label, const std::string& s) {
    std::cout << label << ": size " << s.size() << ", capacity " << s.capacity()
              << ", chars at " << static_cast<const void*>(s.data()) << '\n';
}

int main() {
    std::string s;
    show("empty           ", s);
    s.reserve(1000);             // one allocation up front
    show("reserve(1000)   ", s);
    const char* before = s.data();
    for (int i = 0; i < 1000; ++i) s.push_back('a');   // no copies
    show("1000 push_backs ", s);
    std::cout << "pointer unchanged during the loop: " << std::boolalpha << (s.data() == before) << '\n';

    s.pop_back();                // O(1), capacity unchanged
    show("pop_back        ", s);
    s.resize(10);                // size 10, capacity still 1000
    show("resize(10)      ", s);
    s.clear();                   // size 0, capacity still 1000
    show("clear           ", s);
    s.shrink_to_fit();           // ask to release: back to 15, no heap
    show("shrink_to_fit   ", s);

    std::size_t c = s.capacity();   // chars that fit before the next copy
    std::cout << "capacity now " << c << ": the next " << c << " chars need no allocation\n";

    // the chars are back inside the object once they fit the small buffer
    const char* obj_begin = reinterpret_cast<const char*>(&s);
    bool inside = s.data() >= obj_begin && s.data() < obj_begin + sizeof(s);
    std::cout << "chars stored inside the object after shrink_to_fit: " << inside << '\n';
    return 0;
}
