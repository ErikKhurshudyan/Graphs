#ifndef __WEIGHTED_GRAPH_HPP__
#define __WEIGHTED_GRAPH_HPP__

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <queue>
#include <limits>
#include <functional>

template <typename T, typename W = int>
class WeightedGraph {
public:
    using value_type      = T;
    using weight_type     = W;
    using size_type       = std::size_t;
    using reference       = value_type&;
    using const_reference = const value_type&;

public:
    struct Edge {
        T u;
        T v;
        W weight;
    };

public:
    explicit WeightedGraph(bool directed = false);
    WeightedGraph(std::initializer_list<Edge> init_list, bool directed = false);
    
    WeightedGraph(const WeightedGraph& rhv);
    WeightedGraph& operator=(const WeightedGraph& rhv);
    
    WeightedGraph(WeightedGraph&& rhv)             noexcept;
    WeightedGraph& operator=(WeightedGraph&& rhv)  noexcept;
    ~WeightedGraph() = default;

    [[nodiscard]] bool hasNode(const_reference node)                          const;
    [[nodiscard]] bool hasEdge(const_reference u, const_reference v)          const;
    [[nodiscard]] weight_type getWeight(const_reference u, const_reference v) const;
    [[nodiscard]] size_type getDegree(const_reference node)                   const;
    
    [[nodiscard]] std::vector<std::pair<T, W>> getNeighbors(const_reference node) const;

    void addNode(const_reference node);
    void addEdge(const_reference u, const_reference v, const W& weight);
    void removeEdge(const_reference u, const_reference v);
    void removeNode(const_reference node);

    [[nodiscard]] bool empty()          const noexcept;
    [[nodiscard]] size_type size()      const noexcept;
    [[nodiscard]] size_type edge_size() const noexcept;
    void clear()                              noexcept;

    void printPretty() const;
    
    ///====ALGORITHMS====

    [[nodiscard]] std::vector<T> dijkstra(const_reference startNode, const_reference targetNode) const;///Positiv
    [[nodiscard]] std::unordered_map<T, W> bellmanFord(const_reference startNode) const; ///Negative weight
    [[nodiscard]] std::vector<T> aStar(const_reference startNode, 
                                       const_reference targetNode, 
                                       std::function<W(T, T)> heuristic_func)     const; ///A*(A-Star)

private:
    std::unordered_map<T, std::unordered_map<T, W>> adjacencyList;
    bool isDirected;
    size_type edgeCount;
};

#include "templates/WeightedGraph.cpp"

#endif /// __WEIGHTED_GRAPH_HPP__
