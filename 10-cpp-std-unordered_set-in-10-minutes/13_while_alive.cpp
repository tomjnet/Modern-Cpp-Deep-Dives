// std::unordered_set in 10 Minutes - slide 13: thank you
// Build: make 13_while_alive
// The slide includes an imaginary "tomjnet.h"; this version defines just enough of it to run.
#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>

struct Topic {
    std::string name;
    bool operator==(const Topic&) const = default;
};
namespace std {
template <> struct hash<Topic> {
    std::size_t operator()(const Topic& t) const noexcept { return std::hash<std::string>{}(t.name); }
};
}

static int episodes = 0;
static bool alive() { return episodes < 4; }                 // four episodes, then the demo ends
static Topic next_cpp_topic() {
    static const char* topics[] = {"std::unordered_map", "std::set", "std::unordered_map", "std::map"};
    return Topic{topics[episodes++]};
}
static void publish(const Topic& t) { std::cout << "  published " << t.name << '\n'; }
static void subscribe() { std::cout << "  subscribed to TomJNet\n"; }

int main() {
    std::unordered_set<Topic> covered;
    while (alive()) {
        Topic t = next_cpp_topic();
        if (covered.insert(t).second)     // O(1) avg: new topic?
            publish(t);
        else
            std::cout << "  " << t.name << " already covered, skipped\n";
        subscribe();                      // lifetime benefit
    }
    std::cout << "covered topics: " << covered.size() << '\n';
    return 0;
}
