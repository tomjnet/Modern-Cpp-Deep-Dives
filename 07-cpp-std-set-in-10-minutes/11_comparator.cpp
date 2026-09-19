// std::set in 10 Minutes - slide 11: comparators and heterogeneous lookup
// Build: make 11_comparator
#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <string_view>

struct Task { int prio; std::string name; };
struct ByPrio {
    bool operator()(const Task& x, const Task& y) const {
        return x.prio < y.prio;  // strict weak ordering only
    }
};

int main() {
    std::set<Task, ByPrio> tasks;    // same prio: same key, dropped
    std::set<int, std::greater<>> desc{1, 2, 3};   // {3, 2, 1}

    std::set<std::string, std::less<>> names;      // transparent
    names.find("bob");   // no std::string temporary: C++14

    tasks.insert({2, "deploy"});
    tasks.insert({1, "build"});
    tasks.insert({2, "notify"});     // equivalent to {2, "deploy"} under ByPrio: dropped
    std::cout << "tasks by prio:";
    for (const Task& t : tasks) std::cout << "  " << t.prio << ':' << t.name;
    std::cout << "\n  (2:notify was dropped: equal prio means the same key)\n";

    std::cout << "desc:";
    for (int x : desc) std::cout << ' ' << x;
    std::cout << '\n';

    names.insert("alice");
    names.insert("bob");
    std::string_view sv = "bob";
    std::cout << std::boolalpha;
    std::cout << "names.find(\"bob\") found: " << (names.find("bob") != names.end()) << '\n';
    std::cout << "names.contains(string_view): " << names.contains(sv) << "  (no temporary std::string built)\n";
    std::cout << "names.count(\"carol\"): " << names.count("carol") << '\n';
    return 0;
}
