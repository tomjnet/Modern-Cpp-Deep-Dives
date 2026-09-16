// std::stack in 10 Minutes - slide 10: matching brackets, the classic job
// Build: make 10_brackets
#include <iostream>
#include <stack>
#include <string>
#include <string_view>

bool balanced(std::string_view text) {  // O(n) time, O(depth) space
    std::stack<char> open;
    for (char ch : text) {
        if (ch == '(' || ch == '[') { open.push(ch); continue; }
        if (ch != ')' && ch != ']') continue;
        char want = (ch == ')') ? '(' : '[';
        if (open.empty() || open.top() != want) return false;
        open.pop();
    }
    return open.empty();                // unclosed opener?
}

// same walk, but reports the deepest nesting: that is the stack's peak size
static std::size_t max_depth(std::string_view text) {
    std::stack<char> open;
    std::size_t deepest = 0;
    for (char ch : text) {
        if (ch == '(' || ch == '[') { open.push(ch); if (open.size() > deepest) deepest = open.size(); }
        else if ((ch == ')' || ch == ']') && !open.empty()) open.pop();
    }
    return deepest;
}

int main() {
    const char* cases[] = {
        "(a + b) * [c - d]",
        "([)]",
        "((a)",
        "a + b)",
        "",
        "[[[[[[[[[[x]]]]]]]]]]",
    };
    std::cout << std::boolalpha;
    for (const char* text : cases) {
        std::cout << "balanced(\"" << text << "\") = " << balanced(text)
                  << "   length " << std::string_view(text).size()
                  << ", deepest nesting " << max_depth(text) << '\n';
    }
    // a long flat string costs O(n) time but only O(1) stack space: depth never exceeds 1
    std::string flat;
    for (int i = 0; i < 100000; ++i) flat += "()";
    std::cout << "100000 flat pairs: balanced " << balanced(flat) << ", deepest nesting " << max_depth(flat) << '\n';
    return 0;
}
