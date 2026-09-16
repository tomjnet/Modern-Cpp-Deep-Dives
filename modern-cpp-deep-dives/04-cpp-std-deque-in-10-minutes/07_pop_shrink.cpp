// std::deque in 10 Minutes - slide 7: pop and releasing memory
// Build: make 07_pop_shrink
#include <deque>
#include <iostream>

int main() {
    std::deque<int> d;
    for (int i = 0; i < 100000; ++i) d.push_back(i);
    std::cout << "filled: size " << d.size() << ", front " << d.front() << ", back " << d.back() << '\n';

    d.pop_front();       // O(1); an emptied end block is freed
    d.pop_back();        // O(1)
    std::cout << "after pop_front + pop_back: size " << d.size() << ", front " << d.front() << ", back " << d.back() << '\n';

    // popping from the front a block at a time: constant per element, no shifting of the rest
    for (int i = 0; i < 50000; ++i) d.pop_front();
    std::cout << "after 50000 pop_front: size " << d.size() << ", front " << d.front() << '\n';

    d.clear();           // size 0, blocks may stay allocated
    std::cout << "after clear(): size " << d.size() << ", empty " << std::boolalpha << d.empty() << '\n';
    d.shrink_to_fit();   // ask to release spare blocks and map
    std::cout << "after shrink_to_fit(): size " << d.size() << " (spare blocks and map slots may be released)\n";

    // no reserve(), no capacity(): growth is per block
    std::cout << "deque has no reserve() or capacity(): growth happens one block at a time\n";
    return 0;
}
