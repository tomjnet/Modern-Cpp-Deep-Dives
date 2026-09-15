// std::hive (C++26) - bucketed storage for unordered data with stable element addresses
//   insert            amortized O(1): reuses an erased slot (free list) or appends to the current block
//   erase(iterator)   O(1): the slot becomes a skip-field hole, nothing shifts, no other element moves
//   iteration         O(n) skipping holes, contiguous inside each block (far better than a list)
//   no index access, no ordering; pointers and iterators to live elements survive every insert and erase
//
// Without <hive> the same idea is built by hand: a vector of slots with an "alive" flag and a free list.
#include "bigo.h"
#include <cstdio>
#include <vector>
#include <version>

#if defined(__cpp_lib_hive)
#include <hive>
using Hive = std::hive<int>;
static const char* impl = "std::hive (library)";
static void erase_one(Hive& h) { h.erase(h.begin()); }
#else
struct Hive {                                   // minimal stand-in: slots + free list, addresses never move
    struct Slot { int value; bool alive; };
    std::vector<Slot> slots;
    std::vector<std::size_t> free_list;
    std::size_t live = 0;
    void insert(int v) {
        if (!free_list.empty()) { slots[free_list.back()] = {v, true}; free_list.pop_back(); }
        else slots.push_back({v, true});
        ++live;
    }
    void erase_at(std::size_t i) { slots[i].alive = false; free_list.push_back(i); --live; }
    std::size_t size() const { return live; }
    template <class F> void for_each(F f) const { for (auto& s : slots) if (s.alive) f(s.value); }
};
static const char* impl = "hand-rolled slots + free list (no <hive> in this standard library)";
static void erase_one(Hive& h) { for (std::size_t i = 0; i < h.slots.size(); ++i) if (h.slots[i].alive) { h.erase_at(i); return; } }
#endif

int main() {
    bigo::header("std::hive", "stable addresses with O(1) insert and erase; iteration skips holes in contiguous blocks");
    std::printf("implementation: %s\n\n", impl);

    auto make = [](std::size_t n) { Hive h; for (std::size_t i = 0; i < n; ++i) h.insert(int(i)); return h; };

    bigo::scale("erase one + insert (hole)", "O(1)", make, [](Hive& h) { erase_one(h); h.insert(1); return h.size(); });
    bigo::scale("iteration", "O(n)", make, [](Hive& h) {
        std::size_t s = 0;
#if defined(__cpp_lib_hive)
        for (int x : h) s += std::size_t(x);
#else
        h.for_each([&](int x) { s += std::size_t(x); });
#endif
        return s;
    }, 20'000, 20);
    return 0;
}
