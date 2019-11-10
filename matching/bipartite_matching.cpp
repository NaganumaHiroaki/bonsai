#include<iostream>
// Need start
#include<cstring>
#include<vector>
// Need end
using namespace std;

// Copy start
// time complexity is O(|E||V|)
class BipartiteMatching {
    private:
        int node_size;
        vector<vector<int> > graph;
        vector<int> match;
        vector<bool> is_used;
    public:
        BipartiteMatching(int n) {
            node_size = n;
            graph.resize(n);
            match.resize(n);
            is_used.resize(n);
        }
        void add_edge(int u, int v) {
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        bool dfs(int v) {
            is_used[v] = true;
            for (int i = 0; i < graph[v].size(); i++) {
                int u = graph[v][i], w = match[u];
                if (w < 0 || (!is_used[w] && dfs(w))) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
            return false;
        }
        int calc_match() {
            int cnt = 0;
            fill(match.begin(), match.end(), -1);
            for (int v = 0; v < node_size; v++) {
                if (match[v] < 0) {
                    fill(is_used.begin(), is_used.end(), false);
                    if (dfs(v)) cnt++;
                }
            }
            return cnt;
        }
};
// Copy end

char grid[44][44];
int number[44][44];

int main() {
    // This sample is AtCoder SoundHound Inc. Programming Contest 2018 C
    cin.tie(0);
    ios::sync_with_stdio(false);
    int R, C, V = 0;
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

    BipartiteMatching B(V); // initialize with node size

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == '*') continue;
            if (i + 1 < R && grid[i + 1][j] == '.') {
                B.add_edge(number[i][j], number[i + 1][j]);
            }
            if (j + 1 < C && grid[i][j + 1] == '.') {
                B.add_edge(number[i][j], number[i][j + 1]);
            }
        }
    }
    cout << V - B.calc_match() << endl;
    return 0;
}