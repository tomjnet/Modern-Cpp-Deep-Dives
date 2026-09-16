// std::priority_queue in 10 Minutes - slide 5: create and top
// Build: make 05_create_top
#include <iostream>
#include <queue>

int main() {
    std::priority_queue<int> pq;      // max-heap over std::vector<int>
    pq.push(30); pq.push(10); pq.push(40);

    int t = pq.top();       // 40: O(1), v[0], const reference only
    bool e = pq.empty();    // O(1)
    size_t n = pq.size();   // O(1)

    // no pq[i], no pq.at(i), no begin() / end(): only top is ordered
    // pq.pop() returns void: read top(), then pop()

    std::cout << "top()   = " << t << '\n';                       // 40
    std::cout << "empty() = " << (e ? "true" : "false") << '\n';  // false
    std::cout << "size()  = " << n << '\n';                       // 3

    // the adaptor hides the vector: these lines do not compile
    // int x = pq[0];                  // no operator[]
    // for (int v : pq) use(v);        // no begin() / end()
    // int y = pq.pop();               // pop() returns void
    // pq.top() = 99;                  // top() is a const reference

    // the only way to see the elements in order: read top, then pop
    std::cout << "drain  :";
    while (!pq.empty()) {
        std::cout << ' ' << pq.top();  // 40 10 30 pushed, comes out 40 30 10
        pq.pop();
    }
    std::cout << '\n';
    std::cout << "sizeof(std::priority_queue<int>) = " << sizeof(pq)
              << " bytes (the vector plus the comparator)\n";
    return 0;
}
