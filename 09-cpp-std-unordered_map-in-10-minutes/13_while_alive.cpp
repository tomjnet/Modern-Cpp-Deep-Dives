// std::unordered_map in 10 Minutes - slide 13: thank you
// Build: make 13_while_alive
// The slide includes an imaginary "tomjnet.h"; this version defines just enough of it to run.
#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

struct Topic {
    std::string name;
    bool operator==(const Topic&) const = default;
};
struct Video { std::string title; };
template <> struct std::hash<Topic> {
    size_t operator()(const Topic& t) const noexcept { return std::hash<std::string>{}(t.name); }
};

static int episodes = 0;
static bool alive() { return episodes < 3; }                 // three episodes, then the demo ends
static Topic next_cpp_topic() {
    static const char* topics[] = {"std::deque", "std::map", "std::unordered_map"};
    return Topic{topics[episodes++]};
}
static Video record() { return Video{"episode " + std::to_string(episodes + 1)}; }
static Topic viewer_request() { return Topic{"std::deque"}; }   // already covered: try_emplace keeps it
static void subscribe() { std::cout << "  subscribed to TomJNet\n"; }

int main() {
    std::unordered_map<Topic, Video> channel;
    while (alive()) {
        channel[next_cpp_topic()] = record();    // O(1) avg
        channel.try_emplace(viewer_request());   // no duplicates
        subscribe();                             // lifetime benefit
    }
    std::cout << "channel has " << channel.size() << " videos (the viewer request for std::deque was already there):\n";
    for (const auto& [topic, video] : channel) std::cout << "  " << topic.name << " -> " << video.title << '\n';
    return 0;
}
