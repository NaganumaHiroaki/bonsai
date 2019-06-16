#include<iostream>
#include<algorithm>
#include<utility>
// Need start
#include<limits>
#include<vector>
#include<functional>
// Need end
using namespace std;
typedef pair<int, int> P;

// Copy start
template <typename T>
class SegTree {
    private:
        size_t node_size;
        vector<T> node;
        T identity;                     // ex) INF, 0, etc...
        function<T(T, T)> operation;    // ex) min, max, sum, etc...
        function<T(T, T)> update;       // ex) add, change, etc..
    public:
        SegTree(size_t _node_size, T _identity, function<T(T, T)> _operation, function<T(T, T)> _update):
        identity(_identity), operation(_operation), update(_update) {
            node_size = 1;
            while (node_size < _node_size) node_size *= 2;
            node = vector<T>(2 * node_size - 1, identity);
        }
        void change(int idx, T new_value) {
            int node_idx = idx + node_size - 1;
            node[node_idx] = update(node[node_idx], new_value);
            while (node_idx > 0) {
                node_idx = (node_idx - 1) / 2;
                node[node_idx] = operation(node[node_idx * 2 + 1], node[node_idx * 2 + 2]);
            }
        }
        T _query(int left, int right, int node_idx, int node_left, int node_right) {
            // interval [node_left, node_right) corresponds to node_idx
            if (node_right <= left || right <= node_left) {
                return identity;
            }
            if (left <= node_left && node_right <= right) {
                return node[node_idx];
            }
            else {
                T left_value = _query(left, right, node_idx * 2 + 1, node_left, (node_left + node_right) / 2);
                T right_value = _query(left, right, node_idx * 2 + 2, (node_left + node_right) / 2, node_right);
                return operation(left_value, right_value);
            }
        }
        T query(int left, int right) {
            return _query(left, right, 0, 0, node_size);
        }
        T operator[](int idx) {
            return node[idx + node_size - 1];
        }
};
// Copy end

/*
You have to pass update and operation function to SegTree.
It is very useful to use lambda functions.
For example,
1) Range Minimum Query
    auto operation = [](int a, int b) {return min(a, b)}
    auto update = [](int a, int b) {return b}
2) Range Sum Query
    auto operation = [](int a, int b) {return a + b}
    auto update = [](int a, int b) {return a + b}
*/

const int MAX_W = 1e5 + 1;
const int INF = 1 << 30;

bool comp(const P& l, const P& r) {
    if (l.first != r.first) return l.first < r.first;
    else return l.second > r.second;
}

int main() {
    // This sample is Atcoder Beginners Contest 38 D
    int N, W, H;
    cin >> N;
    vector<P> box(N);
    for (int i = 0; i < N; i++) {
        cin >> W >> H;
        box[i] = P(W, H);
    }
    sort(box.begin(), box.end(), comp);
    SegTree<int> S(MAX_W, INF, 
                    [](int a, int b) {return min(a, b);},
                    [](int a, int b) {return b;});
    vector<int> dp(N, 0);
    S.change(0, 0);
    for (int i = 0; i < N; i++) {
        dp[i] = -S.query(0, box[i].second) + 1;
        S.change(box[i].second, -dp[i]);
    }
    int ans = -INF;
    for (int i = 0; i < N; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}