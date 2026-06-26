C++ Graph Theory Library
This project is a comprehensive, template-based C++17 library for graph theory. It is designed for high performance and memory-safe management (utilizing move semantics) and is fully covered by Google Test (GTest) unit tests.

Key Features
Flexible Architecture: Fully supports both directed and undirected graphs.

Template-Based Design: Nodes and edge weights can be of any data type (e.g., std::string, int, double).

Modern C++: Adheres to C++11/C++17 best practices, including the Rule of Five, [[nodiscard]] attributes, noexcept specifiers, std::function, and lambda expressions.

Core Traversal Algorithms: Includes Breadth-First Search (BFS) and Depth-First Search (DFS).

Advanced Pathfinding:

Dijkstra's Algorithm: Optimized shortest path search featuring Early Exit logic.

Bellman-Ford Algorithm: Robust shortest path calculation with support for negative edge weights and Negative Cycle detection.

A (A-Star) Search:* Heuristic-driven pathfinding algorithm allowing custom heuristic functions (e.g., Manhattan distance) via lambdas.

Project Structure
The project is strictly modular, separating declarations from implementations:

Plaintext
projectGraphs/
├── headers/
│   ├── Graph.hpp              # Basic Graph declarations
│   └── WeightedGraph.hpp      # Weighted Graph declarations
├── templates/
│   ├── Graph.cpp              # Basic Graph implementations
│   └── WeightedGraph.cpp      # Weighted Graph implementations
├── main_utest.cpp             # Google Test suite
└── Makefile                   # Build rules and compiler flags

Prerequisites
To build and run this project, you will need:

Compiler: GCC (g++) or Clang with C++17 support.

Operating System: Linux / Ubuntu (or Windows Subsystem for Linux - WSL).

Libraries: Google Test framework (libgtest-dev).

Build and Run
Use the provided Makefile to compile the library and execute the unit test suite with strict compiler warnings enabled (-Wall -Wextra -Werror -std=c++17). Run the following commands in your terminal:

Bash
# Clean up previous build artifacts (if any)
make clean

# Compile the project and build the test executable
make

# Run the Google Test suite
./main_utest
Usage Example (A* Algorithm)
C++
#include "headers/WeightedGraph.hpp"
#include <cmath>
#include <string>

int main() {
    // Initialize an undirected weighted graph
    WeightedGraph<std::string, int> g(false);
    
    // Build the graph
    g.addEdge("Yerevan", "Dilijan", 100);
    g.addEdge("Dilijan", "Ijevan", 35);

    // Define a custom heuristic function using a lambda
    auto heuristic = [](const std::string& u, const std::string& v) -> int {
        return 0; // Simplified for demonstration purposes
    };

    // Find the shortest path using A*
    auto path = g.aStar("Yerevan", "Ijevan", heuristic);
    
    return 0;
}
