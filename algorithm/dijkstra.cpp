#include<iostream>
// Need start
#include<vector>
#include<queue>
#include<utility>
#include<limits>
// Need end
using namespace std;
typedef long long ll;


// Copy start
template <class T>
class Dijkstra {
    private:
        using P = pair<T, int>;
        struct edge {
            int to;
            T cost;
        };
        T identity;
        vector<vector<edge> > graph;
        vector<T> dist;
    public:
        Dijkstra(int node_num, T _identity):
        identity(_identity), graph(vector<vector<edge> >(node_num)), dist(vector<T>(node_num, identity)) {}
        void add_edge(int from, int to, T cost) {
            edge now_edge = {to, cost};
            graph[from].push_back(now_edge);
        }
        void calc_shortest_path(int start_node) {
            priority_queue<P, vector<P>, greater<P> > PQ;
            dist[start_node] = 0;
            PQ.push(P(0, start_node));
            while (!PQ.empty()) {
                P now = PQ.top();
                PQ.pop();
                int now_u = now.second;
                if (dist[now_u] < now.first) continue;
                for (int i = 0; i < graph[now_u].size(); i++) {
                    edge e = graph[now_u][i];
                    if (dist[e.to] > dist[now_u] + e.cost) {
                        dist[e.to] = dist[now_u] + e.cost;
                        PQ.push(P(dist[e.to], e.to));
                    }
                }
            }
        }
        T get_dist(int u) {
            return dist[u];
        }
};
// Copy end


const ll INF = 1LL << 50;

int main() {
    // This sample is Atcoder Beginners Contest 35 D
    ll N, M, T;
    cin >> N >> M >> T;
    vector<ll> A(N);
    for (ll i = 0; i < N; i++) cin >> A[i];
    ll a, b, c;
    Dijkstra<ll> dkt1(N, INF), dkt2(N, INF);
    for (ll i = 0; i < M; i++) {
        cin >> a >> b >> c;
        a--, b--;
        dkt1.add_edge(a, b, c);
        dkt2.add_edge(b, a, c);
    }
    dkt1.calc_shortest_path(0);
    dkt2.calc_shortest_path(0);
    ll ans = 0;
    for (ll u = 0; u < N; u++) {
        if (dkt1.get_dist(u) == INF || dkt2.get_dist(u) == INF) continue;
        ans = max(ans, A[u] * (T - dkt1.get_dist(u) - dkt2.get_dist(u)));
    }
    cout << ans << endl;
    return 0;
}