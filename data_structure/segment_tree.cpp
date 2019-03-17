#include<iostream>
#include<algorithm>
#include<utility>
// Need start
#include<limits>
#include<vector>
// Need end
using namespace std;
typedef pair<int, int> P;

// Copy start
template <class T>
class RangeMinimumQuerySegTree {
    private:
        int node_size;
        vector<T> node;
    public:
        RangeMinimumQuerySegTree(int n) {
            node_size = 1;
            while (node_size < n) node_size *= 2;
            node.resize(2 * node_size);
            fill(node.begin(), node.end(), numeric_limits<T>::max());
        }
        void update(int idx, T new_value) {
            int node_idx = idx + node_size - 1;
            node[node_idx] = new_value;
            while (node_idx > 0) {
                node_idx = (node_idx - 1) / 2;
                node[node_idx] = min(node[node_idx * 2 + 1], node[node_idx * 2 + 2]);
            }
        }
        T get_min(int left, int right, int node_idx, int node_left, int node_right) {
            // interval [node_left, node_right) corresponds to node_idx
            if (node_right <= left || right <= node_left) {
                return numeric_limits<T>::max();
            }
            if (left <= node_left && node_right <= right) {
                return node[node_idx];
            }
            else {
                T left_value = get_min(left, right, node_idx * 2 + 1, node_left, (node_left + node_right) / 2);
                T right_value = get_min(left, right, node_idx * 2 + 2, (node_left + node_right) / 2, node_right);
                return min(left_value, right_value);
            }
        }
};
// Copy end

const int MAX_W = 1e5 + 1;

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
    RangeMinimumQuerySegTree<int> S(MAX_W);
    vector<int> dp(N, 0);
    S.update(0, 0);
    // calc power of 2 value
    int pow_max_w = 1;
    while (pow_max_w < MAX_W) {
        pow_max_w *= 2;
    }
    for (int i = 0; i < N; i++) {
        dp[i] = -S.get_min(0, box[i].second, 0, 0, pow_max_w) + 1;  // set power of 2 value as forth argument
        S.update(box[i].second, -dp[i]);
    }
    int ans = numeric_limits<int>::min();
    for (int i = 0; i < N; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}