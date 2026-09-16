// std::unordered_map in 10 Minutes - slide 5: create and access
// Build: make 05_create_access   (or: g++ -std=c++20 -Wall -O2 05_create_access.cpp -o 05_create_access)
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> a;        // empty, no nodes yet
    std::unordered_map<std::string, int> b{{"ana", 31}, {"bo", 27}};

    b["cid"] = 44;        // O(1) avg: hash, bucket, insert if missing
    int x = b["ana"];     // 31
    int y = b["zed"];     // 0: operator[] inserts a default value!
    int z = b.at("bo");   // 27, throws std::out_of_range if missing

    std::cout << "a.size() = " << a.size() << ", a.bucket_count() = " << a.bucket_count()
              << " (default constructed: no nodes, a tiny bucket array)\n";
    std::cout << "b[\"ana\"]   = " << x << "\nb[\"zed\"]   = " << y << " (zed did not exist: inserted with value 0)\n"
              << "b.at(\"bo\") = " << z << "\nb.size()   = " << b.size() << " (ana, bo, cid, zed)\n";
    std::cout << std::boolalpha << "b.contains(\"zed\") = " << b.contains("zed") << "  <- the trap: a read added a key\n";

    try {
        int bad = b.at("nobody");   // bounds checked: throws instead of inserting
        std::cout << "not reached: " << bad << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "b.at(\"nobody\") threw std::out_of_range: " << e.what() << '\n';
    }
    std::cout << "b.size()   = " << b.size() << " (at() did not insert)\n";
    return 0;
}
