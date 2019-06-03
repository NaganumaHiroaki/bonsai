#include<iostream>
// Need start
#include<cstring>
#include<vector>
// Need end
using namespace std;

// Copy start
const int MAX_V = 2002; // set your self
int V;                  // node number
vector<int> G[MAX_V];   // graph
int match[MAX_V];       // pair of matching
bool used[MAX_V];       // flag whether is checked or not by DFS

void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

bool dfs(int v) {
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        int u = G[v][i], w = match[u];
        if (w < 0 || (!used[w] && dfs(w))) {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

// O(|E||V|)
int bipartite_matching() {
    int res = 0;
    memset(match, -1, sizeof(match));
    for (int v = 0; v < V; v++) {
        if (match[v] < 0) {
            memset(used, 0, sizeof(used));
            if (dfs(v)) {
                res++;
            }
        }
    }
    return res;
}
// Copy end

int R, C;
char grid[44][44];
int number[44][44];

int main() {
    // This sample is AtCoder SoundHound Inc. Programming Contest 2018 C
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> R >> C;
    int now_number = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == '.') {
                number[i][j] = now_number++;
                V++;
            }
        }
    }
    // You don't need to add start and end node
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == '*') continue;
            if (i + 1 < R && grid[i + 1][j] == '.') {
                add_edge(number[i][j], number[i + 1][j]);
            }
            if (j + 1 < C && grid[i][j + 1] == '.') {
                add_edge(number[i][j], number[i][j + 1]);
            }
        }
    }
    cout << V - bipartite_matching() << endl;
    return 0;
}