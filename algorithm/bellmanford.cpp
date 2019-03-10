#include<iostream>
// Need start
#include<vector>
#include<limits>
// Need end
using namespace std;
typedef long long ll;

// Copy start
template <class T>
class Bellmanford {
    private:
        T inf;
        struct edge {
            T from, to, cost;
        };
        vector<edge> es;
        vector<T> dist;
        vector<T> is_negative;
        T node_num, edge_num;
        bool negative_loop;
    public:
        Bellmanford(T v, T e) {
            inf = numeric_limits<T>::max();  // please set yourself
            node_num = v;
            edge_num = e;
            dist.resize(node_num);
            is_negative.resize(node_num);
            negative_loop = false;
            fill(dist.begin(), dist.end(), inf);
            fill(is_negative.begin(), is_negative.end(), false);
        }
        void add_edge(T from, T to, T cost) {
            edge e = {from, to, cost};
            es.push_back(e);
        }
        void calc_shortest_path(T start) {
            dist[start] = 0;
            for (T i = 0; i < node_num; i++) {
                for (T j = 0; j < edge_num; j++) {
                    edge e = es[j];
                    if (dist[e.from] != inf && dist[e.to] > dist[e.from] + e.cost) {
                        dist[e.to] = dist[e.from] + e.cost;
                        if (i == node_num - 1) {
                            negative_loop = true;
                            is_negative[e.to] = true;
                        }
                    }
                    if (is_negative[e.from]) {
                        is_negative[e.to] = true;
                    }
                }
            }
        }
        bool is_negative_loop() {
            return negative_loop;
        }
        bool have_negative_path(T u) {
            // if path from start to u has negative loop, return true
            return is_negative[u];
        }
        T get_dist(T u) {
            return dist[u];
        }
};
// Copy end

int main() {
    // This sample is Atcoder Beginners Contest 61 D
    ll N, M;
    cin >> N >> M;
    ll a, b, c;
    Bellmanford<ll> B(N, M);
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;
        a--, b--;
        B.add_edge(a, b, -c);
    }
    B.calc_shortest_path(0);
    ll ans = -B.get_dist(N - 1);
    if (B.is_negative_loop() && B.have_negative_path(N - 1)) {
        cout << "inf" << endl;
    }
    else {
        cout << ans << endl;
    }
    return 0;
}