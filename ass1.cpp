#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

void idsRecursive(pair<string, int> start, pair<string, int> target, map<pair<string, int>, vector<pair<string, int>>> &adj, int maxDepth) {
    for (int depth = 0; depth <= maxDepth; ++depth) {
        map<pair<string, int>, bool> vis;
        vector<pair<pair<string, int>, int>> ansAtDepth;

        dlsRecursive(start, adj, vis, ansAtDepth, 0, depth);

        for (auto node : ansAtDepth) {
            if (node.first == target) {
                cout << "Target found: " << node.first.first << " " << node.first.second << " at level " << node.second << endl;
                return;
            }
        }
    }
    cout << "Target not found within depth " << maxDepth << endl;
}

void dlsRecursive(pair<string, int> node, map<pair<string, int>, vector<pair<string, int>>> &adj, map<pair<string, int>, bool> &vis, vector<pair<pair<string, int>, int>> &ans, int level, int depth) {
    if (level > depth) return;
    ans.push_back({node, level});
    vis[node] = true;
    for (auto neighbor : adj[node]) {
        if (!vis[neighbor]) {
            dlsRecursive(neighbor, adj, vis, ans, level + 1, depth);
        }
    }
}

void dlsRecursivebfs(map<pair<string, int>, vector<pair<string, int>>> &adj, map<pair<string, int>, bool> &vis, vector<pair<pair<string, int>, int>> &ans, queue<pair<pair<string, int>, int>> &q, int level, int depth) {
    if (q.empty() || level > depth) {
        return;
    }
    auto [u, v] = q.front();
    q.pop();
    ans.push_back({u, v});
    for (auto neighbor : adj[u]) {
        if (!vis[neighbor]) {
            vis[neighbor] = true;
            q.push({neighbor, v + 1});
        }
    }
    dlsRecursivebfs(adj, vis, ans, q, level, depth);
}

void dfsRecursive(pair<string, int> node, map<pair<string, int>, vector<pair<string, int>>> &adj, map<pair<string, int>, bool> &vis, vector<pair<pair<string, int>, int>> &ans, int level) {
    ans.push_back({node, level});
    vis[node] = true;
    for (auto neighbor : adj[node]) {
        if (!vis[neighbor]) {
            dfsRecursive(neighbor, adj, vis, ans, level + 1);
        }
    }
}

void dfsNonRecursive(pair<string, int> start, map<pair<string, int>, vector<pair<string, int>>> &adj, vector<pair<pair<string, int>, int>> &ans) {
    map<pair<string, int>, bool> vis;
    stack<pair<pair<string, int>, int>> s;
    s.push({start, 0});
    while (!s.empty()) {
        auto [node, level] = s.top();
        s.pop();
        if (!vis[node]) {
            vis[node] = true;
            ans.push_back({node, level});
            for (auto nb = adj[node].rbegin(); nb != adj[node].rend(); ++nb) {
                if (!vis[*nb]) {
                    s.push({*nb, level + 1});
                }
            }
        }
    }
}

void bfsRecursive(map<pair<string, int>, vector<pair<string, int>>> &adj, map<pair<string, int>, bool> &vis, vector<pair<pair<string, int>, int>> &ans, queue<pair<pair<string, int>, int>> &q) {
    if (q.empty()) {
        return;
    }
    auto [u, v] = q.front();
    q.pop();
    ans.push_back({u, v});
    for (auto neighbor : adj[u]) {
        if (!vis[neighbor]) {
            vis[neighbor] = true;
            q.push({neighbor, v + 1});
        }
    }
    bfsRecursive(adj, vis, ans, q);
}

void bfsNonRecursive(pair<string, int> start, map<pair<string, int>, vector<pair<string, int>>> &adj, vector<pair<pair<string, int>, int>> &ans, int level) {
    map<pair<string, int>, bool> vis;
    queue<pair<pair<string, int>, int>> q;
    q.push({start, level});
    vis[start] = true;
    while (!q.empty()) {
        auto [u, v] = q.front();
        q.pop();
        ans.push_back({u, v});
        for (auto neighbor : adj[u]) {
            if (!vis[neighbor]) {
                vis[neighbor] = true;
                q.push({neighbor, v + 1});
            }
        }
    }
}

