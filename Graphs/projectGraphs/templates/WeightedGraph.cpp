#include "headers/WeightedGraph.hpp"
#include <limits>

template <typename T, typename W>
WeightedGraph<T, W>::WeightedGraph(bool directed)
    : isDirected(directed)
    , edgeCount(0)
{}

template <typename T, typename W>
WeightedGraph<T, W>::WeightedGraph(std::initializer_list<Edge> init_list, bool directed) 
    : isDirected(directed)
    , edgeCount(0)
{
    for (const auto& edge : init_list) {
        addEdge(edge.u, edge.v, edge.weight);
    }
}

template <typename T, typename W>
WeightedGraph<T, W>::WeightedGraph(const WeightedGraph& rhv) 
    : adjacencyList(rhv.adjacencyList)
    , isDirected(rhv.isDirected)
    , edgeCount(rhv.edgeCount)
{}

template <typename T, typename W>
WeightedGraph<T, W>&
WeightedGraph<T, W>::operator=(const WeightedGraph& rhv)
{
    if (this != &rhv) {
        adjacencyList = rhv.adjacencyList;
        isDirected = rhv.isDirected;
        edgeCount = rhv.edgeCount;
    }
    return *this;
}

template <typename T, typename W>
WeightedGraph<T, W>::WeightedGraph(WeightedGraph&& rhv) noexcept 
    : adjacencyList(std::move(rhv.adjacencyList)), 
      isDirected(rhv.isDirected), 
      edgeCount(rhv.edgeCount)
{
    rhv.edgeCount = 0;
}

template <typename T, typename W>
WeightedGraph<T, W>&
WeightedGraph<T, W>::operator=(WeightedGraph&& rhv) noexcept
{
    if (this != &rhv) {
        adjacencyList = std::move(rhv.adjacencyList);
        isDirected = rhv.isDirected;
        edgeCount = rhv.edgeCount;
        rhv.edgeCount = 0;
    }
    return *this;
}

template <typename T, typename W>
bool
WeightedGraph<T, W>::hasNode(const_reference node) const
{
    return adjacencyList.find(node) != adjacencyList.end();
}

template <typename T, typename W>
bool
WeightedGraph<T, W>::hasEdge(const_reference u, const_reference v) const
{
    auto it = adjacencyList.find(u);
    if (it != adjacencyList.end()) {
        return it->second.find(v) != it->second.end();
    }
    return false;
}

template <typename T, typename W>
typename WeightedGraph<T, W>::weight_type
WeightedGraph<T, W>::getWeight(const_reference u, const_reference v) const
{
    auto it_u = adjacencyList.find(u);
    if (it_u != adjacencyList.end()) {
        auto it_v = it_u->second.find(v);
        if (it_v != it_u->second.end()) {
            return it_v->second;
        }
    }
    throw std::invalid_argument("This edge does not exist!");
}

template <typename T, typename W>
typename WeightedGraph<T, W>::size_type
WeightedGraph<T, W>::getDegree(const_reference node) const
{
    auto it = adjacencyList.find(node);
    if (it != adjacencyList.end()) {
        return it->second.size();
    }
    throw std::invalid_argument("This node does not exist!");
}

template <typename T, typename W>
std::vector<std::pair<T, W>>
WeightedGraph<T, W>::getNeighbors(const_reference node) const
{
    std::vector<std::pair<T, W>> neighbors;
    auto it = adjacencyList.find(node);
    if (it != adjacencyList.end()) {
        for (const auto& pair : it->second) {
            neighbors.push_back({pair.first, pair.second});
        }
    }
    return neighbors;
}

template <typename T, typename W>
void
WeightedGraph<T, W>::addNode(const_reference node)
{
    if (adjacencyList.find(node) == adjacencyList.end()) {
        adjacencyList[node] = std::unordered_map<T, W>();
    }
}

template <typename T, typename W>
void
WeightedGraph<T, W>::addEdge(const_reference u, const_reference v, const W& weight)
{
    addNode(u);
    addNode(v);

    auto& neighborsOfU = adjacencyList[u];
    if (neighborsOfU.find(v) == neighborsOfU.end()) {
        neighborsOfU[v] = weight;
        if (!isDirected) {
            adjacencyList[v][u] = weight;
        }
        edgeCount++;
    } else {
        neighborsOfU[v] = weight;
        if (!isDirected) {
            adjacencyList[v][u] = weight;
        }
    }
}

template <typename T, typename W>
void
WeightedGraph<T, W>::removeEdge(const_reference u, const_reference v)
{
    auto it_u = adjacencyList.find(u);
    if (it_u != adjacencyList.end() && it_u->second.erase(v)) {
        if (!isDirected) {
            adjacencyList[v].erase(u);
        }
        edgeCount--;
    }
}

template <typename T, typename W>
void
WeightedGraph<T, W>::removeNode(const_reference node)
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
        for (const auto& neighborPair : it->second) {
            adjacencyList[neighborPair.first].erase(node);
        }
    }

    edgeCount -= it->second.size();
    adjacencyList.erase(it);
}

template <typename T, typename W>
bool
WeightedGraph<T, W>::empty() const noexcept
{
    return adjacencyList.empty();
}

template <typename T, typename W>
typename WeightedGraph<T, W>::size_type
WeightedGraph<T, W>::size() const noexcept
{
    return adjacencyList.size();
}

template <typename T, typename W>
typename WeightedGraph<T, W>::size_type
WeightedGraph<T, W>::edge_size() const noexcept
{
    return edgeCount;
}

template <typename T, typename W>
void
WeightedGraph<T, W>::clear() noexcept
{
    adjacencyList.clear();
    edgeCount = 0;
}

