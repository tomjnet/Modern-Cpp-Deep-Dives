// std::queue in 10 Minutes - slide 10: breadth-first search and job queues
// Build: make 10_bfs
#include <chrono>
#include <iostream>
#include <queue>
#include <vector>

// a small undirected graph; vertex 6 is not connected to the rest
//   0 - 1 - 3
//   |   |
//   2 - 4 - 5        6
static std::vector<std::vector<int>> graph() {
    std::vector<std::vector<int>> g(7);
    auto edge = [&g](int a, int b) { g[a].push_back(b); g[b].push_back(a); };
    edge(0, 1); edge(0, 2); edge(1, 3); edge(1, 4); edge(2, 4); edge(4, 5);
    return g;
}

// the same BFS on a path graph of n vertices; returns microseconds
static long long bfs_path(int n) {
    std::vector<std::vector<int>> adj(static_cast<std::size_t>(n));
    for (int i = 0; i + 1 < n; ++i) { adj[i].push_back(i + 1); adj[i + 1].push_back(i); }
    const auto t0 = std::chrono::steady_clock::now();
    std::vector<int> dist(adj.size(), -1);
    std::queue<int> frontier;
    dist[0] = 0;
    frontier.push(0);
    while (!frontier.empty()) {
        int u = frontier.front(); frontier.pop();
        for (int v : adj[u])
            if (dist[v] < 0) { dist[v] = dist[u] + 1; frontier.push(v); }
    }
    const auto t1 = std::chrono::steady_clock::now();
    if (dist[n - 1] != n - 1) std::cout << "unexpected distance\n";
    return std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
}

int main() {
    std::vector<std::vector<int>> adj = graph();
    std::vector<int> dist(adj.size(), -1);
    std::queue<int> frontier;             // FIFO: level by level

    dist[0] = 0;
    frontier.push(0);
    while (!frontier.empty()) {
        int u = frontier.front(); frontier.pop();        // O(1)
        for (int v : adj[u])
            if (dist[v] < 0) { dist[v] = dist[u] + 1; frontier.push(v); }
    }
    // every vertex pushed and popped once: O(V + E)

    for (std::size_t v = 0; v < dist.size(); ++v) {
        std::cout << "vertex " << v << ": ";
        if (dist[v] < 0) std::cout << "unreachable\n";
        else             std::cout << "distance " << dist[v] << " from vertex 0\n";
    }

    // linear in V + E: ten times the vertices and edges, about ten times the time
    const long long t1 = bfs_path(200000);
    const long long t10 = bfs_path(2000000);
    std::cout << "BFS on a path of 200k vertices: " << t1 << " us, 2M vertices: " << t10 << " us, ratio "
              << (t1 > 0 ? static_cast<double>(t10) / static_cast<double>(t1) : 0.0)
              << " (expected about 10)\n";
    return 0;
}
