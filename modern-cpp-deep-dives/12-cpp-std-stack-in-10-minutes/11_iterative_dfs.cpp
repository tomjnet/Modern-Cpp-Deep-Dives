// std::stack in 10 Minutes - slide 11: replacing recursion with an explicit stack
// Build: make 11_iterative_dfs
#include <iostream>
#include <stack>
#include <vector>

static bool verbose = true;
static long long visited = 0;
static void visit(int v) {
    ++visited;
    if (verbose) std::cout << ' ' << v;
}

// adjacency list graph: O(V + E) time, O(V) stack space on the heap
void dfs(const std::vector<std::vector<int>>& g, int root) {
    std::vector<bool> seen(g.size());
    std::stack<int> todo;
    todo.push(root);
    while (!todo.empty()) {
        int v = todo.top(); todo.pop();
        if (seen[v]) continue;
        seen[v] = true;  visit(v);
        for (int w : g[v]) if (!seen[w]) todo.push(w);
    }
}

int main() {
    // small graph: 0 -> 1, 2; 1 -> 3; 2 -> 3, 4; 3 -> 5; 4 -> 5
    std::vector<std::vector<int>> g = {{1, 2}, {3}, {3, 4}, {5}, {5}, {}};
    std::cout << "dfs from 0 visits:";
    dfs(g, 0);
    std::cout << "   (" << visited << " vertices, last pushed neighbour comes out first)\n";

    // a chain one million nodes deep: a recursive dfs would need a million call frames
    // and overflow the default thread stack; the explicit std::stack lives on the heap
    const int n = 1000000;
    std::vector<std::vector<int>> chain(n);
    for (int i = 0; i + 1 < n; ++i) chain[i].push_back(i + 1);
    verbose = false;
    visited = 0;
    dfs(chain, 0);
    std::cout << "chain of " << n << " nodes: visited " << visited
              << " with an explicit stack, no stack overflow\n";
    // static void dfs_recursive(const std::vector<std::vector<int>>& g, int v) { ... dfs_recursive(g, w); }
    // is left out on purpose: at this depth it crashes with a stack overflow on most systems
    return 0;
}
