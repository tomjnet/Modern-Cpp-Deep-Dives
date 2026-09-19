// std::stack in 10 Minutes - slide 6: push, emplace and growth
// Build: make 06_push_grow
#include <cstdint>
#include <deque>
#include <iostream>
#include <stack>
#include <vector>

// counts how often the address of top() is not the next slot after the previous top:
// on a vector that is a reallocation (everything moved), on a deque a block boundary
template <class Stack>
static long count_jumps(Stack& s, int n) {
    long jumps = 0;
    std::uintptr_t prev = 0;
    for (int i = 0; i < n; ++i) {
        s.push(i);
        auto here = reinterpret_cast<std::uintptr_t>(&s.top());
        if (i > 0 && here != prev + sizeof(int)) ++jumps;
        prev = here;
    }
    return jumps;
}

int main() {
    std::stack<int> s;              // deque underneath
    s.push(10);                     // O(1): next slot of the last block
    s.emplace(20);                  // in place; block full? one new block
    int& top = s.top();
    const void* where = &top;
    s.push(30);                     // top still valid: nothing moved
    std::cout << "deque:  reference taken before push(30) still reads " << top
              << " at " << where << '\n';
    s.pop();
    std::cout << "        &s.top() after push and pop: " << static_cast<const void*>(&s.top())
              << (&s.top() == where ? "  (same address, nothing moved)\n" : "  (moved)\n");

    std::stack<int, std::vector<int>> v;
    v.push(10);                     // O(1) amortized: doubles when full
    int& vt = v.top();
    const void* vwhere = &vt;
    std::cout << "vector: reference taken before push(20) reads " << vt << " at " << vwhere << '\n';
    v.push(20);                     // vt may dangle: the buffer moved
    v.pop();                        // vt is not read again: it may be dangling now
    std::cout << "        &v.top() after push and pop: " << static_cast<const void*>(&v.top())
              << (&v.top() == vwhere ? "  (same address)\n" : "  (different address: the buffer moved)\n");

    // growth pattern over one million pushes
    const int n = 1000000;
    std::stack<int> d;
    std::stack<int, std::vector<int>> w;
    std::cout << "deque  stack: " << count_jumps(d, n) << " address jumps in " << n
              << " pushes (one per new block)\n";
    std::cout << "vector stack: " << count_jumps(w, n) << " address jumps in " << n
              << " pushes (one per doubling)\n";
    return 0;
}
