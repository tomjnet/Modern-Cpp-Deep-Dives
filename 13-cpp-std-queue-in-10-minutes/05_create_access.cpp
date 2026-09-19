// std::queue in 10 Minutes - slide 5: create and access
// Build: make 05_create_access
#include <cstddef>
#include <deque>
#include <iostream>
#include <queue>
#include <utility>

int main() {
    std::queue<int> a;                    // empty, a deque<int> inside
    std::deque<int> d{10, 20, 30, 40};
    std::queue<int> b(d);                 // copies the deque into c

    int f = b.front();     // 10: the oldest element, O(1)
    int l = b.back();      // 40: the newest element, O(1)
    bool e = a.empty();    // true, O(1)
    std::size_t n = b.size();   // 4, O(1)
    // no b[i], no at(), no begin(): only the two ends are visible

    std::cout << "b.front() = " << f << "  (the oldest, next to leave)\n";
    std::cout << "b.back()  = " << l << "  (the newest, last pushed)\n";
    std::cout << "a.empty() = " << std::boolalpha << e << '\n';
    std::cout << "b.size()  = " << n << '\n';

    // the adapter adds nothing on top of its container
    std::cout << "sizeof(std::queue<int>) = " << sizeof(std::queue<int>)
              << ", sizeof(std::deque<int>) = " << sizeof(std::deque<int>) << '\n';

    // b holds its own copy: the source deque is untouched by the queue
    d.push_back(50);
    std::cout << "after d.push_back(50): d.size() = " << d.size() << ", b.size() = " << b.size() << '\n';

    // moving the deque in avoids the copy; d is left valid but unspecified (empty in practice)
    std::queue<int> m(std::move(d));
    std::cout << "std::queue<int> m(std::move(d)): m.size() = " << m.size()
              << ", m.back() = " << m.back() << '\n';

    // b.front() on an empty queue is undefined behaviour, so the guard is always the same:
    if (!a.empty()) std::cout << a.front() << '\n';
    else            std::cout << "a is empty: front() and back() must not be called\n";
    return 0;
}
