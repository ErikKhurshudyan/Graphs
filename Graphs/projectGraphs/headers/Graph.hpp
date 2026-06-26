#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <initializer_list>
#include <stdexcept>
#include <queue>
#include <utility>

template <typename T>
class Graph {
public:
    using value_type      = T;
    using size_type       = std::size_t;
    using reference       = value_type&;
    using const_reference = const value_type&;

public:
    ///=====CONSTRUCTORS====
    explicit Graph(bool directed = false);
    Graph(std::initializer_list<std::pair<T, T>> init_list, bool directed = false);
    Graph(const Graph& rhv);
    Graph& operator=(const Graph& rhv);
    Graph(Graph&& rhv)            noexcept;
    Graph& operator=(Graph&& rhv) noexcept;
    ~Graph() = default;

    [[nodiscard]] bool hasNode(const_reference node)                 const;
    [[nodiscard]] bool hasEdge(const_reference u, const_reference v) const;
    [[nodiscard]] std::vector<T> getNeighbors(const_reference node)  const;
    [[nodiscard]] size_type getDegree(const_reference node)          const;

    void addNode(const_reference node);
    void addEdge(const_reference u, const_reference v);
    void removeEdge(const_reference u, const_reference v);
    void removeNode(const_reference node);

    [[nodiscard]] bool empty()          const noexcept;
    [[nodiscard]] size_type size()      const noexcept;
    [[nodiscard]] size_type edge_size() const noexcept;
    void clear()                              noexcept;

    void printPretty()                  const;
    void bfs(const_reference startNode) const;
    void dfs(const_reference startNode) const;
    
private:
    void dfsRecursive(const_reference currentNode, std::unordered_set<T>& visited) const;

private:
    std::unordered_map<T, std::unordered_set<T>> adjacencyList;
    bool isDirected;
    size_type edgeCount;
};

#include "templates/Graph.cpp"

#endif /// __GRAPH_HPP__
