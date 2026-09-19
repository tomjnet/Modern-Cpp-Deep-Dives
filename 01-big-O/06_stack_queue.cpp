// std::stack / std::queue (C++98) - container adapters: a restricted interface over deque by default
//   stack: push / pop / top       O(1)  (amortized O(1) when the underlying container is a vector)
//   queue: push / pop / front     O(1)
//   they inherit the cost and memory layout of the container they wrap
#include "bigo.h"
#include <queue>
#include <stack>
#include <vector>

int main() {
    bigo::header("std::stack / std::queue", "adapters: only the end operations are exposed, all O(1)");

    auto make_stack = [](std::size_t n) { std::stack<int> s; for (std::size_t i = 0; i < n; ++i) s.push(int(i)); return s; };
    bigo::scale("stack push + pop", "O(1)", make_stack, [](std::stack<int>& s) { s.push(1); s.pop(); return s.size(); });
    bigo::scale("stack top", "O(1)", make_stack, [](std::stack<int>& s) { return std::size_t(s.top()); });

    auto make_vstack = [](std::size_t n) { std::stack<int, std::vector<int>> s; for (std::size_t i = 0; i < n; ++i) s.push(int(i)); return s; };
    bigo::scale("stack<vector> push + pop", "O(1)", make_vstack, [](std::stack<int, std::vector<int>>& s) { s.push(1); s.pop(); return s.size(); });

    auto make_queue = [](std::size_t n) { std::queue<int> q; for (std::size_t i = 0; i < n; ++i) q.push(int(i)); return q; };
    bigo::scale("queue push + pop", "O(1)", make_queue, [](std::queue<int>& q) { q.push(1); q.pop(); return q.size(); });
    bigo::scale("queue front", "O(1)", make_queue, [](std::queue<int>& q) { return std::size_t(q.front()); });
    return 0;
}
