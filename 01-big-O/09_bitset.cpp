// std::bitset<N> (C++98) - N bits packed into N/8 bytes, size fixed at compile time, no heap
//   test / set / reset / flip(i)   O(1)        count()             O(N/64) word-parallel popcount
//   any / none / all               O(N/64)     &, |, ^, <<, >>     O(N/64), one instruction per 64 bits
//   space: exactly ceil(N/64) words; a bool per element would be 8x bigger
#include "bigo.h"
#include <bitset>
#include <cstdio>

int main() {
    std::printf("std::bitset<N>\nfixed-size packed bits: single-bit ops O(1), whole-set ops O(N/64)\n\n");

    std::bitset<64> small;                       // 8 bytes
    std::bitset<1 << 20> big;                    // 1 Mi bits = 128 KiB
    small.set(3);
    big.set(12345).set(999'999);

    std::printf("sizeof(bitset<64>) = %zu B, sizeof(bitset<2^20>) = %zu B (%zu bools would need %zu B)\n",
                sizeof(small), sizeof(big), std::size_t(1) << 20, std::size_t(1) << 20);
    std::printf("small = %s, small.count() = %zu\n", small.to_string().c_str(), small.count());
    std::printf("big.test(12345) = %d, big.count() = %zu\n", int(big.test(12345)), big.count());

    // the whole-set operations scale with N/64, not N: 16x more bits costs ~16x more words
    std::bitset<1 << 16> b16; b16.set(7);
    std::bitset<1 << 20> b20; b20.set(7);
    const int reps = 2000;
    double t16 = bigo::ms([&] { for (int r = 0; r < reps; ++r) bigo::sink = bigo::sink + b16.count(); });
    double t20 = bigo::ms([&] { for (int r = 0; r < reps; ++r) bigo::sink = bigo::sink + b20.count(); });
    std::printf("\ncount(): 65536 bits %.3f ms, 1048576 bits %.3f ms, ratio %.1f (expected ~16 = 16x more 64-bit words)\n",
                t16, t20, t20 / (t16 > 0 ? t16 : 1e-9));
    double f16 = bigo::ms([&] { for (int r = 0; r < reps; ++r) { b16.flip(5); bigo::sink = bigo::sink + b16.test(5); } });
    double f20 = bigo::ms([&] { for (int r = 0; r < reps; ++r) { b20.flip(5); bigo::sink = bigo::sink + b20.test(5); } });
    std::printf("flip+test(i): 65536 bits %.3f ms, 1048576 bits %.3f ms, ratio %.1f (expected ~1, O(1))\n",
                f16, f20, f20 / (f16 > 0 ? f16 : 1e-9));
    return 0;
}
