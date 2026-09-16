// std::queue in 10 Minutes - slide 8: choosing the backend
// Build: make 08_backends
#include <chrono>
#include <deque>
#include <iostream>
#include <list>
#include <queue>
#include <vector>

// push n then pop n on any queue type; returns microseconds
template <class Queue>
static long long round_trip(int n) {
    Queue q;
    const auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < n; ++i) q.push(i);
    long long sum = 0;
    while (!q.empty()) { sum += q.front(); q.pop(); }
    const auto t1 = std::chrono::steady_clock::now();
    if (sum != static_cast<long long>(n) * (n - 1) / 2) std::cout << "unexpected sum\n";
    return std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
}

int main() {
    std::queue<int> a;                    // std::deque<int> underneath
    std::queue<int, std::list<int>> b;    // one node per element
    std::queue<int, std::vector<int>> c;  // declares fine, but c.pop()
                                          // fails: no pop_front()
    // the container needs front(), back(), push_back(), pop_front()
    // deque: blocks of 128 ints, O(1) both ends, cache friendly
    // list:  one allocation per push, pointer chasing on every pop

    a.push(1); b.push(1);
    c.push(1);   // push, front, back, size and empty work on the vector backend
    // c.pop();  // does not compile: std::vector has no pop_front()
    std::cout << "deque backend: size " << a.size() << ", list backend: size " << b.size()
              << ", vector backend: size " << c.size() << " (push works, pop would not compile)\n";

    // the adapter is exactly its container
    std::cout << "sizeof queue<int, deque>  = " << sizeof(std::queue<int>) << '\n';
    std::cout << "sizeof queue<int, list>   = " << sizeof(std::queue<int, std::list<int>>) << '\n';
    std::cout << "sizeof queue<int, vector> = " << sizeof(std::queue<int, std::vector<int>>) << '\n';

    // same Big-O, different constants: 2M push then 2M pop on each backend
    const int n = 2000000;
    const long long td = round_trip<std::queue<int>>(n);
    const long long tl = round_trip<std::queue<int, std::list<int>>>(n);
    std::cout << "2M push+pop on deque: " << td << " us, on list: " << tl << " us, list/deque = "
              << (td > 0 ? static_cast<double>(tl) / static_cast<double>(td) : 0.0) << '\n';
    return 0;
}
