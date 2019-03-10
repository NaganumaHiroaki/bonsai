#include<iostream>
#include<algorithm>
// Need start
#include<vector>
#include<limits>
// Need end
using namespace std;

template <class T>
class WarshallFloyd {
    private:
        T inf;
        T node_num;
        vector<vector<T> > dist;
    public:
        WarshallFloyd(T n) {
            inf = numeric_limits<T>::max();
            node_num = n;
            dist.resize(node_num);
            for (T i = 0; i < node_num; i++) {
                dist[i].resize(node_num);
                fill(dist[i].begin(), dist[i].end(), inf);
            }
        }
        void add_edge(T from, T to, T cost) {
            dist[from][to] = cost;
        }
        void calc_shortest_path() {
            for (T k = 0; k < node_num; k++) {
                for (T i = 0; i < node_num; i++) {
                    for (T j = 0; j < node_num; j++) {
                        if (dist[i][k] == inf || dist[k][j] == inf) continue;
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        T get_dist(T from, T to) {
            return dist[from][to];
        }
};

int main() {
    // This sample is Atcoder Beginners Contest 73 D
    int N, M, R, A, B, C;
    cin >> N >> M >> R;
    vector<int> r(R);
    for (int i = 0; i < R; i++) {
        cin >> r[i];
        r[i]--;
    }
    WarshallFloyd<int> W(N);
    for (int i = 0; i < M; i++) {
        cin >> A >> B >> C;
        A--, B--;
        W.add_edge(A, B, C);
        W.add_edge(B, A, C);
    }
    W.calc_shortest_path();
    vector<int> perm(R);
    for (int i = 0; i < R; i++) {
        perm[i] = i;
    }
    int ans = numeric_limits<int>::max();
    int inf = numeric_limits<int>::max();
    do {
        int now_dist = 0;
        for (int i = 1; i < R; i++) {
            if (W.get_dist(r[perm[i - 1]], r[perm[i]]) == inf) {
                now_dist = inf;
                break;
            }
            now_dist += W.get_dist(r[perm[i - 1]], r[perm[i]]);
        }
        ans = min(ans, now_dist);
    } while (next_permutation(perm.begin(), perm.end()));
    cout << ans << endl;
    return 0;
}