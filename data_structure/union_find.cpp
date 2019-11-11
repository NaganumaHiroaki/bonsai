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
        vector<int> parent_;
        vector<int> node_rank_;
        vector<int> sizes_;
    public:
        UnionFind(int node_num):
        parent_(vector<int>(node_num)), node_rank_(vector<int>(node_num)), sizes_(vector<int>(node_num)) {
            for (int i = 0; i < node_num; ++i) {
                parent_[i] = i;
                node_rank_[i] = 0;
                sizes_[i] = 1;
            }
        }
        int getRoot(int u) {
            return parent_[u] == u ? u : parent_[u] = getRoot(parent_[u]);
        }
        bool isSame(int u, int v) {
            return getRoot(u) == getRoot(v);
        }
        void unite(int u, int v) {
            u = getRoot(u);
            v = getRoot(v);
            if (u == v) return;
            if (node_rank_[u] < node_rank_[v]) {
                parent_[u] = v;
                sizes_[v] += sizes_[u];
            }
            else {
                parent_[v] = u;
                sizes_[u] += sizes_[v];
                if (node_rank_[u] == node_rank_[v]) {
                    node_rank_[u]++;
                }
            }
        }
        int getSize(int u) {
            return sizes_[getRoot(u)];
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
        if (uf.isSame(A[i], B[i])) {
            continue;
        }
        else {
            now_sizes -= (ll)uf.getSize(A[i]) * (ll)uf.getSize(B[i]);
            uf.unite(A[i], B[i]);
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << endl;
    }
    return 0;
}