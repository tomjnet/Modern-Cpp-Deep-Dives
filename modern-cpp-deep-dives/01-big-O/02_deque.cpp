// std::deque (C++98) - double-ended queue: fixed-size blocks plus an index map
//   push/pop at both ends   O(1)          index          O(1) with two indirections
//   insert / erase middle   O(n)          space: blocks + map, no spare doubling like vector
//   references to elements survive push_front/push_back; iterators do not
#include "bigo.h"
#include <deque>

int main() {
    bigo::header("std::deque", "blocks + index map: both ends O(1), indexing O(1) but slower than vector");

    auto make = [](std::size_t n) { std::deque<int> d; for (std::size_t i = 0; i < n; ++i) d.push_back(int(i)); return d; };

    bigo::scale("d[i]", "O(1)", make, [](std::deque<int>& d) { return std::size_t(d[d.size() / 2]); });
    bigo::scale("push_front + pop_front", "O(1)", make, [](std::deque<int>& d) { d.push_front(1); d.pop_front(); return d.size(); });
    bigo::scale("push_back + pop_back", "O(1)", make, [](std::deque<int>& d) { d.push_back(1); d.pop_back(); return d.size(); });
    bigo::scale("insert + erase in middle", "O(n)", make,
                [](std::deque<int>& d) { d.erase(d.insert(d.begin() + std::ptrdiff_t(d.size() / 2), 1)); return d.size(); });
    bigo::scale("range-for sum", "O(n)", make, [](std::deque<int>& d) { std::size_t s = 0; for (int x : d) s += x; return s; });
    return 0;
}
