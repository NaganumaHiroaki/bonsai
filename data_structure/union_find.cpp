#include<iostream>
#include<algorithm>
// Need start
#include<vector>
// Need end
using namespace std;
typedef long long ll;

// Start
class UnionFind {
    private:
        ll node_num;
        vector<ll> parent;
        vector<ll> node_rank;
        vector<ll> sizes;
    public:
        UnionFind(ll n) {
            node_num = n;
            parent.resize(node_num);
            node_rank.resize(node_num);
            sizes.resize(node_num);
        }
        void init() {
            for (ll i = 0; i < node_num; i++) {
                parent[i] = i;
                node_rank[i] = 0;
                sizes[i] = 1;
            }
        }
        ll root(ll u) {
            return parent[u] == u ? u : parent[u] = root(parent[u]);
        }
        bool same(ll u, ll v) {
            return root(u) == root(v);
        }
        void unite(ll u, ll v) {
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
        ll get_size(ll u) {
            return sizes[root(u)];
        }
};
// End

int main() {
    // This sample usage is Atcoder Beginners Contest 120 D
    ll N, M;
    cin >> N >> M;
    UnionFind UF(N);
    UF.init();
    vector<ll> A(M), B(M);
    for (ll i = 0; i < M; i++) {
        cin >> A[i] >> B[i];
        A[i]--, B[i]--;
    }
    ll now_sizes = N * (N - 1) / 2;
    vector<ll> ans;
    for (ll i = M - 1; i >= 0; i--) {
        ans.push_back(now_sizes);
        if (UF.same(A[i], B[i])) {
            continue;
        }
        else {
            now_sizes -= UF.get_size(A[i]) * UF.get_size(B[i]);
            UF.unite(A[i], B[i]);
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << endl;
    }
    return 0;
}