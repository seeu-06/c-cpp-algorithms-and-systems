# N-Queens Problem: Performance Benchmark

This section compares the execution time of the standard backtracking algorithm (`naive`) versus the bitwise & bit-masking implementation (`optimized`). 

*Compiled with `g++ -O3` on WSL (Ubuntu 24.04).*

| Board Size (N) | Total Solutions | `naive` Time (ms) | `optimized` Time (ms) | Speedup (x) |
| :--- | :--- | :--- | :--- | :--- |
| 4 | 2 | 0.00636 | 0.000216 | ~29.4x |
| 6 | 4 | 0.049915 | 0.001078 | ~46.3x |
| 10 | 724 | 19.1308 | 0.176275 | ~108.5x |
| 15 | 2,279,184 | 195657 | 874.791 | ~223.7x |
| 18 | 666,090,624 | Timeout | 298680 | N/A | 

> **Note:** Execution times may vary slightly depending on background processes, but the exponential divergence in efficiency is clearly demonstrated.