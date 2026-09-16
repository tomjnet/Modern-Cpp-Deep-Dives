// std::queue in 10 Minutes - slide 7: pop and the FIFO discipline
// Build: make 07_pop_fifo
#include <chrono>
#include <iostream>
#include <queue>

static void use(int x) { std::cout << ' ' << x; }

// push n elements then pop them all; returns microseconds for the whole round trip
static long long round_trip(int n) {
    std::queue<int> q;
    const auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < n; ++i) q.push(i);
    long long sum = 0;
    while (!q.empty()) { sum += q.front(); q.pop(); }
    const auto t1 = std::chrono::steady_clock::now();
    if (sum != static_cast<long long>(n) * (n - 1) / 2) std::cout << "unexpected sum\n";
    return std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
}

int main() {
    std::queue<int> q;
    for (int x : {10, 20, 30, 40}) q.push(x);

    int f = q.front();   // 10: the oldest element, read it first
    q.pop();             // c.pop_front(): O(1), returns void

    std::cout << "front() before pop: " << f << ", after pop: " << q.front()
              << ", size " << q.size() << '\n';

    std::cout << "drain in arrival order:";
    while (!q.empty()) { // drain in arrival order: O(n) total
        use(q.front());
        q.pop();
    }
    std::cout << "\nafter the drain: size " << q.size() << ", empty " << std::boolalpha << q.empty() << '\n';

    // push n then pop n is linear: ten times the elements, about ten times the time
    const long long t1 = round_trip(1000000);
    const long long t10 = round_trip(10000000);
    std::cout << "1M push+pop: " << t1 << " us, 10M push+pop: " << t10 << " us, ratio "
              << (t1 > 0 ? static_cast<double>(t10) / static_cast<double>(t1) : 0.0)
              << " (expected about 10)\n";
    return 0;
}
