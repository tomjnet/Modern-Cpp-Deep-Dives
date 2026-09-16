// std::unordered_set in 10 Minutes - slide 5: create and insert
// Build: make 05_create_insert
#include <iostream>
#include <unordered_set>

static void show(const char* label, const std::unordered_set<int>& s) {
    std::cout << label << ": size " << s.size() << ", bucket_count " << s.bucket_count()
              << ", load_factor " << s.load_factor() << ", keys {";
    for (int k : s) std::cout << ' ' << k;
    std::cout << " }\n";
}

int main() {
    std::unordered_set<int> a;                  // empty: no nodes yet
    std::unordered_set<int> b{10, 20, 30, 40};  // 4 nodes, 4+ buckets
    show("a", a);
    show("b", b);

    auto [it, ok] = b.insert(20);   // O(1) avg: already there, ok = false
    std::cout << "insert(20): inserted = " << std::boolalpha << ok << ", *it = " << *it << '\n';
    b.insert(50);                   // hash(50) % bucket_count -> chain
    b.emplace(60);                  // build the node in place
    show("b after insert(50) and emplace(60)", b);

    // no b[i], no b.front(): there is no order to index into
    // b[0];        // does not compile: unordered_set has no operator[]
    // b.front();   // does not compile: no front(), no back()
    std::cout << "iteration order is bucket order, not insertion order\n";
    return 0;
}
