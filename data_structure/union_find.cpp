#include<iostream>
#include<algorithm>
// Need start
#include<vector>
// Need end
using namespace std;
typedef long long ll;

// Copy start
class UnionFind {
    private:
        vector<int> parent;
        vector<int> node_rank;
        vector<int> sizes;
    public:
        UnionFind(int node_num):
        parent(vector<int>(node_num)), node_rank(vector<int>(node_num)), sizes(vector<int>(node_num)) {
            for (int i = 0; i < node_num; ++i) {
                parent[i] = i;
                node_rank[i] = 0;
                sizes[i] = 1;
            }
        }
        int root(int u) {
            return parent[u] == u ? u : parent[u] = root(parent[u]);
        }
        bool same(int u, int v) {
            return root(u) == root(v);
        }
        void unite(int u, int v) {
            u = root(u);
            v = root(v);
            if (u == v) return;
            if (node_rank[u] < node_rank[v]) {
                parent[u] = v;
                sizes[v] += sizes[u];
            }
            else {
                parent[v] = u;
                sizes[u] += sizes[v];
                if (node_rank[u] == node_rank[v]) {
                    node_rank[u]++;
                }
            }
        }
        int get_size(int u) {
            return sizes[root(u)];
        }
};
// Copy end

int main() {
    // This sample is Atcoder Beginners Contest 120 D
    ll N, M;
    cin >> N >> M;
    UnionFind uf(N);
    vector<ll> A(M), B(M);
    for (ll i = 0; i < M; i++) {
        cin >> A[i] >> B[i];
        A[i]--, B[i]--;
    }
    ll now_sizes = N * (N - 1) / 2;
    vector<ll> ans;
    for (ll i = M - 1; i >= 0; i--) {
        ans.push_back(now_sizes);
        if (uf.same(A[i], B[i])) {
            continue;
        }
        else {
            now_sizes -= (ll)uf.get_size(A[i]) * (ll)uf.get_size(B[i]);
            uf.unite(A[i], B[i]);
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << endl;
    }
    return 0;
}