#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

void addEdge(map<int, vector<pair<int, int>>>& adj, int u, int v, int wt) {
    adj[u].push_back({v, wt});
    adj[v].push_back({u, wt}); // undirected graph
}

void primMST(int V, map<int, vector<pair<int, int>>>& adj) {
    // Min-heap: {weight, node, parent}
    priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;

    map<int, bool> vis;
    vector<vector<int>> mst; // Each entry: {node, weight, parent}
    
    pq.push({0, 0, -1}); // Start from node 0

    while (!pq.empty()) {
        vector<int> curr = pq.top(); pq.pop();
        int wt = curr[0], node = curr[1], parent = curr[2];

        if (vis[node]) continue;

        vis[node] = true;
        mst.push_back({node, wt, parent});

        for (auto [nbr, weight] : adj[node]) {
            if (!vis[nbr]) {
                pq.push({weight, nbr, node});
            }
        }
    }

    // Output
    cout << "Node\tWeight\tParent\n";
    for (auto& row : mst) {
        cout << row[0] << "\t" << row[1] << "\t";
        if (row[2] == -1)
            cout << "None\n";
        else
            cout << row[2] << "\n";
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    map<int, vector<pair<int, int>>> adj;

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, wt;
        cin >> u >> v >> wt;
        addEdge(adj, u, v, wt);
    }

    cout << "\nMinimum Spanning Tree:\n";
    primMST(V, adj);

    return 0;
}
