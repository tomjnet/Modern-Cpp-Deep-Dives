// std::queue in 10 Minutes - slide 11: a thread-safe producer consumer channel
// Build: make 11_thread_safe
// The slide's class template cannot live inside main() (local classes cannot be templates), so it sits here.
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>

template <class T> class channel {   // producer / consumer
    std::queue<T> q_; std::mutex m_; std::condition_variable cv_;
public:
    void send(T v) {                 // O(1) under the lock
        { std::lock_guard lk(m_); q_.push(std::move(v)); }
        cv_.notify_one();
    }
    T receive() {                    // blocks while empty
        std::unique_lock lk(m_);
        cv_.wait(lk, [&] { return !q_.empty(); });
        T v = std::move(q_.front()); q_.pop(); return v; }
};

int main() {
    const int n = 100000;
    channel<int> ch;

    // the producer sends 1..n, then a 0 as the end marker
    std::thread producer([&ch, n] {
        for (int i = 1; i <= n; ++i) ch.send(i);
        ch.send(0);
    });

    // the consumer receives until the marker; FIFO means the values arrive in order
    long long sum = 0;
    int count = 0;
    int last = 0;
    bool in_order = true;
    for (;;) {
        int v = ch.receive();
        if (v == 0) break;
        if (v != last + 1) in_order = false;
        last = v;
        sum += v;
        ++count;
    }
    producer.join();

    std::cout << "received " << count << " messages, sum " << sum
              << " (expected " << static_cast<long long>(n) * (n + 1) / 2 << ")\n";
    std::cout << "arrival order preserved: " << std::boolalpha << in_order << '\n';
    return 0;
}
