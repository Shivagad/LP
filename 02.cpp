#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

const int N = 3;
const vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};


const vector<pair<int, int>> directions = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};


// Convert board to string for visited state tracking
string boardToString(const vector<vector<int>>& board) {
    string s;
    for (auto row : board)
        for (int val : row)
            s += to_string(val);
    return s;
}

// Heuristic: count misplaced tiles
int misplacedTiles(const vector<vector<int>>& board) {
    int count = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (board[i][j] != 0 && board[i][j] != goal[i][j])
                count++;
    return count;
}

// Print board
void printBoard(const vector<vector<int>>& board) {
    for (auto row : board) {
        for (int val : row)
            cout << (val == 0 ? " " : to_string(val)) << " ";
        cout << endl;
    }
    cout << "---------------------\n";
}

// A* search with simple priority queue and parallel arrays
void solveAStar(vector<vector<int>> start) {
    int sx, sy;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (start[i][j] == 0)
                sx = i, sy = j;

    // Priority queue: stores f (g + h) values and index into the below vectors
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    // Parallel vectors to store state info
    vector<vector<vector<int>>> boards;  // list of board states
    vector<int> g_values;                // g cost
    vector<int> x_vals, y_vals;          // blank tile positions

    set<string> visited;

    int h = misplacedTiles(start);
    boards.push_back(start);
    g_values.push_back(0);
    x_vals.push_back(sx);
    y_vals.push_back(sy);

    pq.push({h, 0}); // {f, index}

    while (!pq.empty()) {
        auto [f, idx] = pq.top(); pq.pop();

        auto board = boards[idx];
        int g = g_values[idx];
        int x = x_vals[idx];
        int y = y_vals[idx];

        string stateStr = boardToString(board);
        if (visited.count(stateStr)) continue;
        visited.insert(stateStr);

        cout << "Step " << g << " | Heuristic (h): " << f - g << " | Total (f = g + h): " << f << endl;
        printBoard(board);

        if (board == goal) {
            cout << "✅ Puzzle solved in " << g << " moves.\n";
            return;
        }

        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                auto newBoard = board;
                swap(newBoard[x][y], newBoard[nx][ny]);
                string newStr = boardToString(newBoard);

                if (!visited.count(newStr)) {
                    int newG = g + 1;
                    int newH = misplacedTiles(newBoard);
                    int newIdx = boards.size();

                    boards.push_back(newBoard);
                    g_values.push_back(newG);
                    x_vals.push_back(nx);
                    y_vals.push_back(ny);

                    pq.push({newG + newH, newIdx});
                }
            }
        }
    }

    cout << "❌ No solution found.\n";
}

int main() {
    vector<vector<int>> start(3, vector<int>(3));
    cout << "Enter the initial 8-puzzle state (use 0 for blank):\n";
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> start[i][j];

    solveAStar(start);
    return 0;
}
