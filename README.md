# Parallel Merge Sort using Pthreads

This project implements and benchmarks a parallel version of the Merge Sort algorithm using Pthreads in C++. It compares the performance of sequential vs multithreaded implementations and includes graphs, timing data, and a final report.

 Folder Structure

- `src/` — C++ source files for both sequential and parallel implementations.
- `docs/` — Final project report and performance graphs.
- `results/` — Timing data collected from all experiments.

 Algorithm Overview

Merge Sort is a divide-and-conquer algorithm that recursively splits arrays and merges them in sorted order. This project parallelizes the sorting of left and right halves using `pthread_create` and synchronizes them with `pthread_join`.

System Specifications

- **CPU**: Intel Core i3-8130U (2 cores / 4 threads)
- **RAM**: 8 GB
- **OS**: Windows 10 + WSL
- **Compiler**: g++ with `-pthread` flag

Input Sizes Tested

- 1,000
- 10,000
- 100,000
- 1,000,000

Each was tested with:
- 1 thread
- 2 threads
- 4 threads

Performance Graphs

Graphs showing execution time and speedup for different thread counts can be found in `docs/graphs/`.

Report

See `docs/Project1 Report.pdf` for full documentation, analysis, and conclusions.

AI Assistance Disclaimer

Some assistance was provided by OpenAI’s ChatGPT for parallel code, graph generation, and documentation editing. All final code and analysis were verified tested  ran and understood and run anby the author.

## 👤 Author

Mahmoud Qasrawi
