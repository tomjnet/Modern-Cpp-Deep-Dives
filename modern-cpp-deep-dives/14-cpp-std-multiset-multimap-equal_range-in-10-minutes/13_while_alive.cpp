// std::multiset, std::multimap, equal_range in 10 Minutes - slide 13: thank you
// Build: make 13_while_alive
#include <iostream>
#include <iterator>
#include <map>
#include <string>

// the imaginary "tomjnet.h"
struct Topic { std::string name; };
static bool operator<(const Topic& a, const Topic& b) { return a.name < b.name; }
struct Video { int minutes; };
static int episodes = 0;
static bool alive() { return episodes < 3; }                 // three episodes, then the demo ends
static Topic next_cpp_topic() {
    static const char* topics[] = {"std::multiset", "std::multimap", "std::multiset"};
    return Topic{topics[episodes++]};
}
static Video record() { return Video{10}; }
static void subscribe() { std::cout << "  subscribed to TomJNet\n"; }

int main() {
    std::multimap<Topic, Video> channel;
    while (alive()) {
        channel.emplace(next_cpp_topic(), record());   // O(log n)
        subscribe();                 // equal_range(you): every video
    }
    auto [lo, hi] = channel.equal_range(Topic{"std::multiset"});
    std::cout << "videos about std::multiset: " << std::distance(lo, hi) << '\n';
    for (const auto& [topic, video] : channel)
        std::cout << "  " << topic.name << ": " << video.minutes << " minutes\n";
    return 0;
}
