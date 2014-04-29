#include "algorithm.h"

void HopcroftKarp::input_data_test() {
    num_nodes_left = 5;
    num_nodes_right = 4;
 
    graph[5].push_back(2);
    graph[7].push_back(5);
    
    graph[1].push_back(2);
    graph[7].push_back(1);

    graph[4].push_back(3);
    graph[8].push_back(4);

    graph[3].push_back(1);
    graph[6].push_back(3);

    graph[2].push_back(2);
    graph[7].push_back(2);

    graph[4].push_back(4);
    graph[9].push_back(4);
}

void HopcroftKarp::input_data() {
    std::cout<<"Enter the number of nodes on LEFT side of bipartite graph: ";
    scanf("%d", &num_nodes_left);
    
    std::cout<<"Enter the number of nodes on RIGHT side of bipartite graph: ";
    scanf("%d", &num_nodes_right);
    
    int total_edges, left_edge, right_edge;
    std::cout<<"Enter the total number of edges: ";
    scanf("%d", &total_edges);
    
    for(int i=0; i<total_edges; i++) {
        std::cout<<"Enter edge indices "<<i+1<<" of "<<total_edges<<" separated by a space: ";
        scanf("%d%d", &left_edge, &right_edge);
        right_edge += num_nodes_left;
        graph[left_edge].push_back(right_edge);
        graph[right_edge].push_back(left_edge);
    }
}

bool HopcroftKarp::bfs() {
    // Standard use of queues to perform BFS
    std::queue<int> queue;
    // Nodes are numbered 1 through n, and don't start from 0
    for(int i = 1; i <= num_nodes_left; i++) {
        // Check to see if there is a matching for this node already
        if(matching[i] == constants::NIL) {
            // Not found, set distance to 0 and add to queue
            distance[i] = 0;
            queue.push(i);
        } else {
            distance[i] = constants::INF;
        }
    }
    
    distance[constants::NIL] = constants::INF;

    // As long as the queue isn't empty...
    while(!queue.empty()) {
        int left = queue.front();
        queue.pop();
        // Sanity check
        if(left != constants::NIL) {
            // For each node on the right connected to left by an edge...
            for(int right : graph[left]) {
                // If the distance is set to INF/-1, set distance to be
                // that of left node + 1 (for this edge)
                if(distance[ matching[right] ] == constants::INF) {
                    distance[ matching[right] ] = distance[left] + 1;
                    queue.push(matching[right]);
                }
            }
        }
    }
    return (distance[constants::NIL] != constants::INF);
}

bool HopcroftKarp::dfs(int left) {
    // Only proceed with DFS if the node isn't NIL
    if(left != constants::NIL) {
        // For each node on the right connected to left by an edge...
        for(int right : graph[left]) {
            if(distance[ matching[right] ] == distance[ left ] + 1) {
                // Standard DFS recursion
                if(dfs(matching[right])) {
                    matching[left] = right;
                    matching[right] = left;
                    std::cout<<"\n\tFound Matching; left: "<<left<<", right: "<<right;
                    return true;
                }
            }
        }
        distance[left] = constants::INF;
        return false;
    }
    // Node was nil, no further depth search possible; return true
    return true;
}

void HopcroftKarp::output_matching(int num_matching) {
    std::cout<<"\n\tMaximum Cardinality Matching: "<<num_matching<<"\n";
}

void HopcroftKarp::run() {
    // Input data to form bipartite graph
    //input_data();
    input_data_test();

    // Run the algorithm to count max matching
    int num_matching;
    while(bfs()) {
        for(int i = 0; i <= num_nodes_left; i++) {
            if(matching[i] == constants::NIL && dfs(i)) {
                num_matching++;
            }
        }
    }

    // Output function
    output_matching(num_matching);
}

int main() {
    HopcroftKarp algorithm;
    algorithm.run();
    return 0;
}
