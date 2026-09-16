// C Array and std::array in 10 Minutes - slide 7: decay: the c array's trap
// Build: make 07_decay
#include <array>
#include <cstddef>
#include <iostream>

// The three functions the slide declares. f receives a pointer whatever the caller wrote:
// "int p[4]" in a parameter list means "int* p", so it is spelled that way here to keep
// sizeof(p) honest (the compiler warns when you take sizeof of an array-style parameter).
void f(int* p) {
    std::cout << "  f: sizeof(p) = " << sizeof(p) << " B (a pointer), p[0] = " << p[0]
              << ", N is gone\n";
}

void g(const std::array<int, 4>& a) {
    std::cout << "  g: sizeof(a) = " << sizeof(a) << " B, a.size() = " << a.size()
              << ", the size is in the type\n";
}

void h(int (&r)[4]) {
    std::cout << "  h: sizeof(r) = " << sizeof(r) << " B, " << sizeof(r) / sizeof(r[0])
              << " elements, the size is in the type\n";
}

int main() {
    void f(int p[4]);                    // really: void f(int* p)
    void g(const std::array<int, 4>& a); // the size is part of the type
    void h(int (&r)[4]);                 // reference to array: size kept
    int c[4] = {1, 2, 3, 4};
    std::cout << "sizeof(c) = " << sizeof(c) << '\n';  // 16: the whole array
    f(c);                                // decays: sizeof(p) is 8, N lost
    h(c);                                // no decay: only 4 ints fit
    std::array<int, 4> a = {1, 2, 3, 4};
    g(a);                                // a value type: never decays

    // int five[5] = {};
    // h(five);                          // error: int (&)[4] does not bind to int[5]
    // g(std::array<int, 5>{});          // error: a different type
    // f(five);                          // compiles: the pointer forgot the size, that is the trap
    std::cout << "a C array decays to a pointer when passed by value; a reference to array and\n"
                 "std::array keep N in the type, so a wrong size is a compile error, not a bug\n";
    return 0;
}
