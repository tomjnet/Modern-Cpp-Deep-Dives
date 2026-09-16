// std::map in 10 Minutes - slide 13: thank you
// Build: make 13_while_alive
// The slide includes an imaginary "tomjnet.h"; this version defines just enough of it to run.
#include <iostream>
#include <map>
#include <string>

struct Topic { std::string name; bool operator<(const Topic& o) const { return name < o.name; } };
struct Video { int minutes; };

static int episodes = 0;
static bool alive() { return episodes < 3; }                 // three episodes, then the demo ends
static Topic next_cpp_topic() {
    static const char* topics[] = {"std::unordered_map", "std::list", "std::string"};
    return Topic{topics[episodes++]};
}
static Topic viewer_request() {
    static const char* requests[] = {"std::deque", "std::map", "std::vector"};
    return Topic{requests[episodes - 1]};
}
static Video record() { return Video{10}; }
static void subscribe() { std::cout << "  subscribed to TomJNet\n"; }

int main() {
    std::map<Topic, Video> channel;
    while (alive()) {
        channel.emplace(next_cpp_topic(), record());  // O(log n)
        channel[viewer_request()] = record();         // sorted for free
        subscribe();                          // lifetime benefit
    }
    std::cout << "channel, sorted by topic:";
    for (const auto& [topic, video] : channel) std::cout << ' ' << topic.name << " (" << video.minutes << " min)";
    std::cout << '\n';
    return 0;
}
