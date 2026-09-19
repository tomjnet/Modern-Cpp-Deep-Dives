// std::vector in 10 Minutes - slide 8: insert and erase in the middle
// Build: make 08_insert_erase
#include <iostream>
#include <vector>

static void show(const char* label, const std::vector<int>& v) {
    std::cout << label << ": ";
    for (int x : v) std::cout << x << ' ';
    std::cout << "(size " << v.size() << ")\n";
}

int main() {
    std::vector<int> v{10, 20, 30, 40};
    show("start                ", v);

    v.insert(v.begin() + 1, 99);  // shifts 20,30,40 right: O(n)
    show("insert(begin()+1, 99)", v);

    v.erase(v.begin());           // shifts everything left: O(n)
    show("erase(begin())       ", v);

    v.pop_back();                 // O(1), nothing to move
    show("pop_back()           ", v);

    v.insert(v.end(), 50);        // same as push_back: O(1)
    show("insert(end(), 50)    ", v);
    return 0;
}
