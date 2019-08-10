#include<iostream>
// Need start
#include<vector>
// Need end
using namespace std;
typedef long long ll;

// Copy start
template <class T>
class Bellmanford {
    private:
        T identity;
        struct edge {
            int from, to;
            T cost;
        };
        vector<edge> edges;
        vector<T> dist;
        vector<bool> in_negative;
        bool negative_loop;
    public:
        Bellmanford(int node_num, int edge_num, T _identity):identity(_identity), dist(vector<T>(node_num, _identity)), in_negative(vector<bool>(node_num, false)) {}
        void add_edge(int from, int to, T cost) {
            edge e = {from, to, cost};
            edges.push_back(e);
        }
        void _calc_shortest_path(int start_node) {
            dist[start_node] = 0;
            int n = (int)dist.size();
            int m = (int)edges.size();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    edge now_edge = edges[j];
                    if (dist[now_edge.from] != identity && dist[now_edge.to] > dist[now_edge.from] + now_edge.cost) {
                        dist[now_edge.to] = dist[now_edge.from] + now_edge.cost;
                        if (i == n - 1) {
                            negative_loop = true;
                            in_negative[now_edge.to] = true;
                        }
                    }
                    if (in_negative[now_edge.from]) {
                        in_negative[now_edge.to] = true;
                    }
                }
            }
        }
        void calc_shortest_path(int start_node) {
            // for the function "in_negative_loop", run _calc_shortest_path twice
            _calc_shortest_path(start_node);
            _calc_shortest_path(start_node);
        }
        bool have_negative_loop() {
            return negative_loop;
        }
        bool in_negative_loop(int node) {
            // return if node is in negative loop
            return in_negative[node];
        }
        T get_dist(int node) {
            return dist[node];
        }
};
// Copy end

int main() {
    // This sample is Atcoder Beginners Contest 61 D
    ll N, M;
    cin >> N >> M;
    ll a, b, c;
    Bellmanford<ll> bell(N, M, 1LL << 50);
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;
        a--, b--;
        bell.add_edge(a, b, -c);
    }
    bell.calc_shortest_path(0);
    ll ans = -bell.get_dist(N - 1);
    if (bell.have_negative_loop() && bell.in_negative_loop(N - 1)) {
        cout << "inf" << endl;
    }
    else {
        cout << ans << endl;
    }
    return 0;
}