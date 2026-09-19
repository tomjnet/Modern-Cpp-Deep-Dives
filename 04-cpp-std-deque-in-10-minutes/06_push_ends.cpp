// std::deque in 10 Minutes - slide 6: push_front, push_back and growth
// Build: make 06_push_ends
#include <deque>
#include <iostream>

static void show(const char* label, const std::deque<int>& d) {
    std::cout << label << ": ";
    for (int x : d) std::cout << x << ' ';
    std::cout << "(size " << d.size() << ")\n";
}

int main() {
    std::deque<int> d{10, 20, 30, 40};
    show("start          ", d);

    d.push_back(50);    // O(1): next slot in the last block
    show("push_back(50)  ", d);
    d.push_front(5);    // O(1): slot before the first element
                        // block full? allocate one more block
                        // map full?   reallocate the map only
    show("push_front(5)  ", d);

    int& first = d.front();
    const int* where = &first;
    d.push_back(60);    // first still valid, nothing moved
    show("push_back(60)  ", d);
    std::cout << "reference to front taken before push_back: value " << first
              << ", address " << (where == &d.front() ? "unchanged" : "changed") << " (elements never move)\n";

    // grow from both ends: every push is O(1), the element addresses stay put
    std::deque<int> g;
    for (int i = 1; i <= 5000; ++i) { g.push_back(i); g.push_front(-i); }
    const int* mid = &g[g.size() / 2];
    int value = *mid;
    for (int i = 0; i < 5000; ++i) { g.push_back(0); g.push_front(0); }
    std::cout << "after 10000 more pushes at both ends the element at the old middle is still " << *mid
              << (value == *mid ? " (same address, same value)" : " (moved!)") << ", size " << g.size() << '\n';
    return 0;
}
