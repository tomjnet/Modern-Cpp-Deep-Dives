// std::stack in 10 Minutes - slide 9: no iterators, looking inside
// Build: make 09_inspect
#include <deque>
#include <iostream>
#include <stack>

void print(std::stack<int> s) {          // by value: a copy, O(n)
    while (!s.empty()) { std::cout << s.top() << ' '; s.pop(); }
}

template <class T, class C>
struct peek_stack : std::stack<T, C> {   // c is protected, not private
    const C& container() const { return this->c; }
};

int main() {
    std::stack<int> x, y;
    bool same = (x == y);    // compares the containers: O(n)
    std::cout << std::boolalpha << "two empty stacks equal: " << same << '\n';

    for (int v : {1, 2, 3, 4}) x.push(v);
    std::cout << "print(x) pops a copy, top first: ";
    print(x);
    std::cout << "  (x still has " << x.size() << " elements)\n";
    // for (int v : x) {}          // does not compile: no begin() or end()
    // std::find(x.begin(), ...)   // same reason: no iterators, use the container directly

    peek_stack<int, std::deque<int>> p;
    for (int v : {10, 20, 30}) p.push(v);
    std::cout << "peek_stack container, bottom first: ";
    for (int v : p.container()) std::cout << v << ' ';
    std::cout << '\n';

    y = x;                                   // copy: O(n)
    std::cout << "x == y after copy: " << (x == y) << '\n';
    y.push(5);
    std::cout << "x == y after y.push(5): " << (x == y) << ", x < y: " << (x < y)
              << " (lexicographic on the containers, O(n))\n";
    return 0;
}
