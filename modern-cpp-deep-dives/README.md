# Modern C++ Deep Dives

Runnable code from the [Modern C++ Deep Dives](https://www.youtube.com/@TomJNet) video series, in English and Spanish.
One folder per video, one complete program per topic.

| Folder | Video |
|---|---|
| `01-big-O` | C++ Data Structures: Time and Space Complexity from C++98 to C++26. One program per container; each times its operations at n and 10n and prints the measured ratio next to the expected Big-O. |
| `02-cpp-carray-and-std-array-in-10-minutes` | C Array and std::array in 10 Minutes: Big-O, Decay and Bounds. The slide snippets as full programs. |
| `03-cpp-std-vector-in-10-minutes` | std::vector in 10 Minutes: Big-O, Growth and Memory Layout. The slide snippets as full programs. |
| `04-cpp-std-deque-in-10-minutes` | std::deque in 10 Minutes: Big-O, Blocks and Memory Layout. The slide snippets as full programs. |
| `05-cpp-std-string-in-10-minutes` | std::string in 10 Minutes: Big-O, SSO and Memory Layout. The slide snippets as full programs. |
| `06-cpp-std-list-in-10-minutes` | std::list in 10 Minutes: Big-O, Nodes and Memory Layout. The slide snippets as full programs. |
| `07-cpp-std-set-in-10-minutes` | std::set in 10 Minutes: Big-O, Red-Black Trees and Ordered Lookup. The slide snippets as full programs. |
| `08-cpp-std-map-in-10-minutes` | std::map in 10 Minutes: Big-O, Red-Black Tree and Memory Layout. The slide snippets as full programs. |
| `09-cpp-std-unordered_map-in-10-minutes` | std::unordered_map in 10 Minutes: Hashing, Buckets and Big-O. The slide snippets as full programs. |
| `10-cpp-std-unordered_set-in-10-minutes` | std::unordered_set in 10 Minutes: Hashing, Buckets and Big-O. The slide snippets as full programs. |
| `11-cpp-std-priority_queue-in-10-minutes` | std::priority_queue in 10 Minutes: Big-O, Heaps and Memory Layout. The slide snippets as full programs. |
| `12-cpp-std-stack-in-10-minutes` | std::stack in 10 Minutes: Big-O, Adapters and LIFO. The slide snippets as full programs. |
| `13-cpp-std-queue-in-10-minutes` | std::queue in 10 Minutes: Adapter, Big-O and Backends. The slide snippets as full programs. |
| `14-cpp-std-multiset-multimap-equal_range-in-10-minutes` | std::multiset, std::multimap, equal_range in 10 Minutes: Big-O, Duplicates and Groups. The slide snippets as full programs. |

## Build and run

Every folder has the same Makefile. It picks the compiler by operating system: MSVC on Windows (run from a Developer Command Prompt), g++ on Linux, clang++ on macOS.

```bash
cd 01-big-O
make            # build everything
make run        # build and run every sample
make run-01_vector
make clean
```

Override the compiler or standard with `make CXX=g++` or `make STD=c++20` (default c++26). The C++23 and C++26 containers fall back to a hand-rolled equivalent when your standard library does not ship them yet.

## License

MIT
