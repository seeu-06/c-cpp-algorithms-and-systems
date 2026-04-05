# C/C++ Algorithms & Systems

This repository is a continuous collection of academic exercises and various algorithms for my personal learning. Its purpose is to document my progress and depth exploration of Computer Science fundamentals using C and C++.

## Repository Focus

* **Language Fundamentals:** Memory management, pointers, and core syntax of C/C++.
* **Object-Oriented Programming (OOP):** Classes, inheritance, polymorphism, and encapsulation in C++.
* **Data Structures:** Implementation of lists, stacks, queues, and their logical behavior.
* **Trees and Graphs:** Exploration, traversals, and algorithms applied to non-linear structures.
* **Backtracking:** Implementation of systematic search algorithms for solving combinatorial problems. This section explores:
    * **State-Space Tree Exploration:** Understanding how recursive calls build a tree of potential solutions.
    * **Pruning Techniques:** Enhancing efficiency by discarding non-promising paths early in the search.
    * **Resource Management:** Restoring the system state (backtrack) after exploring recursive branches to maintain data integrity.
* **Automata & Finite State Machines:** Formal models of computation for pattern recognition and sequence translation.
    * **Deterministic Finite Automata (DFA):** Implementation of mathematical models to recognize regular languages through state-based acceptance.
    * **Finite State Transducers (FST):** Implementation of models with output alphabets, such as Mealy and Moore machines, for data translation and logic control.
* **Computability Theory:** Exploration of the fundamental capabilities and limits of computation. 

## Development and Compilation Environment

All source code is written and tested under the following environment:
* **Subsystem:** WSL (Windows Subsystem for Linux)
* **Operating System:** Ubuntu 24.04.1 LTS
* **C Compiler:** gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
* **C++ Compiler:** g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0

## How to Run

This repository does not use a global build system. Each exercise and algorithm is completely standalone and is meant to be compiled and executed individually.

1. **Clone the repository and enter the directory:**
   ```bash
   git clone https://github.com/seeu-06/c-cpp-algorithms-and-systems
   cd c-cpp-algorithms-and-systems
   ```

2. **Compile a specific exercise:**
   ```bash
   # For C++ files
   g++ ./C++/path/to/file.cpp -o program
   
   # For C files
   gcc ./C/path/to/file.c -o program
   ```

3. **Execute the compiled binary:**
    ```bash
    ./program
    ```