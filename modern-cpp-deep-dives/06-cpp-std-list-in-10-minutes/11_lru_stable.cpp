// std::list in 10 Minutes - slide 11: LRU cache, stable handles plus O(1) moves
// Build: make 11_lru_stable
// The slide shows touch() and evict(); this version adds put() and get() around them to run a small cache.
#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>

using Node = std::pair<int, int>;               // key, value
std::list<Node> order;                          // most recent first
std::unordered_map<int, std::list<Node>::iterator> where;

void touch(int key) {                           // O(1) average
    auto it = where.find(key);
    if (it == where.end()) return;
    order.splice(order.begin(), order, it->second);  // O(1) relink
}
void evict() {                                  // O(1)
    where.erase(order.back().first);
    order.pop_back();                           // others stay valid
}

static constexpr std::size_t capacity = 3;

static void put(int key, int value) {           // O(1) average
    if (where.count(key)) { where[key]->second = value; touch(key); return; }
    if (order.size() == capacity) evict();
    order.emplace_front(key, value);            // one node, no other node moves
    where[key] = order.begin();
}

static const int* get(int key) {                // O(1) average, nullptr on a miss
    auto it = where.find(key);
    if (it == where.end()) return nullptr;
    touch(key);
    return &it->second->second;
}

static void print(const char* label) {
    std::cout << label << " (most recent first):";
    for (const Node& n : order) std::cout << " {" << n.first << ": " << n.second << '}';
    std::cout << '\n';
}

int main() {
    put(1, 100); put(2, 200); put(3, 300);
    print("after put 1, 2, 3");
    const int* v1 = get(1);
    std::cout << "get(1) = " << (v1 ? *v1 : -1) << ", 1 moved to the front by splice\n";
    print("after get(1)");
    put(4, 400);
    print("after put 4 (evicts 2, the least recently used)");
    std::cout << "get(2) = " << (get(2) ? "hit" : "miss") << '\n';

    // the map's iterators stay valid across every splice, insert and pop: check each one
    bool all_valid = true;
    for (const auto& [key, it] : where) all_valid = all_valid && (it->first == key);
    std::cout << "every iterator stored in the map still points at its own node: " << (all_valid ? "yes" : "no") << '\n';

    // the value returned by get(1) lives in a node that never moved
    put(5, 500);   // evicts 3
    put(6, 600);   // evicts 4
    std::cout << "after two more evictions, the pointer from get(1) still reads " << *v1 << '\n';
    print("final");
    return 0;
}
