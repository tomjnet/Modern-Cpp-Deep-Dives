// std::stack in 10 Minutes - slide 13: thank you
// Build: make 13_while_alive
// The slide includes an imaginary "tomjnet.h"; this version defines just enough of it to run.
#include <iostream>
#include <stack>
#include <string>

struct Topic { std::string name; };

static int episodes = 0;
static bool alive() { return episodes < 3; }                 // three episodes, then the demo ends
static Topic next_cpp_topic() {
    static const char* topics[] = {"std::queue", "std::priority_queue", "std::string"};
    return Topic{topics[episodes++]};
}
static Topic viewer_request() { return Topic{"viewer request #" + std::to_string(episodes)}; }
static void subscribe() { std::cout << "  subscribed to TomJNet\n"; }

int main() {
    std::stack<Topic> todo;
    while (alive()) {
        todo.push(next_cpp_topic());     // O(1)
        todo.push(viewer_request());     // most recent first
        subscribe();                     // lifetime benefit
    }
    std::cout << "topics come out last in, first out:\n";
    while (!todo.empty()) {
        std::cout << "  " << todo.top().name << '\n';
        todo.pop();
    }
    return 0;
}
