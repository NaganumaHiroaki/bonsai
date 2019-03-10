#include<iostream>
// Need start
#include<vector>
#include<queue>
#include<utility>
// Need end
using namespace std;
typedef long long ll;
typedef pair<ll, ll> P;

// Copy start
struct edge {
    ll to, cost;
};

class Dijkstra {
    private:
        ll INF;
        ll node_num;
        vector<vector<edge> > graph;
        vector<ll> dist;
    public:
        Dijkstra(ll n) {
            INF = 1LL << 40;  // please pay attention to overflow
            node_num = n;
            graph.resize(node_num);
            dist.resize(node_num);
            fill(dist.begin(), dist.end(), INF);
        }
        void add_edge(ll u, ll v, ll cost) {
            edge e1 = {v, cost};
            graph[u].push_back(edge(e1));
        }
        void calc_min_dist(ll start) {
            priority_queue<P, vector<P>, greater<P> > PQ;
            dist[start] = 0;
            PQ.push(P(0, start));
            while (!PQ.empty()) {
                P now = PQ.top();
                PQ.pop();
                ll now_u = now.second;
                if (dist[now_u] < now.first) continue;
                for (ll i = 0; i < graph[now_u].size(); i++) {
                    edge e = graph[now_u][i];
                    if (dist[e.to] > dist[now_u] + e.cost) {
                        dist[e.to] = dist[now_u] + e.cost;
                        PQ.push(P(dist[e.to], e.to));
                    }
                }
            }
        }
        ll get_dist(ll u) {
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
    Dijkstra D1(N), D2(N);
    for (ll i = 0; i < M; i++) {
        cin >> a >> b >> c;
        a--, b--;
        D1.add_edge(a, b, c);
        D2.add_edge(b, a, c);
    }
    D1.calc_min_dist(0);
    D2.calc_min_dist(0);
    ll ans = 0;
    for (ll u = 0; u < N; u++) {
        ans = max(ans, A[u] * (T - D1.get_dist(u) - D2.get_dist(u)));
    }
    cout << ans << endl;
    return 0;
}