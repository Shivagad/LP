#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <climits>
using namespace std;

class Graph {
public:
    void dijkstra(int src, const map<int, vector<pair<int, int>>>& adjList, int V) {
        // Min-heap priority queue: (distance, node)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    
        // Using vector for distances instead of map
        vector<int> dist(V, INT_MAX);  // Initialize with INF
        dist[src] = 0;
        
        pq.push({0, src});  // Push source with distance 0

        while (!pq.empty()) {
            auto [currDist, u] = pq.top();
            pq.pop();

            // Check all neighbors of the current node
            for (auto [v, weight] : adjList.at(u)) {
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        // Output the shortest path from the source to all nodes
        for (int i = 0; i < V; i++) {
            if (dist[i] == INT_MAX)
                cout << "No path from " << src << " to " << i << endl;
            else
                cout << "Shortest path from " << src << " to " << i << " is " << dist[i] << endl;
        }
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    map<int, vector<pair<int, int>>> adjList;

    cout << "Enter edges in format: src dest weight\n";
    for (int i = 0; i < E; ++i) {
        int u, v, wt;
        cin >> u >> v >> wt;
        adjList[u].push_back({v, wt});
        adjList[v].push_back({u, wt}); // For undirected graph
    }

    int src;
    cout << "Enter source node: ";
    cin >> src;

    cout << "\n--- Dijkstra's Algorithm Output ---\n";
    Graph g;
    g.dijkstra(src, adjList, V);

    return 0;
}
