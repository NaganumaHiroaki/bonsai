#include<iostream>
// Need start
#include<vector>
// Need end
using namespace std;

// Copy start
template <class T>
class Bellmanford {
    private:
        struct edge {
            int from, to;
            T cost;
        };
        T identity_;
        vector<edge> edges_;
        vector<T> dist_;
        vector<bool> in_negative_;
        bool negative_loop_;
    public:
        Bellmanford(int node_num, int edge_num, T identity):
        identity_(identity), dist_(vector<T>(node_num, identity)), in_negative_(vector<bool>(node_num, false)) {}
        void addEdge(int from, int to, T cost) {
            edge e = {from, to, cost};
            edges_.push_back(e);
        }
        void _calcShortestPath(int start_node) {
            dist_[start_node] = 0;
            int n = (int)dist_.size();
            int m = (int)edges_.size();
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    edge now_edge = edges_[j];
                    if (dist_[now_edge.from] != identity_ && dist_[now_edge.to] > dist_[now_edge.from] + now_edge.cost) {
                        dist_[now_edge.to] = dist_[now_edge.from] + now_edge.cost;
                        if (i == n - 1) {
                            negative_loop_ = true;
                            in_negative_[now_edge.to] = true;
                        }
                    }
                    if (in_negative_[now_edge.from]) {
                        in_negative_[now_edge.to] = true;
                    }
                }
            }
        }
        void calcShortestPath(int start_node) {
            _calcShortestPath(start_node);
            _calcShortestPath(start_node);
        }
        bool hasNegLoop() {
            return negative_loop_;
        }
        bool inNegLoop(int node) {
            return in_negative_[node];
        }
        T getDist(int node) {
            return dist_[node];
        }
};
// Copy end

const int INF = 1 << 30;

int main() {
    // This sample is Atcoder Beginners Contest 137 E
    int N, M, P;
    cin >> N >> M >> P;
    Bellmanford<int> bellmanford(N, M, INF);
    int A, B, C;
    for (int i = 0; i < M; ++i) {
        cin >> A >> B >> C;
        --A, --B;
        bellmanford.addEdge(A, B, P - C);
    }
    bellmanford.calcShortestPath(0);
    if (bellmanford.inNegLoop(N - 1)) {
        cout << -1 << endl;
    }
    else {
        cout << max(-bellmanford.getDist(N - 1), 0) << endl;
    }
    return 0;
}