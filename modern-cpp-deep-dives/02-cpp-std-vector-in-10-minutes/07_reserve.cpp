// std::vector in 10 Minutes - slide 7: reserve, capacity and shrink_to_fit
// Build: make 07_reserve
#include <iostream>
#include <vector>

static void show(const char* label, const std::vector<int>& v) {
    std::cout << label << ": size " << v.size() << ", capacity " << v.capacity() << '\n';
}

int main() {
    std::vector<int> v;
    v.reserve(1000);                 // one allocation, size stays 0
    show("after reserve(1000)   ", v);

    const int* block = v.data();
    for (int i = 0; i < 1000; ++i)
        v.push_back(i);              // never reallocates
    show("after 1000 push_back  ", v);
    std::cout << "block moved during the loop? " << (v.data() == block ? "no" : "yes") << '\n';

    v.clear();                       // size 0, capacity still 1000
    show("after clear()         ", v);

    v.shrink_to_fit();               // ask to release the block
    show("after shrink_to_fit() ", v);

    v.reserve(1000);
    std::vector<int>().swap(v);      // pre-C++11 way to free it
    show("after swap with empty ", v);
    return 0;
}
