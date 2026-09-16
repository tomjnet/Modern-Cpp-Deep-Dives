// std::priority_queue in 10 Minutes - slide 10: what it cannot do, and the workarounds
// Build: make 10_lazy_delete
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

static void process(int id, int p) { std::cout << "  process id " << id << " at priority " << p << '\n'; }

int main() {
    const std::size_t ids = 8;

    // no find, no erase, no decrease-key: push again, skip stale ones
    std::priority_queue<std::pair<int, int>> pq;   // {priority, id}
    std::vector<int> best(ids, -1);                // current per id

    pq.push({7, 3}); best[3] = 7;
    pq.push({9, 3}); best[3] = 9;      // id 3 upgraded, {7, 3} stale
    pq.push({8, 5}); best[5] = 8;
    pq.push({4, 1}); best[1] = 4;
    pq.push({6, 1}); best[1] = 6;      // id 1 upgraded, {4, 1} stale

    std::cout << "queue holds " << pq.size() << " entries for 3 ids\n";
    while (!pq.empty()) {
        auto [p, id] = pq.top(); pq.pop();
        if (p != best[id]) {           // stale: skipped in O(log n)
            std::cout << "  skip    id " << id << " at priority " << p << " (stale, current is "
                      << best[id] << ")\n";
            continue;
        }
        process(id, p);
    }
    pq = {};                           // no clear(): assign an empty one
    std::cout << "after pq = {}: size " << pq.size() << '\n';

    // the other operations simply do not exist; these lines do not compile
    // pq.clear();                                  // no clear()
    // auto it = std::find(pq.begin(), pq.end(), x); // no iterators
    // pq.erase(it);                                 // no erase
    return 0;
}
