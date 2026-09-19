// std::priority_queue in 10 Minutes - slide 9: build from a range
// Build: make 09_build_range
#include <chrono>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

static std::vector<int> shuffled(int n) {          // deterministic pseudo random ints
    std::vector<int> v(static_cast<std::size_t>(n));
    unsigned long long s = 12345;
    for (int& x : v) { s = s * 6364136223846793005ULL + 1442695040888963407ULL; x = static_cast<int>(s >> 33); }
    return v;
}

int main() {
    std::vector<int> v{30, 10, 50, 20, 40};

    // range constructor: copy, then std::make_heap: O(n)
    std::priority_queue<int> a(v.begin(), v.end());

    // move a filled vector in: no copy, then make_heap: O(n)
    std::priority_queue<int> b(std::less<int>{}, std::move(v));

    // n pushes: O(n log n), one sift up per element
    std::priority_queue<int> c;
    for (int x : {30, 10, 50, 20, 40}) c.push(x);   // the slow way

    std::cout << "a.top() = " << a.top() << ", b.top() = " << b.top()
              << ", c.top() = " << c.top() << '\n';                     // 50 50 50
    std::cout << "v after the move: size " << v.size() << '\n';         // 0

    // measure: make_heap over n elements against n pushes
    using clock = std::chrono::steady_clock;
    const int n = 1 << 21;
    std::vector<int> data = shuffled(n);

    auto t0 = clock::now();
    std::priority_queue<int> ranged(data.begin(), data.end());
    auto t1 = clock::now();
    std::priority_queue<int> pushed;
    for (int x : data) pushed.push(x);
    auto t2 = clock::now();

    auto ms = [](auto d) { return std::chrono::duration<double, std::milli>(d).count(); };
    std::cout << "n = " << n << ": range constructor " << ms(t1 - t0) << " ms, "
              << n << " pushes " << ms(t2 - t1) << " ms, same top "
              << (ranged.top() == pushed.top() ? "yes" : "no") << '\n';
    return 0;
}
