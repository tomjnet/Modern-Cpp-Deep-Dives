// std::stack in 10 Minutes - slide 8: choosing the container underneath
// Build: make 08_choose_container
#include <chrono>
#include <cstdint>
#include <deque>
#include <iostream>
#include <list>
#include <stack>
#include <utility>
#include <vector>

// pushes n ints then pops them all; returns milliseconds
template <class Stack>
static double time_push_pop(int n) {
    Stack s;
    auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < n; ++i) s.push(i);
    long long sum = 0;
    while (!s.empty()) { sum += s.top(); s.pop(); }
    auto t1 = std::chrono::steady_clock::now();
    if (sum != static_cast<long long>(n) * (n - 1) / 2) std::cout << "checksum mismatch\n";
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

int main() {
    std::stack<int> a;                          // std::deque<int>: default
    std::stack<int, std::vector<int>> b;        // fastest, contiguous
    std::stack<int, std::list<int>> c;          // one allocation per push

    std::vector<int> buf;
    buf.reserve(1024);                          // size the buffer first
    std::stack<int, std::vector<int>> d(std::move(buf));  // no realloc
    // any type with back(), push_back(), pop_back() works

    std::cout << "sizeof: deque stack " << sizeof(a) << " B, vector stack " << sizeof(b)
              << " B, list stack " << sizeof(c) << " B\n";

    // d never reallocates while it stays within the reserved 1024: the address of top() advances by one slot
    long jumps = 0;
    std::uintptr_t prev = 0;
    for (int i = 0; i < 1024; ++i) {
        d.push(i);
        auto here = reinterpret_cast<std::uintptr_t>(&d.top());
        if (i > 0 && here != prev + sizeof(int)) ++jumps;
        prev = here;
    }
    std::cout << "pre-sized vector stack: " << jumps << " reallocations in 1024 pushes\n";

    const int n = 2000000;
    std::cout << "push and pop " << n << " ints:\n";
    std::cout << "  deque  stack: " << time_push_pop<std::stack<int>>(n) << " ms\n";
    std::cout << "  vector stack: " << time_push_pop<std::stack<int, std::vector<int>>>(n) << " ms\n";
    std::cout << "  list   stack: " << time_push_pop<std::stack<int, std::list<int>>>(n)
              << " ms (one allocation per push)\n";
    return 0;
}
