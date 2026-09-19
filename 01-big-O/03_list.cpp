// std::list (C++98) - doubly linked list: one heap node per element
//   insert / erase at a known iterator  O(1)      splice, reverse   O(1) / O(n)
//   access by position                  O(n)      find              O(n)
//   space: n * (sizeof(T) + 2 pointers) + allocator overhead per node; every step is a cache miss
#include "bigo.h"
#include <iterator>
#include <list>

int main() {
    bigo::header("std::list", "O(1) insert at an iterator, but reaching any position and scanning is O(n)");

    auto make = [](std::size_t n) { std::list<int> l; for (std::size_t i = 0; i < n; ++i) l.push_back(int(i)); return l; };

    bigo::scale("insert + erase at begin()", "O(1)", make, [](std::list<int>& l) { l.erase(l.insert(l.begin(), 1)); return l.size(); });
    bigo::scale("splice one node to front", "O(1)", make,
                [](std::list<int>& l) { l.splice(l.begin(), l, std::prev(l.end())); return std::size_t(l.front()); });
    bigo::scale("push_front + pop_front", "O(1)", make, [](std::list<int>& l) { l.push_front(1); l.pop_front(); return l.size(); });
    bigo::scale("reach the middle (advance)", "O(n)", make,
                [](std::list<int>& l) { auto it = l.begin(); std::advance(it, std::ptrdiff_t(l.size() / 2)); return std::size_t(*it); });
    bigo::scale("range-for sum", "O(n)", make, [](std::list<int>& l) { std::size_t s = 0; for (int x : l) s += x; return s; },
                20'000, 20);   // fewer reps: pointer chasing is far slower than a vector scan
    return 0;
}
