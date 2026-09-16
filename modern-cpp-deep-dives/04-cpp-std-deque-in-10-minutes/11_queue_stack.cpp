// std::deque in 10 Minutes - slide 11: deque behind queue, stack and sliding windows
// Build: make 11_queue_stack
#include <deque>
#include <iostream>
#include <queue>
#include <stack>

int main() {
    std::queue<int> q;      // queue<int, deque<int>> by default
    q.push(1); q.push(2);   // push_back
    q.pop();                // pop_front: O(1), vector cannot
    std::cout << "queue after push 1, push 2, pop: front " << q.front() << ", size " << q.size() << '\n';

    std::stack<int> s;      // also a deque underneath
    s.push(7); s.pop();
    std::cout << "stack after push 7, pop: size " << s.size() << '\n';

    // sliding window: the average of the last k samples, O(1) per new sample
    const std::size_t k = 3;
    const int samples[] = {5, 8, 6, 9, 4, 7};
    std::deque<int> window;                      // last k samples
    int sum = 0;
    std::cout << "sliding window (k = " << k << "):\n";
    for (int x : samples) {
        window.push_back(x);                         // newest in
        sum += x;
        if (window.size() > k) { sum -= window.front(); window.pop_front(); }   // oldest out: O(1)
        std::cout << "  sample " << x << " -> window [";
        for (int w : window) std::cout << ' ' << w;
        std::cout << " ] average " << double(sum) / double(window.size()) << '\n';
    }
    return 0;
}
