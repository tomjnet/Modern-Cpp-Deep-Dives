// std::list in 10 Minutes - slide 7: insert and erase anywhere
// Build: make 07_insert_erase
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

static void print(const char* label, const std::list<int>& l) {
    std::cout << label << ':';
    for (int v : l) std::cout << ' ' << v;
    std::cout << '\n';
}

int main() {
    std::list<int> l{10, 20, 30, 40};
    const int* addr20 = &*std::next(l.begin(), 1);
    const int* addr40 = &l.back();

    auto it = std::next(l.begin(), 2);   // O(n): walk two links to 30
    l.insert(it, 99);                    // O(1): new node before 30
                                         // two pointers rewired, no move
    print("after insert(it, 99)", l);

    it = l.erase(it);                    // O(1): unlink 30, free the node
                                         // returns the iterator to 40
    std::cout << "erase returned the iterator to " << *it << '\n';
    l.insert(l.end(), 50);               // same as push_back: O(1)
    print("after erase(it) and insert(end, 50)", l);
    std::cout << "the neighbours never moved: 20 is " << (addr20 == &*std::next(l.begin(), 1) ? "at the same address" : "elsewhere")
              << ", 40 is " << (addr40 == &*it ? "at the same address" : "elsewhere") << '\n';

    // the measurement: 1000 inserts at a held position in the middle of 1,000,000 elements
    constexpr int n = 1'000'000;
    constexpr int inserts = 1000;
    using clock = std::chrono::steady_clock;
    auto ms = [](auto d) { return std::chrono::duration<double, std::milli>(d).count(); };

    std::list<int> big(n, 1);
    auto mid = std::next(big.begin(), n / 2);   // paid once: O(n) walk
    auto t0 = clock::now();
    for (int i = 0; i < inserts; ++i) big.insert(mid, i);   // O(1) each, the iterator stays valid
    auto t1 = clock::now();

    std::vector<int> vec(n, 1);
    auto t2 = clock::now();
    for (int i = 0; i < inserts; ++i) vec.insert(vec.begin() + n / 2, i);   // O(n) each: shifts half the vector
    auto t3 = clock::now();

    std::cout << inserts << " inserts in the middle of " << n << " elements with the position in hand: list "
              << ms(t1 - t0) << " ms, vector " << ms(t3 - t2) << " ms\n";

    // the same inserts when the position has to be found each time: the walk dominates
    auto t4 = clock::now();
    long long walked = 0;
    for (int i = 0; i < 10; ++i) {
        auto pos = std::next(big.begin(), n / 2);   // O(n) walk, cache miss per node
        big.insert(pos, i);
        walked += n / 2;
    }
    auto t5 = clock::now();
    std::cout << "10 inserts that walk to the middle first: " << ms(t5 - t4) << " ms for " << walked
              << " hops (the walk, not the insert, is the cost)\n";
    return 0;
}
