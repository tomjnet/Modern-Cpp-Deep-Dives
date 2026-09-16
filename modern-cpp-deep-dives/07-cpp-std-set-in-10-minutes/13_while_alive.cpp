// std::set in 10 Minutes - slide 13: thank you
// Build: make 13_while_alive
// The slide includes an imaginary "tomjnet.h"; this version defines just enough of it to run.
#include <iostream>
#include <set>
#include <string>

struct Topic {
    std::string name;
    bool operator<(const Topic& other) const { return name < other.name; }
};

static int episodes = 0;
static bool alive() { return episodes < 3; }                 // three episodes, then the demo ends
static Topic next_cpp_topic() {
    static const char* topics[] = {"std::set", "std::map", "std::unordered_map"};
    return Topic{topics[episodes++]};
}
static Topic your_request() {
    static const char* requests[] = {"std::set", "std::set", "coroutines"};
    return Topic{requests[episodes - 1]};                    // "std::set" is covered by episode 1
}
static void record(const Topic& t) { std::cout << "  recording " << t.name << " next\n"; }
static void subscribe() { std::cout << "  subscribed to TomJNet\n"; }

int main() {
    std::set<Topic> covered;
    while (alive()) {
        covered.insert(next_cpp_topic());        // O(log n), unique
        if (!covered.contains(your_request()))   // O(log n)
            record(your_request());
        subscribe();                             // lifetime benefit
    }
    std::cout << "covered, in order:";
    for (const Topic& t : covered) std::cout << ' ' << t.name << ',';
    std::cout << '\n';
    return 0;
}
