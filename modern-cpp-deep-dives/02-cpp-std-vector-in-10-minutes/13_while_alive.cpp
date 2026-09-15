// std::vector in 10 Minutes - slide 13: thank you
// Build: make 13_while_alive
// The slide includes an imaginary "tomjnet.h"; this version defines just enough of it to run.
#include <iostream>
#include <string>
#include <vector>

struct Topic { std::string name; };

static int episodes = 0;
static bool alive() { return episodes < 3; }                 // three episodes, then the demo ends
static Topic next_cpp_topic() {
    static const char* topics[] = {"std::deque", "std::map", "std::unordered_map"};
    return Topic{topics[episodes++]};
}
static void subscribe() { std::cout << "  subscribed to TomJNet\n"; }

int main() {
    std::vector<Topic> queue;
    while (alive()) {
        queue.push_back(next_cpp_topic());  // amortized O(1)
        subscribe();                    // O(1), lifetime benefit
    }
    std::cout << "queued topics:";
    for (const Topic& t : queue) std::cout << ' ' << t.name;
    std::cout << '\n';
    return 0;
}