template <typename T, typename W>
void
WeightedGraph<T, W>::printPretty() const
{
    std::cout << "╭────────────────────────────────────────╮\n";
    std::cout << "│      ԿՇՌՎԱԾ ԳՐԱՖԻ ԿԱՌՈՒՑՎԱԾՔԸ          │\n";
    std::cout << "├────────────────────────────────────────┤\n";
    std::cout << "│ Տեսակը՝ " << (isDirected ? "Ուղղորդված" : "Չուղղորդված") << "                     │\n";
    std::cout << "│ Գագաթներ՝ " << size() << " | Կողեր՝ " << edge_size() << "                 │\n";
    std::cout << "╰────────────────────────────────────────╯\n";

    for (const auto& pair : adjacencyList) {
        std::cout << " [" << pair.first << "] ── միացած է ──> { ";
        auto it = pair.second.begin();
        while (it != pair.second.end()) {
            std::cout << it->first << "(" << it->second << ")";
            if (++it != pair.second.end()) std::cout << ", ";
        }
        std::cout << " }\n";
    }
    std::cout << std::endl;
}

template <typename T, typename W>
std::vector<T> WeightedGraph<T, W>::dijkstra(const_reference startNode, const_reference targetNode) const
{
    std::vector<T> path;
    
    if (!hasNode(startNode) || !hasNode(targetNode)) {
        return path; 
    }

    std::unordered_map<T, W> distances;
    for (const auto& pair : adjacencyList) {
        distances[pair.first] = std::numeric_limits<W>::max();
    }
    distances[startNode] = W{};

    std::unordered_map<T, T> cameFrom;

    using P = std::pair<W, T>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    
    pq.push({distances[startNode], startNode});

    while (!pq.empty()) {
        W currentDist = pq.top().first;
        T currentNode = pq.top().second;
        pq.pop();

        /// finish
        if (currentNode == targetNode) {
            T temp = currentNode;
            while (temp != startNode) {
                path.push_back(temp);
                temp = cameFrom[temp];
            }
            path.push_back(startNode);
            std::reverse(path.begin(), path.end());
            return path;
        }

        if (currentDist > distances[currentNode]) continue;

        for (const auto& neighborPair : adjacencyList.at(currentNode)) {
            const T& neighbor = neighborPair.first;
            const W& weight = neighborPair.second;

            if (distances[currentNode] + weight < distances[neighbor]) {
                distances[neighbor] = distances[currentNode] + weight;
                cameFrom[neighbor] = currentNode;
                pq.push({distances[neighbor], neighbor});
            }
        }
    }

    return path;
}

template <typename T, typename W>
std::unordered_map<T, W> 
WeightedGraph<T, W>::bellmanFord(const_reference startNode) const
{
    std::unordered_map<T, W> distances;

    if (adjacencyList.find(startNode) == adjacencyList.end()) {
        return distances;
    }

    for (const auto& pair : adjacencyList) {
        distances[pair.first] = std::numeric_limits<W>::max();
    }
    distances[startNode] = W{};

    const size_type V = size();

    for (size_type i = 0; i < V - 1; ++i) {
        bool anyDistanceUpdated = false; 

        for (const auto& u_pair : adjacencyList) {
            T u = u_pair.first;
            
            if (distances[u] == std::numeric_limits<W>::max()) continue;

            for (const auto& v_pair : u_pair.second) {
                T v = v_pair.first;
                W weight = v_pair.second;

                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    anyDistanceUpdated = true;
                }
            }
        }

        if (!anyDistanceUpdated) break;
    }

    for (const auto& u_pair : adjacencyList) {
        T u = u_pair.first;
        if (distances[u] == std::numeric_limits<W>::max()) continue;

        for (const auto& v_pair : u_pair.second) {
            T v = v_pair.first;
            W weight = v_pair.second;

            if (distances[u] + weight < distances[v]) {
                throw std::runtime_error("Error: Negative Cycle!");
            }
        }
    }

    return distances;
}

/// f(n) = g(n) + h(n)
template <typename T, typename W>
std::vector<T>
WeightedGraph<T, W>::aStar(const_reference startNode, const_reference targetNode, 
                            std::function<W(T, T)> heuristic_func) const 
{
    std::vector<T> path;

    if (!hasNode(startNode) || !hasNode(targetNode)) return path;

    // gScore
    std::unordered_map<T, W> gScore;
    for (const auto& pair : adjacencyList) {
        gScore[pair.first] = std::numeric_limits<W>::max();
    }
    gScore[startNode] = W{};

    // fScore: gScore + heuristic
    std::unordered_map<T, W> fScore;
    fScore[startNode] = heuristic_func(startNode, targetNode);


    using P = std::pair<W, T>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> openSet;
    openSet.push({fScore[startNode], startNode});


    std::unordered_map<T, T> cameFrom;

    while (!openSet.empty()) {
        T current = openSet.top().second;
        W currentF = openSet.top().first;
        openSet.pop();

        /// finish
        if (current == targetNode) {
            T temp = current;
            while (temp != startNode) {
                path.push_back(temp);
                temp = cameFrom[temp];
            }
            path.push_back(startNode);
            std::reverse(path.begin(), path.end());
            return path;
        }

        if (currentF > fScore[current]) continue;

        for (const auto& neighborPair : adjacencyList.at(current)) {
            const T& neighbor = neighborPair.first;
            const W& weight = neighborPair.second;

            /// new gScore
            const W tentative_gScore = gScore[current] + weight;

            if (tentative_gScore < gScore[neighbor]) {
              
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentative_gScore;
                
                /// new fScore
                fScore[neighbor] = gScore[neighbor] + heuristic_func(neighbor, targetNode);
                
                openSet.push({fScore[neighbor], neighbor});
            }
        }
    }

    return path;
}
