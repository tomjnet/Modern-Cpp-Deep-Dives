// std::priority_queue in 10 Minutes - slide 7: pop and sift down
// Build: make 07_pop
#include <iostream>
#include <queue>
#include <vector>

// The adaptor keeps its vector in the protected member c. A derived class may
// read it, which is the only standard way to look at the heap layout.
struct Peek : std::priority_queue<int> {
    Peek() = default;
    explicit Peek(const std::priority_queue<int>& q) : std::priority_queue<int>(q) {}
    const std::vector<int>& raw() const { return c; }
};

static void show(const char* label, const std::priority_queue<int>& q) {
    Peek copy(q);                          // a named copy: its vector outlives the loop
    std::cout << label << ": {";
    const char* sep = "";
    for (int x : copy.raw()) { std::cout << sep << x; sep = ", "; }
    std::cout << "}\n";
}

static void use(int x) { std::cout << ' ' << x; }

int main() {
    std::priority_queue<int> pq;   // heap: {60, 50, 40, 10, 20, 30}
    for (int x : {60, 50, 40, 10, 20, 30}) pq.push(x);   // no swaps in this order
    show("start   ", pq);

    int biggest = pq.top();  // 60, read first: pop() returns void
    pq.pop();                // last (30) moves to the root, pop_back,
                             // then sift down: pick the larger child
                             // 50 > 30 -> swap; 20 < 30 -> stop
                             // O(log n), no allocation, no free
    std::cout << "biggest = " << biggest << '\n';
    show("pop()   ", pq);                 // {50, 30, 40, 10, 20}

    std::cout << "drain   :";
    while (!pq.empty()) { use(pq.top()); pq.pop(); }  // descending
    std::cout << '\n';

    // pop never frees the buffer: the vector only shrinks by one
    Peek keep;                             // a real queue whose vector we can watch
    for (int i = 0; i < 1000; ++i) keep.push(i);
    const int* before = keep.raw().data();
    std::size_t cap_before = keep.raw().capacity();
    for (int i = 0; i < 999; ++i) keep.pop();
    std::cout << "after 999 pops: size " << keep.size()
              << ", capacity " << keep.raw().capacity()
              << " (was " << cap_before << "), buffer "
              << (keep.raw().data() == before ? "unchanged" : "moved") << '\n';
    return 0;
}
