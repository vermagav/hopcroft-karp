/*
 * This is a C++ implemenation of the Hopcroft-Karp algorithm
 * http://en.wikipedia.org/wiki/Hopcroft%E2%80%93Karp_algorithm
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

// Constants used by our algorithm
namespace constants {
const int NIL       = 0;
const int MAX_SIZE  = 100000;
const int INF       = 1000000;
}

class HopcroftKarp {
 private:
    // Nodes for both sides in the bipartite graph stored in arrays of vectors
    // We don't care about the values/weights of the nodes, just that they exist
    // Thus, the data structure is as follows:
    //      Array[] Index -> Vector of connecting edge indices { a, b, c }
    //      Example: graph[1] = { 5, 6, 7 } <-- with num_nodes_left = 4
    //      means that node 1 on the left has edges to nodes (5-4), (6-4), (7-4)
    //      on the right, or node 1 on the left has edges to nodes 1, 2, 3 
    //      on the right side of the graph.
    // This logic with index node numbering also extends to matching and distance
    std::vector<int> graph[constants::MAX_SIZE];

    // Cached number of nodes on each side
    int num_nodes_left, num_nodes_right;

    // A mapping of matched nodes used during the algorithm
    int matching[constants::MAX_SIZE];

    // Distance stored during search
    int distance[constants::MAX_SIZE];

    // Private functions
    void input_data_test();
    void input_data();
    bool bfs();
    bool dfs(int);
    void output_matching(int);

 public:
    // The only public interface for running the algorithm
    void run();
};
