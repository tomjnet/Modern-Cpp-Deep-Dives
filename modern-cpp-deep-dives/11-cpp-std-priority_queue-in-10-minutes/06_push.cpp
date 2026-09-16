// std::priority_queue in 10 Minutes - slide 6: push and sift up
// Build: make 06_push
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

// The adaptor keeps its vector in the protected member c. A derived class may
// read it, which is the only standard way to look at the heap layout.
struct Peek : std::priority_queue<int> {
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

// a comparator that counts how many times push had to compare
static long long compares = 0;
struct CountingLess {
    bool operator()(int a, int b) const { ++compares; return a < b; }
};

int main() {
    std::priority_queue<int> pq;   // heap: {50, 30, 40, 10, 20}
    for (int x : {50, 30, 40, 10, 20}) pq.push(x);   // no swaps in this order
    show("start          ", pq);

    pq.push(45);       // push_back on the vector, then sift up:
                       // 45 > parent 40 -> swap, 45 < 50 -> stop
                       // O(log n) swaps, growth amortized O(1)
    show("push(45)       ", pq);          // {50, 30, 45, 10, 20, 40}

    pq.emplace(60);    // constructs in place, then the same sift up
                       // two swaps: 60 becomes the new top
    show("emplace(60)    ", pq);          // {60, 30, 50, 10, 20, 40, 45}
    std::cout << "top() = " << pq.top() << '\n';

    // proof of O(log n): the worst single push into a heap of n elements
    // compares at most about log2(n) + 1 times
    std::priority_queue<int, std::vector<int>, CountingLess> big;
    const int n = 1 << 20;
    for (int i = 0; i < n; ++i) big.push(i);        // ascending: every push sifts to the top
    compares = 0;
    big.push(n);                                    // the worst case: climbs every level
    std::cout << "push into " << n << " elements: " << compares
              << " compares, log2(n) = " << std::log2(static_cast<double>(n)) << '\n';
    return 0;
}
