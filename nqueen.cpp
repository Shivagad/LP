#include <bits/stdc++.h>
using namespace std;

bool issafe(vector<string>& v, int row, int col, int n) {
    int i = row;
    int j = col;
    for (int k = col; k >= 0; k--) {
        if (v[row][k] == 'Q') return false;
    }
    row = i;
    col = j;
    for (int k = row, l = col; k >= 0 && l >= 0; k--, l--) {
        if (v[k][l] == 'Q') return false;
    }
    for (int k = row, l = col; k <n  && l >= 0; k++, l--) {
        if (v[k][l] == 'Q') return false;
    }
    return true;
}
void backtracking(int n, vector<vector<string>>& ans, vector<string>& v, int col) {
    if (col == n) {
        ans.push_back(v);
        return;
    }

    for (int row = 0; row < n; row++) {
        if (issafe(v, row, col, n)) {
            v[row][col] = 'Q';
            backtracking(n, ans, v, col + 1);
            v[row][col] = '.';
        }
    }
}

void optimize(int n, vector<vector<string>>& ans, vector<string>& v, int col,vector<int>&rowopt,vector<int>&lower,vector<int>&upper) {
    if (col == n) {
        ans.push_back(v);
        return;
    }

    for (int row = 0; row < n; row++) {
        if (rowopt[row]==0&&lower[row+col]==0&&upper[n-1+col-row]==0) {
            v[row][col] = 'Q';
            rowopt[row]=1;
            lower[row+col]=1;
            upper[n-1+col-row]=1;
            optimize(n, ans, v, col + 1,rowopt,lower,upper);
            v[row][col] = '.';
            rowopt[row]=0;
            lower[row+col]=0;
            upper[n-1+col-row]=0;
        }
    }
}

int main() {
    int n;
    cout << "enter the n:" << endl;
    cin >> n;
    vector<vector<string>> ans;
    vector<string> v(n, string(n, '.'));
    // backtracking(n, ans, v, 0);
    vector<int>rowopt(n,0);
    vector<int>upper(2*n-1,0);
    vector<int>lower(2*n-1,0);
    optimize(n, ans, v, 0,rowopt,upper,lower);
    for (int i = 0; i < ans.size(); i++) {
        vector<string> v1 = ans[i];
        for (int j = 0; j < v1.size(); j++) {
            cout << v1[j] << endl;
        }
        cout << "next" << endl;
    }
}