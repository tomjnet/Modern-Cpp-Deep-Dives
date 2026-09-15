# Modern C++ Deep Dives

Runnable code from the [Modern C++ Deep Dives](https://www.youtube.com/@TomJNet) video series, in English and Spanish.
One folder per video, one complete program per topic.

| Folder | Video |
|---|---|
| `01-big-O` | C++ Data Structures: Time and Space Complexity from C++98 to C++26. One program per container; each times its operations at n and 10n and prints the measured ratio next to the expected Big-O. |
| `02-cpp-std-vector-in-10-minutes` | std::vector in 10 Minutes: Big-O, Growth and Memory Layout. The slide snippets as full programs. |
| `03-cpp-std-deque-in-10-minutes` | std::deque in 10 Minutes: Big-O, Blocks and Memory Layout. The slide snippets as full programs. |

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
