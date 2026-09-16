// std::queue in 10 Minutes - slide 9: no iteration, no clear
// Build: make 09_no_iteration
#include <deque>
#include <iostream>
#include <queue>

static void use(int x) { std::cout << ' ' << x; }

int main() {
    std::queue<int> q;
    for (int i = 1; i <= 5; ++i) q.push(i);
    std::cout << "q has " << q.size() << " elements, front " << q.front() << ", back " << q.back() << '\n';

    // no begin() / end(): no range-for, no std::find, on purpose
    // no clear(): swap with an empty queue, or assign {}
    std::queue<int>().swap(q);   // O(1) swap, then O(n) destruction
    std::cout << "after swap with an empty queue: size " << q.size() << '\n';
    q.push(7);
    q = {};                      // same effect
    std::cout << "after q = {}: size " << q.size() << '\n';
    // for (int x : q) use(x);   // does not compile: std::queue has no begin() / end()

    // need to look at everything? use std::deque directly
    std::deque<int> d{1, 2, 3};
    std::cout << "deque:";
    for (int x : d) use(x);      // O(n)
    d.push_back(4);              // still a FIFO
    d.pop_front();
    std::cout << "\nafter push_back(4) and pop_front():";
    for (int x : d) use(x);
    std::cout << "\nthe deque also has d[1] = " << d[1] << " and clear(); the queue hides them on purpose\n";
    d.clear();
    std::cout << "d.clear(): size " << d.size() << '\n';
    return 0;
}