int main() {
    int n, m;
    cout << "Enter the number of students: ";
    cin >> n;
    cout << "Enter the number of relationships (edges): ";
    cin >> m;

    map<pair<string, int>, vector<pair<string, int>>> adj;
    for (int i = 0; i < m; i++) {
        string name1, name2;
        int marks1, marks2;
        cout << "Enter relationship " << i + 1 << " (name1 marks1 name2 marks2): ";
        cin >> name1 >> marks1 >> name2 >> marks2;
        adj[{name1, marks1}].push_back({name2, marks2});
        adj[{name2, marks2}].push_back({name1, marks1});
    }

    char ch;
    do {
        string startName;
        int startMarks, choice;
        cout << "Enter the starting student (name marks): ";
        cin >> startName >> startMarks;
        pair<string, int> start = {startName, startMarks};

        cout << "Choose algorithm:\n1) Recursive DFS\n2) Non-Recursive DFS\n3) Recursive BFS\n4) Non-Recursive BFS\n5) Recursive DLS(DFS)\n6) Recursive DLS(BFS)\n";
        cin >> choice;

        if (choice == 1) {
            map<pair<string, int>, bool> vis;
            vector<pair<pair<string, int>, int>> ans1;
            dfsRecursive(start, adj, vis, ans1, 0);
            cout << "DFS Recursive traversal:\n";
            cout << "Student Name  Marks  Level\n";
            for (auto node : ans1) {
                if (node.first.second >= 19) {
                    cout << node.first.first << "  " << node.first.second << "  " << node.second << endl;
                }
            }
            cout << endl;
        } else if (choice == 2) {
            vector<pair<pair<string, int>, int>> ans1;
            dfsNonRecursive(start, adj, ans1);
            cout << "DFS Non-Recursive traversal:\n";
            cout << "Student Name  Marks  Level\n";
            for (auto node : ans1) {
                if (node.first.second >= 19) {
                    cout << node.first.first << "  " << node.first.second << "  " << node.second << endl;
                }
            }
            cout << endl;
        } else if (choice == 3) {
            map<pair<string, int>, bool> vis;
            queue<pair<pair<string, int>, int>> q;
            q.push({start, 0});
            vis[start] = true;
            vector<pair<pair<string, int>, int>> ans1;
            bfsRecursive(adj, vis, ans1, q);
            cout << "BFS Recursive traversal:\n";
            cout << "Student Name  Marks  Level\n";
            for (auto node : ans1) {
                if (node.first.second >= 19) {
                    cout << node.first.first << "  " << node.first.second << "  " << node.second << endl;
                }
            }
            cout << endl;
        } else if (choice == 4) {
            vector<pair<pair<string, int>, int>> ans1;
            bfsNonRecursive(start, adj, ans1, 0);
            cout << "BFS Non-Recursive traversal:\n";
            cout << "Student Name  Marks  Level\n";
            for (auto node : ans1) {
                if (node.first.second >= 19) {
                    cout << node.first.first << "  " << node.first.second << "  " << node.second << endl;
                }
            }
            cout << endl;
        } else if (choice == 5) {
            map<pair<string, int>, bool> vis;
            int depth;
            cout << "Enter the max depth: ";
            cin >> depth;
            vector<pair<pair<string, int>, int>> ans1;
            dlsRecursive(start, adj, vis, ans1, 0, depth);
            cout << "DLS Recursive traversal:\n";
            cout << "Student Name  Marks  Level\n";
            for (auto node : ans1) {
                if (node.first.second >= 19) {
                    cout << node.first.first << "  " << node.first.second << "  " << node.second << endl;
                }
            }
        } else if (choice == 6) {
            map<pair<string, int>, bool> vis;
            queue<pair<pair<string, int>, int>> q;
            q.push({start, 0});
            vis[start] = true;
            int depth;
            cout << "Enter the max depth: ";
            cin >> depth;
            vector<pair<pair<string, int>, int>> ans1;
            dlsRecursivebfs(adj, vis, ans1, q, 0, depth);
            cout << "DLS Recursive BFS traversal:\n";
            cout << "Student Name  Marks  Level\n";
            for (auto node : ans1) {
                if (node.first.second >= 19) {
                    cout << node.first.first << "  " << node.first.second << "  " << node.second << endl;
                }
            }
        } else if (choice == 7) {
            string targetName;
            int targetMarks, depth;
            cout << "Enter the target student to find (name marks): ";
            cin >> targetName >> targetMarks;
            cout << "Enter the max depth: ";
            cin >> depth;
            pair<string, int> target = {targetName, targetMarks};
            idsRecursive(start, target, adj, depth);
        } else {
            cout << "Invalid choice. Try again.\n";
            continue;
        }
        cout << "Do you want to continue? (Y/N): ";
        cin >> ch;
    } while (ch == 'Y' || ch == 'y');

    return 0;
}