// std::priority_queue in 10 Minutes - slide 8: min-heap and custom comparators
// Build: make 08_comparator
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

int main() {
    // min-heap: std::greater flips the order, top() is the smallest
    std::priority_queue<int, std::vector<int>, std::greater<int>> mn;

    // custom order: name the comparator type, pass the object
    auto by_len = [](const std::string& a, const std::string& b) {
        return a.size() < b.size();          // "less" by length
    };
    std::priority_queue<std::string, std::vector<std::string>,
                        decltype(by_len)> longest(by_len);

    std::priority_queue<std::pair<int, int>> tasks;  // {priority, id}
                                                     // lexicographic

    for (int x : {30, 10, 40, 20}) mn.push(x);
    std::cout << "min-heap top() = " << mn.top() << '\n';       // 10
    std::cout << "min-heap drain :";
    while (!mn.empty()) { std::cout << ' ' << mn.top(); mn.pop(); }  // ascending
    std::cout << '\n';

    for (const char* s : {"deque", "priority_queue", "set", "vector"}) longest.push(s);
    std::cout << "longest top()  = " << longest.top() << '\n';  // priority_queue
    std::cout << "by length      :";
    while (!longest.empty()) { std::cout << ' ' << longest.top(); longest.pop(); }
    std::cout << '\n';

    tasks.push({2, 7}); tasks.push({5, 1}); tasks.push({5, 3}); tasks.push({1, 9});
    std::cout << "tasks          :";
    while (!tasks.empty()) {                 // {5,3} before {5,1}: second field breaks ties
        std::cout << " {" << tasks.top().first << ',' << tasks.top().second << '}';
        tasks.pop();
    }
    std::cout << '\n';
    return 0;
}
