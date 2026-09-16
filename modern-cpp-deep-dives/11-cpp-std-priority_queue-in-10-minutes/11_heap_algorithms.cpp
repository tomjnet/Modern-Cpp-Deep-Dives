// std::priority_queue in 10 Minutes - slide 11: the heap algorithms underneath
// Build: make 11_heap_algorithms
#include <algorithm>
#include <iostream>
#include <vector>

static void show(const char* label, const std::vector<int>& v) {
    std::cout << label << ": {";
    const char* sep = "";
    for (int x : v) { std::cout << sep << x; sep = ", "; }
    std::cout << "}" << (std::is_heap(v.begin(), v.end()) ? "  is_heap" : "") << '\n';
}

int main() {
    std::vector<int> v{30, 10, 50, 20, 40};
    show("start      ", v);
    std::make_heap(v.begin(), v.end());      // O(n): v[0] == 50
    show("make_heap  ", v);

    v.push_back(60);
    show("push_back  ", v);                  // not a heap until push_heap
    std::push_heap(v.begin(), v.end());      // sift up: O(log n)
    show("push_heap  ", v);

    std::pop_heap(v.begin(), v.end());       // top moves to v.back()
    show("pop_heap   ", v);                  // 60 at the back, the rest is a heap
    int top = v.back(); v.pop_back();        // 60, O(log n)
    std::cout << "top = " << top << '\n';

    std::sort_heap(v.begin(), v.end());      // heapsort: O(n log n)
    show("sort_heap  ", v);                  // ascending, no longer a heap
    // priority_queue is these four calls wrapped around a vector
    return 0;
}
