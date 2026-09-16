// std::string in 10 Minutes - slide 13: thank you
// Build: make 13_while_alive
// The slide includes an imaginary "tomjnet.h"; this version defines just enough of it to run.
#include <iostream>
#include <string>

static int episodes = 0;
static bool alive() { return episodes < 3; }                 // three episodes, then the demo ends
static std::string next_cpp_topic() {
    static const char* topics[] = {" std::string_view", " subscribe", " std::format"};
    return topics[episodes++];
}
static void subscribe() { std::cout << "  subscribed to TomJNet\n"; }

int main() {
    std::string channel = "TomJNet";
    while (alive()) {
        channel += next_cpp_topic();          // amortized O(1) per char
        if (channel.find("subscribe") != std::string::npos)
            subscribe();                      // lifetime benefit
    }
    std::cout << "channel: \"" << channel << "\" size " << channel.size() << ", capacity " << channel.capacity() << '\n';
    return 0;
}
