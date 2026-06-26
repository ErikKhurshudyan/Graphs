#include "headers/Graph.hpp"

//=====CONSTRUCTORS=====

template <typename T>
Graph<T>::Graph(const bool directed)
    : isDirected(directed)
    , edgeCount(0)
{}

template <typename T>
Graph<T>::Graph(std::initializer_list<std::pair<T, T>> init_list, const bool directed) 
    : isDirected(directed)
    , edgeCount(0)
{
    for (const auto& edge : init_list) {
        addEdge(edge.first, edge.second);
    }
}

// Copy Constructor
template <typename T>
Graph<T>::Graph(const Graph& rhv) 
    : adjacencyList(rhv.adjacencyList)
    , isDirected(rhv.isDirected)
    , edgeCount(rhv.edgeCount)
{}

// Copy Assignment Operator
template <typename T>
Graph<T>& 
Graph<T>::operator=(const Graph& rhv)
{
    if (this != &rhv) {
        adjacencyList = rhv.adjacencyList;
        isDirected = rhv.isDirected;
        edgeCount = rhv.edgeCount;
    }
    return *this;
}

// Move Constructor
template <typename T>
Graph<T>::Graph(Graph&& rhv) noexcept 
    : adjacencyList(std::move(rhv.adjacencyList))
    , isDirected(rhv.isDirected)
    , edgeCount(rhv.edgeCount)
{
    rhv.edgeCount = 0;
}

// Move Assignment Operator
template <typename T>
Graph<T>&
Graph<T>::operator=(Graph&& rhv) noexcept
{
    if (this != &rhv) {
        adjacencyList = std::move(rhv.adjacencyList);
        isDirected = rhv.isDirected;
        edgeCount = rhv.edgeCount;
        rhv.edgeCount = 0;
    }
    return *this;
}

template <typename T>
bool
Graph<T>::empty() const noexcept
{
    return adjacencyList.empty();
}

template <typename T>
typename Graph<T>::size_type
Graph<T>::size() const noexcept 
{
    return adjacencyList.size();
}

template <typename T>
typename Graph<T>::size_type 
Graph<T>::edge_size() const noexcept
{
    return edgeCount;
}

template <typename T>
void
Graph<T>::clear() noexcept
{
    adjacencyList.clear();
    edgeCount = 0;
}

// ===== GETTERS & CHECKERS =====

template <typename T>
bool
Graph<T>::hasNode(const_reference node) const
{
    return adjacencyList.find(node) != adjacencyList.end();
}

template <typename T>
bool
Graph<T>::hasEdge(const_reference u, const_reference v) const
{
    auto it = adjacencyList.find(u);
    if (it != adjacencyList.end()) {
        return it->second.find(v) != it->second.end();
    }
    return false;
}

template <typename T>
std::vector<T> 
Graph<T>::getNeighbors(const_reference node) const 
{
    std::vector<T> neighbors;
    auto it = adjacencyList.find(node);
    if (it != adjacencyList.end()) {
        neighbors.insert(neighbors.end(), it->second.begin(), it->second.end());
    }
    return neighbors;
}

template <typename T>
typename Graph<T>::size_type
Graph<T>::getDegree(const_reference node) const
{
    auto it = adjacencyList.find(node);
    if (it != adjacencyList.end()) {
        return it->second.size();
    }
    throw std::invalid_argument("Error: Node not found!");
}

// ===== CRUD OPERATIONS =====

template <typename T>
void 
Graph<T>::addNode(const_reference node)
{
    if (adjacencyList.find(node) == adjacencyList.end()) {
        adjacencyList[node] = std::unordered_set<T>();
    }
}

template <typename T>
void 
Graph<T>::addEdge(const_reference u, const_reference v)
{
    addNode(u);
    addNode(v);

    if (adjacencyList[u].find(v) == adjacencyList[u].end()) {
        adjacencyList[u].insert(v);
        if (!isDirected) {
            adjacencyList[v].insert(u);
        }
        edgeCount++;
    }
}

template <typename T>
void
Graph<T>::removeEdge(const_reference u, const_reference v)
{
    auto it_u = adjacencyList.find(u);
    if (it_u != adjacencyList.end() && it_u->second.erase(v)) {
        if (!isDirected) {
            adjacencyList[v].erase(u);
        }
        edgeCount--;
    }
}

template <typename T>
void 
Graph<T>::removeNode(const_reference node) 
{
    auto it = adjacencyList.find(node);
    if (it == adjacencyList.end()) return;

    if (isDirected) {
        for (auto& pair : adjacencyList) {
            if (pair.second.erase(node)) {
                edgeCount--;
            }
        }
    } else {
        for (const auto& neighbor : it->second) {
            adjacencyList[neighbor].erase(node);
        }
    }

    edgeCount -= it->second.size();
    
    adjacencyList.erase(it);
}

template <typename T>
void
Graph<T>::printPretty() const
{
    std::cout << "╭────────────────────────────────────────╮\n";
    std::cout << "│          ԳՐԱՖԻ ԿԱՌՈՒՑՎԱԾՔԸ             │\n";
    std::cout << "├────────────────────────────────────────┤\n";
    std::cout << "│ Տեսակը՝ " << (isDirected ? "Ուղղորդված" : "Չուղղորդված") << "                     │\n";
    std::cout << "│ Գագաթներ՝ " << size() << " | Կողեր՝ " << edge_size() << "                 │\n";
    std::cout << "╰────────────────────────────────────────╯\n";

    for (const auto& pair : adjacencyList) {
        std::cout << " [" << pair.first << "] ── միացած է ──> { ";
        auto it = pair.second.begin();
        while (it != pair.second.end()) {
            std::cout << *it;
            if (++it != pair.second.end()) std::cout << ", ";
        }
        std::cout << " }\n";
    }
    std::cout << std::endl;
}

template <typename T>
void 
Graph<T>::bfs(const_reference startNode) const
{
    if (adjacencyList.find(startNode) == adjacencyList.end()) return;

    std::unordered_set<T> visited;
    std::queue<T> q;

    visited.insert(startNode);
    q.push(startNode);

    while (!q.empty()) {
        T current = q.front();
        q.pop();
        
        std::cout << current << " ";

        for (const auto& neighbor : adjacencyList.at(current)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
    std::cout << std::endl;
}

template <typename T>
void
Graph<T>::dfs(const_reference startNode) const
{
    if (adjacencyList.find(startNode) == adjacencyList.end()) return;

    std::unordered_set<T> visited;
    dfsRecursive(startNode, visited);
    std::cout << std::endl;
}

template <typename T>
void 
Graph<T>::dfsRecursive(const_reference currentNode, std::unordered_set<T>& visited) const
{
    visited.insert(currentNode);
    std::cout << currentNode << " ";

    for (const auto& neighbor : adjacencyList.at(currentNode)) {
        if (visited.find(neighbor) == visited.end()) {
            dfsRecursive(neighbor, visited);
        }
    }
}

