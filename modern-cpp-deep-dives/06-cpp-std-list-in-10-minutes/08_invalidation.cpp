// std::list in 10 Minutes - slide 8: iterator invalidation rules
// Build: make 08_invalidation
//
// The slide states the rules. This program observes them by comparing addresses and only dereferences
// iterators that the rules say are still valid, so it is safe to run.
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>

static void print(const char* label, const std::list<int>& l) {
    std::cout << label << ':';
    for (int v : l) std::cout << ' ' << v;
    std::cout << '\n';
}

int main() {
    std::list<int> l{1, 2, 3};
    int& ref = l.front();
    auto it = std::next(l.begin());     // points at 2
    const int* ref_addr = &ref;
    const int* it_addr = &*it;

    l.push_back(4);       // it and ref still valid
    l.push_front(0);      // still valid: no reallocation, ever
    l.insert(it, 9);      // still valid: nodes never move
    print("after push_back, push_front and insert", l);
    std::cout << "ref = " << ref << " (address " << (ref_addr == &ref ? "unchanged" : "changed") << "), *it = " << *it
              << " (address " << (it_addr == &*it ? "unchanged" : "changed") << ")\n";

    l.erase(it);          // only it dies: the node of 2 is freed
                          // every other iterator and reference lives
    // it must not be used from here on; ref still refers to the node holding 1
    print("after erase(it)", l);
    std::cout << "ref = " << ref << ", still valid: only the erased node is gone\n";

    // sort, reverse and splice rewire links: an iterator keeps pointing at its element
    auto at9 = std::find(l.begin(), l.end(), 9);
    const int* addr9 = &*at9;
    l.sort();
    l.reverse();
    print("after sort and reverse", l);
    std::cout << "at9 still points at " << *at9 << " at the same address: "
              << (addr9 == &*at9 ? "yes" : "no") << '\n';

    std::list<int> other;
    other.splice(other.begin(), l, at9);      // the node moves to another list
    std::cout << "after splice into another list: *at9 = " << *at9 << ", same address: "
              << (addr9 == &*at9 ? "yes" : "no") << ", other.size() = " << other.size() << '\n';
    print("l", l);
    return 0;
}
