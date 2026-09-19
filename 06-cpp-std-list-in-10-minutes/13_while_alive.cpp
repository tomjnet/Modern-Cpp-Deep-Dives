// std::list in 10 Minutes - slide 13: thank you
// Build: make 13_while_alive
// The slide includes an imaginary "tomjnet.h"; this version defines just enough of it to run.
#include <iostream>
#include <list>
#include <string>

struct Topic { std::string name; };

static int episodes = 0;
static bool alive() { return episodes < 3; }                 // three episodes, then the demo ends
static Topic next_cpp_topic() {
    static const char* topics[] = {"std::forward_list", "std::map", "std::unordered_map"};
    return Topic{topics[episodes++]};
}
static std::list<Topic> viewer_requests() {                  // a small list of requests per episode
    return {Topic{"request #" + std::to_string(episodes) + "a"}, Topic{"request #" + std::to_string(episodes) + "b"}};
}
static void subscribe() { std::cout << "  subscribed to TomJNet\n"; }

int main() {
    std::list<Topic> backlog;
    while (alive()) {
        backlog.push_back(next_cpp_topic());    // O(1), one node
        backlog.splice(backlog.begin(), viewer_requests());  // O(1)
        subscribe();                            // lifetime benefit
    }
    std::cout << "backlog, requests first:";
    for (const Topic& t : backlog) std::cout << ' ' << t.name << ',';
    std::cout << '\n';
    return 0;
}
