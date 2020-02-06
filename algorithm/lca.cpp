// Need start
#include<vector>
// Need end
using namespace std;

// Copy start
class LCA {
    private:
        int max_log_v_;
        vector<vector<int>> parent_;
        vector<int> depth_;
        void dfs(const vector<vector<int>>& graph, int node, int parent, int dist) {
            parent_[0][node] = parent;
            depth_[node] = dist;
            for (auto next_node : graph[node]) {
                if (next_node != parent) {
                    dfs(graph, next_node, node, dist + 1);
                }
            }
        }
    public:
        LCA(const vector<vector<int>>& graph, int root) {
            max_log_v_ = 0;
            int node_num = (int)graph.size();
            depth_ = vector<int>(node_num);
            int tmp = node_num;
            while (tmp > 0) {
                ++max_log_v_;
                tmp /= 2;
            }
            parent_ = vector<vector<int>>(max_log_v_, vector<int>(node_num));
            dfs(graph, root, -1, 0);
            for (int i = 0; i < max_log_v_ - 1; ++i) {
                for (int node = 0; node < node_num; ++node) {
                    if (parent_[i][node] < 0) {
                        parent_[i + 1][node] = -1;
                    }
                    else {
                        parent_[i + 1][node] = parent_[i][parent_[i][node]];
                    }
                }
            }
        }
        int getLCA(int u, int v) {
            if (depth_[u] > depth_[v]) {
                swap(u, v);
            }
            for (int i = 0; i < max_log_v_; ++i) {
                if ((depth_[v] - depth_[u]) >> i & 1) {
                    v = parent_[i][v];
                }
            }
            if (u == v) {
                return u;
            }
            for (int i = max_log_v_ - 1; i >= 0; --i) {
                if (parent_[i][u] != parent_[i][v]) {
                    u = parent_[i][u];
                    v = parent_[i][v];
                }
            }
            return parent_[0][u];
        }
};
// Copy end

#include<iostream>
#include<string>
#include<map>
#define rep(i, start, end) for (int i = (int)start; i < (int)end; ++i)
#define rrep(i, start, end) for (int i = (int)start - 1; i >= end; --i)
#define iter(i, c) for (auto i = (c).begin(); i != (c).end(); ++i)
#define riter(i, c) for (auto i = (c).rbegin(); i != (c).rend(); ++i)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;
using ll = long long;
template<typename T> inline bool chmax(T& a, T b) {if (a < b) {a = b; return true;} return 0;}
template<typename T> inline bool chmin(T& a, T b) {if (a > b) {a = b; return true;} return 0;}

struct edge {
    int to_, color_;
    ll dist_;
    edge(int to, ll dist, int color):to_(to), color_(color), dist_(dist) {}
};

using P = pair<int, int>;

void dfs(const vector<vector<edge>>& graph, int node, int parent, vector<ll>& dist, vector<ll>& color, vector<ll>& color_dist, vector<vector<int>>& check_color, map<P, ll>& color_num, map<P, ll>& color_sum) {
    for (auto next_edge : graph[node]) {
        int next_node = next_edge.to_;
        if (next_node == parent) {
            continue;
        }
        int next_color = next_edge.color_;
        ll next_dist = next_edge.dist_;
        dist[next_node] = dist[node] + next_dist;
        ++color[next_color];
        color_dist[next_color] += next_dist;
        for (auto query_color : check_color[next_node]) {
            color_num[P(next_node, query_color)] = color[query_color];
            color_sum[P(next_node, query_color)] = color_dist[query_color];
        }
        dfs(graph, next_node, node, dist, color, color_dist, check_color, color_num, color_sum);
        --color[next_color];
        color_dist[next_color] -= next_dist;
    }
}

int main() {
    // This sample is ABC 133 F
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    vector<ll> A(N - 1), B(N - 1), C(N - 1), D(N - 1);
    rep(i, 0, N - 1) {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
        --C[i], --A[i], --B[i];
    }
    vector<ll> X(Q), Y(Q), U(Q), V(Q);
    rep(i, 0, Q) {
        cin >> X[i] >> Y[i] >> U[i] >> V[i];
        --X[i], --U[i], --V[i];
    }
    vector<vector<int>> graph_for_lca(N);
    vector<vector<edge>> graph(N);
    rep(i, 0, N - 1) {
        graph_for_lca[A[i]].push_back(B[i]);
        graph_for_lca[B[i]].push_back(A[i]);
        graph[A[i]].emplace_back(B[i], D[i], C[i]);
        graph[B[i]].emplace_back(A[i], D[i], C[i]);
    }

    LCA lca(graph_for_lca, 0);
    
    vector<vector<int>> check_color(N);
    rep(i, 0, Q) {
        check_color[U[i]].push_back(X[i]);
        check_color[V[i]].push_back(X[i]);
        check_color[lca.getLCA(U[i], V[i])].push_back(X[i]);
    }
    vector<ll> dist(N, 0), color(N, 0), color_dist(N, 0);
    map<P, ll> color_num, color_sum;

    dfs(graph, 0, -1, dist, color, color_dist, check_color, color_num, color_sum);

    rep(i, 0, Q) {
        ll dist1 = dist[U[i]] + Y[i] * color_num[P(U[i], X[i])] - color_sum[P(U[i], X[i])];
        ll dist2 = dist[V[i]] + Y[i] * color_num[P(V[i], X[i])] - color_sum[P(V[i], X[i])];
        int lca_node = lca.getLCA(U[i], V[i]);
        ll dist3 = dist[lca_node] + Y[i] * color_num[P(lca_node, X[i])] - color_sum[P(lca_node, X[i])];
        cout << dist1 + dist2 - 2 * dist3 << endl;
    }
    return 0;
}