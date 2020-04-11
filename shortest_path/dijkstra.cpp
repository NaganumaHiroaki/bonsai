#include<iostream>
// Need start
#include<vector>
#include<queue>
// Need end
using namespace std;

// Copy start
template <typename T>
class Dijkstra {
private:
    using P = pair<T, int>;
    struct edge {
        int to;
        T cost;
        edge(int to, T cost):to(to), cost(cost) {}
    };
    T identity_;
    vector<vector<edge>> graph_;
    vector<T> dist_;
public:
    Dijkstra(int node_num, T identity):
    identity_(identity), graph_(vector<vector<edge>>(node_num)), dist_(vector<T>(node_num, identity)) {}
    void addEdge(int from, int to, T cost) {
        graph_[from].emplace_back(to, cost);
    }
    void calcShortestPath(int root) {
        priority_queue<P, vector<P>, greater<P>> que;
        dist_[root] = 0;
        que.push(P(0, root));
        while (!que.empty()) {
            P now = que.top();
            que.pop();
            int node = now.second;
            if (dist_[node] < now.first) continue;
            for (auto& e : graph_[node]) {
                if (dist_[e.to] > dist_[node] + e.cost) {
                    dist_[e.to] = dist_[node] + e.cost;
                    que.push(P(dist_[e.to], e.to));
                }
            }
        }
    }
    T getDist(int u) {
        return dist_[u];
    }
};
// Copy end

using ll = long long;

const ll INF = 1LL << 50;

int main() {
    // This sample is Atcoder Nikkei Contest 2019 Qual D
    int N, M;
    cin >> N >> M;
    Dijkstra<ll> dijkstra(N, INF);
    for (int i = 1; i < N; ++i) {
        dijkstra.addEdge(i, i - 1, 0);
    }
    int L, R;
    ll C;
    for (int i = 0; i < M; ++i) {
        cin >> L >> R >> C;
        --L, --R;
        dijkstra.addEdge(L, R, C);
    }
    dijkstra.calcShortestPath(0);
    ll ans = dijkstra.getDist(N - 1);
    cout << (ans == INF ? -1 : ans) << endl;
    return 0;
}