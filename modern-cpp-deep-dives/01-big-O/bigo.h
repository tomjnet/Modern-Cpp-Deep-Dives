// bigo.h - shared by every sample in this folder: a stopwatch and a "does it scale like O(...)?" report.
//
// scale(name, expected, setup, op) builds a container of n elements with setup(n), times `reps` calls of
// op(container) and repeats the whole thing for 10n. The ratio between the two timings is the empirical
// growth: about 1 for O(1), about 1.3 for O(log n), about 10 for O(n), about 13 for O(n log n).
// Timings are wall-clock and noisy, so read the ratio, not the milliseconds.
#pragma once
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstring>

namespace bigo {

inline volatile std::size_t sink = 0;   // every result lands here so the optimizer cannot drop the work

template <class F>
double ms(F&& f) {
    const auto t0 = std::chrono::steady_clock::now();
    f();
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
}

inline const char* expected_ratio(const char* big_o) {
    if (!std::strcmp(big_o, "O(1)")) return "~1";
    if (!std::strcmp(big_o, "O(log n)")) return "~1.3";
    if (!std::strcmp(big_o, "O(n)")) return "~10";
    if (!std::strcmp(big_o, "O(n log n)")) return "~13";
    if (!std::strcmp(big_o, "O(sqrt n)")) return "~3.2";
    return "?";
}

inline void header(const char* container, const char* summary) {
    std::printf("%s\n%s\n(ratio = time at n=200000 / time at n=20000; a ratio well above the expected one on a scan "
                "means the bigger container no longer fits in cache)\n\n%-26s %13s %13s %8s   %s\n",
                container, summary, "operation", "n=20000", "n=200000", "ratio", "expected");
}

// setup(n) -> container; op(container&) -> std::size_t (anything, it is only accumulated into sink).
// `reps` is calibrated on the small container so the measurement lasts at least ~1 ms, then reused unchanged
// for the big one; a warm-up call absorbs first-touch costs (page faults, lazy allocations).
template <class Setup, class Op>
void scale(const char* name, const char* big_o, Setup setup, Op op, std::size_t n1 = 20'000, int reps = 200) {
    double t[2];
    std::size_t n = n1;
    const int reps_cap = reps * 100;
    for (int k = 0; k < 2; ++k, n *= 10) {
        auto c = setup(n);
        sink = sink + op(c);                                   // warm-up, not timed
        for (;;) {
            t[k] = ms([&] { for (int r = 0; r < reps; ++r) sink = sink + op(c); });
            if (k == 1 || t[k] >= 1.0 || reps >= reps_cap) break;
            reps *= 10;
        }
    }
    std::printf("%-26s %10.3f ms %10.3f ms %8.1f   %-10s ratio %s\n", name, t[0], t[1], t[1] / (t[0] > 0 ? t[0] : 1e-9),
                big_o, expected_ratio(big_o));
}

}  // namespace bigo
