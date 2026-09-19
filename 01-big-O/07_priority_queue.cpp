// std::priority_queue (C++98) - binary heap on top of a vector
//   top      O(1)          push   O(log n)          pop   O(log n)
//   build from n elements  O(n)  (heapify), versus n pushes O(n log n)
//   space: the underlying vector, contiguous, no per-element overhead
#include "bigo.h"
#include <queue>
#include <vector>

int main() {
    bigo::header("std::priority_queue", "binary heap: top O(1), push and pop O(log n), heapify O(n)");

    auto make = [](std::size_t n) {
        std::vector<int> v(n);
        for (std::size_t i = 0; i < n; ++i) v[i] = int((i * 7919) % n);          // shuffled-ish
        return std::priority_queue<int>(v.begin(), v.end());                      // O(n) heapify
    };

    bigo::scale("top", "O(1)", make, [](std::priority_queue<int>& pq) { return std::size_t(pq.top()); });
    bigo::scale("push + pop", "O(log n)", make, [](std::priority_queue<int>& pq) { pq.push(-1); pq.pop(); return pq.size(); });
    bigo::scale("push(max) + pop", "O(log n)", make,
                [](std::priority_queue<int>& pq) { pq.push(1 << 30); pq.pop(); return pq.size(); });

    // building: heapify (O(n)) versus one push per element (O(n log n)); both measured once, no reps
    auto build = [](std::size_t n) { std::vector<int> v(n); for (std::size_t i = 0; i < n; ++i) v[i] = int((i * 7919) % n); return v; };
    bigo::scale("build by heapify", "O(n)", build,
                [](std::vector<int>& v) { std::priority_queue<int> pq(v.begin(), v.end()); return pq.size(); }, 20'000, 5);
    bigo::scale("build by n pushes", "O(n log n)", build,
                [](std::vector<int>& v) { std::priority_queue<int> pq; for (int x : v) pq.push(x); return pq.size(); }, 20'000, 5);
    return 0;
}
