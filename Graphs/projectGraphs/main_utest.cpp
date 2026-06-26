#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cmath>
#include "headers/Graph.hpp"
#include "headers/WeightedGraph.hpp"

TEST(GraphTest, BasicInitialization)
{
    Graph<int> g;
    EXPECT_TRUE(g.empty());
    EXPECT_EQ(g.size(), 0);
    EXPECT_EQ(g.edge_size(), 0);

    g.addNode(1);
    EXPECT_FALSE(g.empty());
    EXPECT_EQ(g.size(), 1);
    EXPECT_TRUE(g.hasNode(1));
    EXPECT_FALSE(g.hasNode(2));
}

TEST(GraphTest, UndirectedEdges)
{
    Graph<int> g(false); 
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    EXPECT_EQ(g.size(), 3);
    EXPECT_EQ(g.edge_size(), 2);

    EXPECT_TRUE(g.hasEdge(1, 2));
    EXPECT_TRUE(g.hasEdge(2, 1));

    EXPECT_EQ(g.getDegree(2), 2);
    EXPECT_EQ(g.getDegree(1), 1);
}

TEST(GraphTest, DirectedEdges)
{
    Graph<int> g(true);
    g.addEdge(1, 2);

    EXPECT_EQ(g.size(), 2);
    EXPECT_EQ(g.edge_size(), 1);

    // Քանի որ ուղղորդված է, կապը միակողմանի է
    EXPECT_TRUE(g.hasEdge(1, 2));
    EXPECT_FALSE(g.hasEdge(2, 1));
}

TEST(GraphTest, RemoveEdgeAndNode)
{
    Graph<int> g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);

    EXPECT_EQ(g.edge_size(), 3);

    g.removeEdge(1, 2);
    EXPECT_FALSE(g.hasEdge(1, 2));
    EXPECT_FALSE(g.hasEdge(2, 1));
    EXPECT_EQ(g.edge_size(), 2);

    g.removeNode(1);
    EXPECT_FALSE(g.hasNode(1));
    EXPECT_EQ(g.size(), 2);
    EXPECT_EQ(g.edge_size(), 1); 
}

TEST(GraphTest, StringTypeAndInitializerList)
{
    Graph<std::string> cities = {
        {"Yerevan", "Dilijan"},
        {"Dilijan", "Sevan"}
    };

    EXPECT_EQ(cities.size(), 3);
    EXPECT_EQ(cities.edge_size(), 2);
    EXPECT_TRUE(cities.hasNode("Yerevan"));
    EXPECT_TRUE(cities.hasEdge("Dilijan", "Yerevan"));
}

TEST(GraphTest, Exceptions)
{
    Graph<int> g;
    g.addNode(1);

    EXPECT_THROW(static_cast<void>(g.getDegree(99)), std::invalid_argument);
    
    EXPECT_NO_THROW(static_cast<void>(g.getDegree(1)));
}

TEST(GraphTest, printPretty)
{
    Graph<int> g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);    

    g.printPretty();
}

TEST(WeightedGraphTest, BasicWeights) 
{
    WeightedGraph<std::string, double> g = {
        {"A", "B", 4.5},
        {"B", "C", 2.0}
    };

    EXPECT_EQ(g.size(), 3);
    EXPECT_EQ(g.edge_size(), 2);
    EXPECT_DOUBLE_EQ(g.getWeight("A", "B"), 4.5);
    EXPECT_DOUBLE_EQ(g.getWeight("B", "A"), 4.5);
    EXPECT_DOUBLE_EQ(g.getWeight("B", "C"), 2.0);
}

TEST(WeightedGraphTest, DirectedWeights)
{
    WeightedGraph<int, int> g(true);
    g.addEdge(1, 2, 10);
    
    EXPECT_EQ(g.getWeight(1, 2), 10);
    EXPECT_THROW(static_cast<void>(g.getWeight(2, 1)), std::invalid_argument);
}

TEST(WeightedGraphTest, DijkstraShortestPath)
{
    WeightedGraph<char, int> g(true); 
    g.addEdge('A', 'B', 4);
    g.addEdge('A', 'C', 2);
    g.addEdge('C', 'B', 1);
    g.addEdge('B', 'D', 5);
    g.addEdge('C', 'D', 8);
    g.addEdge('C', 'E', 10);
    g.addEdge('D', 'E', 2);

    auto path = g.dijkstra('A', 'E');

    std::vector<char> expected_path = {'A', 'C', 'B', 'D', 'E'};
    EXPECT_EQ(path, expected_path);

    auto path_AD = g.dijkstra('A', 'D');
    std::vector<char> expected_AD = {'A', 'C', 'B', 'D'};
    EXPECT_EQ(path_AD, expected_AD);
}

TEST(WeightedGraphTest, DijkstraEdgeCases)
{
    WeightedGraph<int, int> g(false); 
    g.addEdge(1, 2, 5);
    g.addEdge(2, 3, 3);
    g.addNode(4);

    auto path_unreachable = g.dijkstra(1, 4);
    EXPECT_TRUE(path_unreachable.empty());


    auto path_same = g.dijkstra(1, 1);
    std::vector<int> expected_same = {1};
    EXPECT_EQ(path_same, expected_same);

    auto path_invalid = g.dijkstra(1, 99);
    EXPECT_TRUE(path_invalid.empty());
}

TEST(WeightedGraphTest, DijkstraWithStringTypes)
{
    WeightedGraph<std::string, double> g(false);
    g.addEdge("CityA", "CityB", 10.5);
    g.addEdge("CityB", "CityC", 5.0);
    g.addEdge("CityA", "CityC", 20.0);

    auto path = g.dijkstra("CityA", "CityC");
    
    std::vector<std::string> expected_path = {"CityA", "CityB", "CityC"};
    EXPECT_EQ(path, expected_path);
}

///A* (A-Star)
TEST(WeightedGraphTest, AStarAlgorithm) {
    WeightedGraph<std::string, int> g(false);

    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 4);
    g.addEdge("B", "C", 2);
    g.addEdge("B", "D", 5);
    g.addEdge("C", "D", 1);
    g.addEdge("D", "E", 3);

    std::unordered_map<std::string, std::pair<int, int>> coords = {
        {"A", {0, 0}},
        {"B", {1, 0}},
        {"C", {1, 2}},
        {"D", {2, 2}},
        {"E", {3, 4}}
    };
    
    auto heuristic = [&coords](const std::string& u, const std::string& v) -> int {
        auto p1 = coords[u];
        auto p2 = coords[v];
        return std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second);
    };

    auto path = g.aStar("A", "E", heuristic);

    std::vector<std::string> expected_path = {"A", "B", "C", "D", "E"};
    
    EXPECT_EQ(path, expected_path);
    EXPECT_EQ(path.size(), 5);
}

int 
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
