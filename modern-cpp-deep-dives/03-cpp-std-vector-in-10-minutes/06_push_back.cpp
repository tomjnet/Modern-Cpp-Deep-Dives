// std::vector in 10 Minutes - slide 6: push_back and growth
// Build: make 06_push_back
#include <iostream>
#include <vector>

static void show(const char* label, const std::vector<int>& v) {
    std::cout << label << ": size " << v.size() << ", capacity " << v.capacity()
              << ", data at " << static_cast<const void*>(v.data()) << '\n';
}

int main() {
    std::vector<int> v{1, 2, 3, 4};   // size 4, capacity 4
    show("start        ", v);

    v.push_back(5);   // full: allocate 8, move 1..4, free old
    show("push_back(5) ", v);          // capacity grew, data pointer changed

    v.push_back(6);   // spare room: O(1), no reallocation
    show("push_back(6) ", v);          // same data pointer

    std::cout << "v.size()     = " << v.size() << '\n';       // 6
    std::cout << "v.capacity() = " << v.capacity() << '\n';   // 8 (implementation dependent)

    // watch the geometric growth: capacity only changes when size catches up with it
    std::vector<int> g;
    std::size_t last = g.capacity();
    for (int i = 0; i < 100; ++i) {
        g.push_back(i);
        if (g.capacity() != last) {
            last = g.capacity();
            std::cout << "reallocation at size " << g.size() << " -> capacity " << last << '\n';
        }
    }
    return 0;
}
