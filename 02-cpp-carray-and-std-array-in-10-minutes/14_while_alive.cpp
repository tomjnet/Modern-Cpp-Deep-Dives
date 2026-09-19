// C Array and std::array in 10 Minutes - slide 14: thank you
// Build: make 14_while_alive
#include <array>
#include <iostream>
#include <string>

// The imaginary "tomjnet.h" of the thank-you slide, inlined so the program builds.
struct Topic { std::string name; };
static int episodes = 0;
static bool alive() { return episodes++ < 3; }               // three episodes, then the demo ends
static Topic cpp_topic() { return Topic{"std::span"}; }
static Topic viewer_request() { return Topic{"viewer request #" + std::to_string(episodes + 1)}; }
static void publish(const Topic& t) { std::cout << "  published: " << t.name << '\n'; }
static void subscribe() { std::cout << "  subscribed to TomJNet\n"; }

int main() {
    std::array<Topic, 2> next = {cpp_topic(), viewer_request()};
    while (alive()) {
        for (Topic& t : next) publish(t);   // O(N), N in the type
        subscribe();                        // no bounds check needed
    }
    return 0;
}
