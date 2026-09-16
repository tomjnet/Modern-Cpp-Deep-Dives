// std::list in 10 Minutes - slide 6: push_front, push_back and growth
// Build: make 06_push_ends
#include <chrono>
#include <iostream>
#include <list>
#include <vector>

static void print(const char* label, const std::list<int>& l) {
    std::cout << label << ':';
    for (int v : l) std::cout << ' ' << v;
    std::cout << '\n';
}

int main() {
    std::list<int> l{10, 20, 30};

    l.push_back(40);     // O(1): new node, linked after 30
    l.push_front(5);     // O(1): new node, linked before 10
    l.emplace_back(50);  // O(1): value built inside the node
    print("after push_back, push_front, emplace_back", l);

    int& first = l.front();
    auto it = l.begin();
    const int* addr = &first;
    l.push_back(60);     // first and it still valid: nothing moved
    std::cout << "after push_back(60): first = " << first << ", *it = " << *it << ", address of front "
              << (addr == &l.front() ? "unchanged" : "changed") << '\n';
    l.pop_front();       // O(1): unlink 5, free its node
    // first and it referred to the popped node: never used again from here on
    print("after pop_front", l);

    // a reference taken now survives any number of pushes at both ends
    int& keep = l.back();                 // 60
    const int* keep_addr = &keep;
    for (int i = 0; i < 100000; ++i) { l.push_back(i); l.push_front(-i); }
    std::cout << "after 200000 more pushes: keep = " << keep << ", address "
              << (keep_addr == &keep ? "unchanged (no reallocation, ever)" : "changed") << '\n';

    // the constant factor: one heap allocation per push versus amortized growth in a vector
    constexpr int n = 1'000'000;
    using clock = std::chrono::steady_clock;
    auto t0 = clock::now();
    std::list<int> big;
    for (int i = 0; i < n; ++i) big.push_back(i);
    auto t1 = clock::now();
    std::vector<int> vec;
    for (int i = 0; i < n; ++i) vec.push_back(i);
    auto t2 = clock::now();
    long long sum = 0;
    for (int v : big) sum += v;
    for (int v : vec) sum -= v;
    auto ms = [](auto d) { return std::chrono::duration<double, std::milli>(d).count(); };
    std::cout << n << " push_back: list " << ms(t1 - t0) << " ms, vector " << ms(t2 - t1)
              << " ms (one malloc per node vs a few reallocations); checksum " << sum << '\n';
    return 0;
}
