#include<iostream>
#include<algorithm>
// Need start
#include<vector>
// Need end
using namespace std;

template <class T>
class WarshallFloyd {
    private:
        T identity_;
        vector<vector<T>> dist_;
    public:
        WarshallFloyd(int node_num, T identity):
        identity_(identity), dist_(vector<vector<T>>(node_num, vector<T>(node_num, identity))) {}
        void addEdge(int from, int to, T cost) {
            dist_[from][to] = cost;
        }
        void calcShortestPath() {
            int n = (int)dist_.size();
            for (int k = 0; k < n; ++k) {
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        if (dist_[i][k] == identity_ || dist_[k][j] == identity_) continue;
                        dist_[i][j] = min(dist_[i][j], dist_[i][k] + dist_[k][j]);
                    }
                }
            }
        }
        T getDist(int from, int to) {
            return dist_[from][to];
        }
};

using ll = long long;

const ll INF = 1LL << 50;

int main() {
    // This sample is Atcoder Beginners Contest 143 E
    int N, M;
    ll L;
    cin >> N >> M >> L;
    WarshallFloyd<ll> warshall_floyd1(N, INF);
    int A, B;
    ll C;
    for (int i = 0; i < M; ++i) {
        cin >> A >> B >> C;
        --A, --B;
        warshall_floyd1.addEdge(A, B, C);
        warshall_floyd1.addEdge(B, A, C);
    }
    int Q;
    cin >> Q;
    vector<int> S(Q), T(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> S[i] >> T[i];
        --S[i], --T[i];
    }
    warshall_floyd1.calcShortestPath();
    WarshallFloyd<ll> warshall_floyd2(N, INF);
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (warshall_floyd1.getDist(i, j) > L) {
                continue;
            }
            warshall_floyd2.addEdge(i, j, 1);
            warshall_floyd2.addEdge(j, i, 1);
        }
    }
    warshall_floyd2.calcShortestPath();
    for (int i = 0; i < Q; ++i) {
        ll ans = warshall_floyd2.getDist(S[i], T[i]);
        cout << (ans == INF ? -1 : ans - 1) << endl;
    }
    return 0;
}