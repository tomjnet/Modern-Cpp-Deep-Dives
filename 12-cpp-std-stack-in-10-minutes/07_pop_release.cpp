// std::stack in 10 Minutes - slide 7: pop and releasing memory
// Build: make 07_pop_release
#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

// peeks at the protected container to report the vector's capacity (memory actually held)
template <class T>
struct sized_stack : std::stack<T, std::vector<T>> {
    std::size_t capacity() const { return this->c.capacity(); }
};

int main() {
    std::stack<std::string> s;
    s.push("a"); s.push("b");

    std::string top = std::move(s.top());  // read or move out first
    s.pop();                               // then remove: O(1), void
    // pop() returns nothing: a throwing copy after the removal
    // would lose the element, so the standard splits the two steps
    std::cout << "moved out \"" << top << "\", size now " << s.size()
              << ", top now \"" << s.top() << "\"\n";

    while (!s.empty()) s.pop();            // clear by hand: O(n)
    std::cout << "after the pop loop: size " << s.size() << '\n';
    s.push("x");
    std::stack<std::string>().swap(s);     // swap with an empty one:
                                           // O(1), releases the memory
    std::cout << "after the swap:     size " << s.size() << ", empty " << std::boolalpha << s.empty() << '\n';

    // the release is visible on a vector backed stack: capacity stays after pops, goes away after the swap
    sized_stack<int> v;
    for (int i = 0; i < 1000; ++i) v.push(i);
    std::cout << "vector stack: size " << v.size() << ", capacity " << v.capacity() << '\n';
    while (!v.empty()) v.pop();
    std::cout << "after popping everything: size " << v.size() << ", capacity " << v.capacity()
              << " (memory still held)\n";
    sized_stack<int>().swap(v);
    std::cout << "after swap with empty:    size " << v.size() << ", capacity " << v.capacity()
              << " (released)\n";
    // std::stack<int> e; e.pop();   // undefined behaviour on an empty stack: never run it
    return 0;
}
