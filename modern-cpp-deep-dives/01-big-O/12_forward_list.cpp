// std::forward_list (C++11) - singly linked list, the leanest node container
//   push_front / pop_front         O(1)      insert_after / erase_after (known iterator)   O(1)
//   no size(): counting is O(n)              no push_back, no reverse iteration
//   space: n * (sizeof(T) + 1 pointer) in separate nodes; the object itself is one pointer
#include "bigo.h"
#include <forward_list>
#include <iterator>

int main() {
    bigo::header("std::forward_list", "one pointer per node: O(1) at the front and after a known iterator, O(n) for everything else");

    auto make = [](std::size_t n) { std::forward_list<int> f; for (std::size_t i = 0; i < n; ++i) f.push_front(int(i)); return f; };

    bigo::scale("push_front + pop_front", "O(1)", make, [](std::forward_list<int>& f) { f.push_front(1); f.pop_front(); return std::size_t(f.front()); });
    bigo::scale("insert_after + erase_after", "O(1)", make,
                [](std::forward_list<int>& f) { f.insert_after(f.begin(), 1); f.erase_after(f.begin()); return std::size_t(f.front()); });
    bigo::scale("count elements (no size)", "O(n)", make,
                [](std::forward_list<int>& f) { return std::size_t(std::distance(f.begin(), f.end())); }, 20'000, 20);
    bigo::scale("range-for sum", "O(n)", make,
                [](std::forward_list<int>& f) { std::size_t s = 0; for (int x : f) s += std::size_t(x); return s; }, 20'000, 20);
    return 0;
}
