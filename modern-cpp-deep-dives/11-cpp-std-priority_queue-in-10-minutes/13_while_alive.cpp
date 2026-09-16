// std::priority_queue in 10 Minutes - slide 13: thank you
// Build: make 13_while_alive
// The slide includes an imaginary "tomjnet.h"; this version defines just enough of it to run.
#include <iostream>
#include <queue>
#include <string>

struct Topic {
    std::string name;
    int votes;
    bool operator<(const Topic& o) const { return votes < o.votes; }   // top() = most voted
};

static int episodes = 0;
static bool alive() { return episodes < 3; }                 // three episodes, then the demo ends
static Topic next_cpp_topic() {
    static const Topic topics[] = {{"std::stack", 40}, {"std::span", 55}, {"std::bitset", 30}};
    return topics[episodes++];
}
static Topic viewer_request() {
    static const Topic requests[] = {{"coroutines", 90}, {"modules", 20}, {"ranges", 70}};
    return requests[episodes - 1];
}
static void record(const Topic& t) { std::cout << "  recording " << t.name << " (" << t.votes << " votes)\n"; }
static void subscribe() { std::cout << "  subscribed to TomJNet\n"; }

int main() {
    std::priority_queue<Topic> backlog;
    while (alive()) {
        backlog.push(next_cpp_topic());        // O(log n)
        backlog.push(viewer_request());        // most wanted first
        record(backlog.top()); backlog.pop();  // O(log n)
        subscribe();                           // lifetime benefit
    }
    std::cout << "still in the backlog:";
    while (!backlog.empty()) { std::cout << ' ' << backlog.top().name; backlog.pop(); }
    std::cout << '\n';
    return 0;
}
