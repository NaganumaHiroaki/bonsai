/*
<reference> --> http://kagamiz.hatenablog.com/entry/2012/12/18/220849
*/
#include<iostream>
// Need start
#include<functional>
#include<vector>
// Need end
#include<string>
#define rep(i, start, end) for (int i = (int)start; i < (int)end; ++i)
#define rrep(i, start, end) for (int i = (int)start - 1; i >= end; --i)
#define iter(i, c) for (auto i = (c).begin(); i != (c).end(); ++i)
#define riter(i, c) for (auto i = (c).rbegin(); i != (c).rend(); ++i)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;
using ll = long long;

template <typename T>
class StarrySkyTree {
    private:
        size_t node_size_;
        vector<T> result_node_, added_node_;
        T identity_;                     // ex) INF, -INF
        function<T(T, T)> operation_;    // ex) min, max
    public:
        StarrySkyTree(size_t node_size, T identity, function<T(T, T)> operation):
        identity_(identity), operation_(operation) {
            node_size_ = 1;
            while (node_size_ < node_size) node_size_ *= 2;
            result_node_ = vector<T>(2 * node_size_ - 1, identity);
            added_node_ = vector<T>(2 * node_size_ - 1, identity);
        }
        void _add(int left, int right, T value, int node_idx, int node_left, int node_right) {
            if (node_right <= left || right <= node_left) {
                return;
            }
            if (left <= node_left && node_right <= right) {
                added_node_[node_idx] += value;
                return;
            }
            _add(left, right, value, node_idx * 2 + 1, node_left, (node_left + node_right) / 2);
            _add(left, right, value, node_idx * 2 + 2, (node_left + node_right) / 2, node_right);
            result_node_[node_idx] = operation_(result_node_[node_idx * 2 + 1] + added_node_[node_idx * 2 + 1], result_node_[node_idx * 2 + 2] + added_node_[node_idx * 2 + 2]);
        }
        void add(int left, int right, T value) {
            _add(left, right, value, 0, 0, node_size_);
        }
        T _query(int left, int right, int node_idx, int node_left, int node_right) {
            if (node_right <= left || right <= node_left) {
                return identity_;
            }
            if (left <= node_left && node_right <= right) {
                return result_node_[node_idx] + added_node_[node_idx];
            }
            else {
                T left_value = _query(left, right, node_idx * 2 + 1, node_left, (node_left + node_right) / 2);
                T right_value = _query(left, right, node_idx * 2 + 2, (node_left + node_right) / 2, node_right);
                return operation_(left_value, right_value) + added_node_[node_idx];
            }
        }
        T query(int left, int right) {
            return _query(left, right, 0, 0, node_size_);
        }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    // This sample is AtCoder Educational DP Contest W
    int N, M;
    cin >> N >> M;
    vector<ll> L(M), R(M), A(M);
    rep(i, 0, M) {
        cin >> L[i] >> R[i] >> A[i];
    }
    vector<vector<int>> interval_idx(N + 1);
    rep(i, 0, M) {
        interval_idx[R[i]].push_back(i);
    }
    StarrySkyTree<ll> dp(N + 1, 0, [](ll a, ll b) {return max(a, b);});
    rep(i, 1, N + 1) {
        ll max_val = dp.query(0, i);
        dp.add(i, i + 1, max_val);
        rep(j, 0, interval_idx[i].size()) {
            int idx = interval_idx[i][j];
            dp.add(L[idx], R[idx] + 1, A[idx]);
        }
    }
    cout << dp.query(0, N + 1) << endl;
    return 0;
}