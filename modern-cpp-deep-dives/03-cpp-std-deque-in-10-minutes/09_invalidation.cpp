// std::deque in 10 Minutes - slide 9: iterator invalidation rules
// Build: make 09_invalidation
//
// The slide states the rules. This program only *observes* them by comparing addresses; it never
// dereferences an invalid iterator, so it is safe to run.
#include <deque>
#include <iostream>

int main() {
    std::deque<int> d{1, 2, 3};
    int& ref = d[1];
    auto it = d.begin() + 1;
    const int* addr = &ref;

    d.push_back(4);      // it is invalid, ref is still valid
    d.push_front(0);     // same: iterators die, references live
    (void)it;            // never use it again after a push
    std::cout << "after push_back and push_front: ref = " << ref << ", address "
              << (addr == &d[2] ? "unchanged (references survive pushes at the ends)" : "changed") << '\n';

    d.pop_back();        // invalidates only the popped element
    d.pop_front();
    std::cout << "after pop_back and pop_front: ref = " << ref << " still valid, only the popped elements are gone\n";

    d.insert(d.begin() + 1, 9);  // middle: every iterator and
                                 // reference is invalid, like vector
    // ref must not be used from here on: the middle insert may have moved d[1]
    std::cout << "after insert in the middle: every iterator and reference is invalid; re-fetch: d[2] = " << d[2] << '\n';

    // the safe pattern across pushes: keep an index, not an iterator
    std::deque<int> q{10, 20, 30};
    std::size_t keep = 1;
    for (int i = 0; i < 1000; ++i) { q.push_front(-1); q.push_back(-1); ++keep; }   // front pushes shift the index
    std::cout << "kept by index across 2000 pushes: q[" << keep << "] = " << q[keep] << '\n';
    return 0;
}
