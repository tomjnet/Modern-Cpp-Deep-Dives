// std::deque in 10 Minutes - slide 8: insert and erase in the middle
// Build: make 08_insert_erase
#include <deque>
#include <iostream>

static void show(const char* label, const std::deque<int>& d) {
    std::cout << label << ": ";
    for (int x : d) std::cout << x << ' ';
    std::cout << "(size " << d.size() << ")\n";
}

int main() {
    std::deque<int> d{10, 20, 30, 40, 50, 60};
    show("start                 ", d);

    d.insert(d.begin() + 2, 99);  // moves 10, 20 (shorter side)
                                  // O(min(i, n - i)), still O(n)
    show("insert(begin()+2, 99) ", d);
    d.erase(d.begin() + 4);       // shorter side fills the gap
    show("erase(begin()+4)      ", d);

    d.insert(d.begin(), 1);       // same as push_front: O(1)
    show("insert(begin(), 1)    ", d);
    d.erase(d.end() - 1);         // same as pop_back:   O(1)
    show("erase(end()-1)        ", d);

    // which side moves: the front side is shorter here, so the elements before the position shift
    // (their addresses change) while the elements after it stay where they were
    std::deque<int> e{1, 2, 3, 4, 5, 6, 7, 8};
    const int* before = &e[1];   // on the short side: value 2
    const int* after = &e[6];    // on the long side:  value 7
    e.insert(e.begin() + 2, 99);
    std::cout << "insert at index 2 of 8: value 2 (front side) "
              << (&e[1] != before ? "moved one slot toward the front" : "did not move") << ", value 7 (back side) "
              << (&e[7] == after ? "stayed in place" : "moved") << '\n';
    return 0;
}
