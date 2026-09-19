// std::set in 10 Minutes - slide 9: iterator invalidation and node handles
// Build: make 09_invalidation
//
// The addresses printed prove the claims: a node never moves on insert, and a node handle
// reinserts the very same memory. The invalid line from the slide stays a comment.
#include <iostream>
#include <set>
#include <utility>

static void print(const char* step, const std::set<int>& s) {
    std::cout << step << " -> {";
    for (int x : s) std::cout << ' ' << x;
    std::cout << " }\n";
}

int main() {
    std::set<int> s{10, 20, 30};
    auto it = s.find(20);
    const int& ref = *it;
    const void* before = &ref;
    std::cout << "node of 20 at " << before << '\n';

    s.insert(15);       // it and ref still valid: nodes never move
    s.insert(25);
    s.erase(10);        // only iterators to the erased key die
    print("insert 15, 25 and erase 10", s);
    std::cout << "node of 20 at " << static_cast<const void*>(&*it)
              << (&*it == before ? "  (same address: it and ref are still valid)" : "  (moved?!)") << '\n';

    // *it = 21;        // error: keys are const, the order must hold
    auto node = s.extract(it);    // unlink the node, keep the memory
    node.value() = 21;            // now the key may change
    s.insert(std::move(node));    // relink: no allocation, O(log n)
    print("extract 20, rename to 21, reinsert", s);
    std::cout << "node of 21 at " << static_cast<const void*>(&*s.find(21))
              << (&*s.find(21) == before ? "  (same memory, no allocation)" : "  (new node?!)") << '\n';

    // the same handles move a key between two sets without copying it
    std::set<int> other;
    other.insert(s.extract(25));
    print("s after moving 25 out", s);
    print("other", other);
    return 0;
}
