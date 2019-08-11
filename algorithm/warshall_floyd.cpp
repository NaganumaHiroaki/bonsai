#include<iostream>
#include<algorithm>
// Need start
#include<vector>
// Need end
using namespace std;

template <class T>
class WarshallFloyd {
    private:
        T identity;
        vector<vector<T> > dist;
    public:
        WarshallFloyd(int node_num, T _identity):
        identity(_identity), dist(vector<vector<T> >(node_num, vector<T>(node_num, _identity))) {}
        void add_edge(int from, int to, T cost) {
            dist[from][to] = cost;
        }
        void calc_shortest_path() {
            int n = (int)dist.size();
            for (int k = 0; k < n; k++) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (dist[i][k] == identity || dist[k][j] == identity) continue;
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        T get_dist(int from, int to) {
            return dist[from][to];
        }
};

const int INF = 1 << 30;

int main() {
    // This sample is Atcoder Beginners Contest 73 D
    int N, M, R, A, B, C;
    cin >> N >> M >> R;
    vector<int> r(R);
    for (int i = 0; i < R; i++) {
        cin >> r[i];
        r[i]--;
    }
    WarshallFloyd<int> warshall(N, INF);
    for (int i = 0; i < M; i++) {
        cin >> A >> B >> C;
        A--, B--;
        warshall.add_edge(A, B, C);
        warshall.add_edge(B, A, C);
    }
    warshall.calc_shortest_path();
    vector<int> perm(R);
    for (int i = 0; i < R; i++) {
        perm[i] = i;
    }
    int ans = INF;
    do {
        int now_dist = 0;
        for (int i = 1; i < R; i++) {
            if (warshall.get_dist(r[perm[i - 1]], r[perm[i]]) == INF) {
                now_dist = INF;
                break;
            }
            now_dist += warshall.get_dist(r[perm[i - 1]], r[perm[i]]);
        }
        ans = min(ans, now_dist);
    } while (next_permutation(perm.begin(), perm.end()));
    cout << ans << endl;
    return 0;
}