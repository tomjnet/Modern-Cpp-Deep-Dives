// std::stack in 10 Minutes - slide 5: create, top and inspect
// Build: make 05_create_access
#include <deque>
#include <iostream>
#include <stack>
#include <vector>

int main() {
    std::stack<int> a;                  // empty: a deque inside
    std::stack<int> b(std::deque<int>{10, 20, 30});  // top is 30
    std::stack<int, std::vector<int>> c(std::vector<int>{1, 2, 3});

    int t = b.top();            // 30, O(1); a reference: b.top() += 1
    bool e = a.empty();         // true, O(1)
    std::size_t n = b.size();   // 3, O(1)
    // top() or pop() on an empty stack is undefined behaviour
    // no b[i], no b.begin(): the top is the only door

    std::cout << std::boolalpha;
    std::cout << "b.top()   = " << t << '\n';
    b.top() += 1;                                   // top() returns a reference
    std::cout << "b.top()   = " << b.top() << " after b.top() += 1\n";
    std::cout << "a.empty() = " << e << '\n';
    std::cout << "b.size()  = " << n << '\n';
    std::cout << "c.top()   = " << c.top() << " (vector underneath: back() is the top)\n";

    // int x = b[0];          // does not compile: no operator[]
    // auto it = b.begin();   // does not compile: no iterators
    // a.top();               // compiles, but undefined behaviour on an empty stack: never run it

    // the adapter adds no fields of its own: it is exactly its container
    std::cout << "sizeof(std::stack<int>)                   = " << sizeof(std::stack<int>)
              << ", sizeof(std::deque<int>)  = " << sizeof(std::deque<int>) << '\n';
    std::cout << "sizeof(std::stack<int, std::vector<int>>) = " << sizeof(c)
              << ", sizeof(std::vector<int>) = " << sizeof(std::vector<int>) << '\n';
    return 0;
}
