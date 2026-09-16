// std::deque in 10 Minutes - slide 13: thank you
// Build: make 13_while_alive
// The slide includes an imaginary "tomjnet.h"; this version defines just enough of it to run.
#include <deque>
#include <iostream>
#include <string>

struct Topic { std::string name; };

static int episodes = 0;
static bool alive() { return episodes < 3; }                 // three episodes, then the demo ends
static Topic next_cpp_topic() {
    static const char* topics[] = {"std::list", "std::map", "std::unordered_map"};
    return Topic{topics[episodes++]};
}
static Topic viewer_request() { return Topic{"request #" + std::to_string(episodes)}; }
static void subscribe() { std::cout << "  subscribed to TomJNet\n"; }

int main() {
    std::deque<Topic> backlog;
    while (alive()) {
        backlog.push_back(next_cpp_topic());   // O(1)
        backlog.push_front(viewer_request());  // O(1), no shift
        subscribe();                           // lifetime benefit
    }
    std::cout << "backlog, requests first:";
    for (const Topic& t : backlog) std::cout << ' ' << t.name << ',';
    std::cout << '\n';
    return 0;
}
