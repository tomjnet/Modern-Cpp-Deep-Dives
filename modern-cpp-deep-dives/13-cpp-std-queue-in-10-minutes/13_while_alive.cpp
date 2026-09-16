// std::queue in 10 Minutes - slide 13: thank you
// Build: make 13_while_alive
// The slide includes an imaginary "tomjnet.h"; this version defines just enough of it to run.
#include <iostream>
#include <queue>
#include <string>

struct Topic { std::string name; };

static int episodes = 0;
static bool alive() { return episodes < 3; }                 // three episodes, then the demo ends
static Topic next_cpp_topic() {
    static const char* topics[] = {"std::stack", "std::priority_queue", "std::set"};
    return Topic{topics[episodes++]};
}
static void record(const Topic& t) { std::cout << "  recording " << t.name << '\n'; }
static void subscribe() { std::cout << "  subscribed to TomJNet\n"; }

int main() {
    std::queue<Topic> backlog;
    while (alive()) {
        backlog.push(next_cpp_topic());      // O(1), at the back
        record(backlog.front());             // oldest first
        backlog.pop();                       // O(1), at the front
        subscribe();                         // lifetime benefit
    }
    std::cout << "backlog left: " << backlog.size() << " topics, every episode recorded in arrival order\n";
    return 0;
}
