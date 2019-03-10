#include<iostream>
// Need start
#include<vector>
#include<queue>
#include<utility>
#include<limits>
// Need end
using namespace std;
typedef long long ll;
typedef pair<ll, ll> P;

// Copy start
template <class T>
class Dijkstra {
    private:
        struct edge {
            T to, cost;
        };
        T inf;
        T node_num;
        vector<vector<edge> > graph;
        vector<T> dist;
    public:
        Dijkstra(T n) {
            inf = numeric_limits<T>::max();  // please pay attention to overflow
            node_num = n;
            graph.resize(node_num);
            dist.resize(node_num);
            fill(dist.begin(), dist.end(), inf);
        }
        void add_edge(T from, T to, T cost) {
            edge e1 = {to, cost};
            graph[from].push_back(edge(e1));
        }
        void calc_shortest_path(T start) {
            priority_queue<P, vector<P>, greater<P> > PQ;
            dist[start] = 0;
            PQ.push(P(0, start));
            while (!PQ.empty()) {
                P now = PQ.top();
                PQ.pop();
                T now_u = now.second;
                if (dist[now_u] < now.first) continue;
                for (T i = 0; i < graph[now_u].size(); i++) {
                    edge e = graph[now_u][i];
                    if (dist[e.to] > dist[now_u] + e.cost) {
                        dist[e.to] = dist[now_u] + e.cost;
                        PQ.push(P(dist[e.to], e.to));
                    }
                }
            }
        }
        T get_dist(T u) {
            return dist[u];
        }
};
// Copy end

int main() {
    // This sample is Atcoder Beginners Contest 35 D
    ll N, M, T;
    cin >> N >> M >> T;
    vector<ll> A(N);
    for (ll i = 0; i < N; i++) cin >> A[i];
    ll a, b, c;
    Dijkstra<ll> D1(N), D2(N);
    for (ll i = 0; i < M; i++) {
        cin >> a >> b >> c;
        a--, b--;
        D1.add_edge(a, b, c);
        D2.add_edge(b, a, c);
    }
    D1.calc_shortest_path(0);
    D2.calc_shortest_path(0);
    ll ans = 0;
    ll INF = numeric_limits<ll>::max();
    for (ll u = 0; u < N; u++) {
        if (D1.get_dist(u) == INF || D2.get_dist(u) == INF) continue;
        ans = max(ans, A[u] * (T - D1.get_dist(u) - D2.get_dist(u)));
    }
    cout << ans << endl;
    return 0;
}