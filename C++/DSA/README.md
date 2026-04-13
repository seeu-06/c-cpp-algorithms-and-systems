# DSA: Data Structures and Algorithms

This directory serves as a modular data structures library and a collection of practical applications focused on the rigorous design, internal management, and optimization of abstract data types. The architecture is explicitly designed to separate core abstract logic from problem-specific implementations.

> [!NOTE]
> All core implementations in this section prioritize memory efficiency and type safety using templates and low-level memory management.

## Directory Structure

### 📂 `core-structures/`
This folder contains the **Header-Only** library of fundamental data structures. Each structure is implemented as a C++ `template`, allowing it to generically handle any data type while maintaining strict performance standards.
* **Architecture:** These files (`.hpp`) include both declarations and internal logic, featuring `header guards` to prevent redefinition errors during complex compilations.
* **Content:** Stack, Queue, Linked List, Graph and Tree, built entirely from scratch without relying on the C++ Standard Template Library (STL).

### 📂 `applications/`
This folder contains standalone exercises and systems that actively "consume" the core structures.
* **Usage:** Instead of rewriting base data structures, each application imports them natively (e.g., `#include "../../core-structures/<data-structure>.hpp"`).

### 📂 `other-challenges/`
This folder houses specialized algorithmic challenges and ad-hoc solutions.
* **Focus:** Academic exercises and complex mathematical problems (such as a modified Dijkstra algorithm for specific graph conditions) that require highly tailored, monolithic logic.
* **Usage:** Unlike the `applications/` directory, scripts here utilize the C++ Standard Template Library (STL) for immediate problem-solving. This approach keeps the custom `core-structures` library pure, strictly separating generic data structures from monolithic, single-file competitive programming scripts.
