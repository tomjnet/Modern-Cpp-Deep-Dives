// std::vector in 10 Minutes - slide 9: iterator invalidation rules
// Build: make 09_invalidation
//
// The slide shows the bugs. This program shows the same operations but only *observes* the
// invalidation (by comparing addresses) instead of dereferencing a dangling pointer, so it is
// safe to run. The undefined-behaviour loop from the slide is kept as a comment.
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3};
    int* first = &v[0];
    auto it = v.begin();
    std::cout << "block before push_back: " << static_cast<const void*>(first) << '\n';

    v.push_back(4);      // may reallocate: first and it now dangle
    std::cout << "block after  push_back: " << static_cast<const void*>(v.data())
              << (v.data() == first ? "  (same block, lucky this time)" : "  (moved: first and it are dangling)") << '\n';
    (void)it;            // never dereference it after a possible reallocation

    first = v.data();
    v.reserve(100);      // reallocates: same problem
    std::cout << "block after  reserve  : " << static_cast<const void*>(v.data())
              << (v.data() == first ? "  (same block)" : "  (moved: every pointer is invalid)") << '\n';

    v.erase(v.begin());  // iterators from that point onward invalid

    // for (int x : v)      // never push_back inside a range-for on v
    //     v.push_back(x);  // undefined behaviour

    // the safe versions: iterate by index (the size is read every time), or reserve first
    const std::size_t n = v.size();
    for (std::size_t i = 0; i < n; ++i)
        v.push_back(v[i]);           // v[i] is re-evaluated after any reallocation

    std::cout << "doubled by index: ";
    for (int x : v) std::cout << x << ' ';
    std::cout << "\n";
    return 0;
}
