#include<iostream>
#include<algorithm>
// Need start
#include<vector>
#include<functional>
// Need end
using namespace std;
typedef pair<int, int> P;

// Copy start
template <typename T>
class SegTree {
private:
    size_t node_size_;
    vector<T> node_;
    T identity_;                     // ex) INF, 0, etc...
    function<T(T, T)> operation_;    // ex) min, max, sum, etc...
    function<T(T, T)> update_;       // ex) add, change, etc..
public:
    SegTree(size_t node_size, T identity, function<T(T, T)> operation, function<T(T, T)> update):
    identity_(identity), operation_(operation), update_(update) {
        node_size_ = 1;
        while (node_size_ < node_size) node_size_ *= 2;
        node_ = vector<T>(2 * node_size_ - 1, identity);
    }
    void change(int idx, T new_value) {
        int node_idx = idx + node_size_ - 1;
        node_[node_idx] = update_(node_[node_idx], new_value);
        while (node_idx > 0) {
            node_idx = (node_idx - 1) / 2;
            node_[node_idx] = operation_(node_[node_idx * 2 + 1], node_[node_idx * 2 + 2]);
        }
    }
    T _query(int left, int right, int node_idx, int node_left, int node_right) {
        if (node_right <= left || right <= node_left) {
            return identity_;
        }
        if (left <= node_left && node_right <= right) {
            return node_[node_idx];
        }
        else {
            T left_value = _query(left, right, node_idx * 2 + 1, node_left, (node_left + node_right) / 2);
            T right_value = _query(left, right, node_idx * 2 + 2, (node_left + node_right) / 2, node_right);
            return operation_(left_value, right_value);
        }
    }
    T query(int left, int right) {
        return _query(left, right, 0, 0, node_size_);
    }
    T operator[](int idx) {
        return node_[idx + node_size_ - 1];
    }
    // serach-method's usage is written on CF567
    int _search(int kth, int node_idx, int node_left, int node_right) {
        // kth >= 1
        if (node_right - node_left == 1) return node_idx - node_size_ + 1;
        if (node_[node_idx * 2 + 1] < kth) return _search(kth - node_[node_idx * 2 + 1], node_idx * 2 + 2, (node_left + node_right) / 2, node_right);
        else return _search(kth, node_idx * 2 + 1, node_left, (node_left + node_right) / 2);
    }
    int search(int kth) {
        return _search(kth, 0, 0, node_size_);
    }
};
// Copy end

/*
You have to pass update and operation function to SegTree.
It is very useful to use lambda functions.
For example,
1) Range Minimum Query
    auto operation = [](int a, int b) {return min(a, b);}
    auto update = [](int a, int b) {return b;}
2) Range Sum Query
    auto operation = [](int a, int b) {return a + b;}
    auto update = [](int a, int b) {return a + b;}
3) Set
    identity = 0
    auto operaton = [](int a, int b) {return a + b;}
    auto update = [](int a, int b) {return 1;}      // without duplicate
                or [](int a, int b) {return a + b;} // duplicate
    If you use SegTree as set, you can use search method.
    This method can be used for accessing k-th number in set.
    (Be careful that you cannot use Segtree as set when 
    set includes large number, because number is corresponding
    to SegTree's index.)
*/

const int MAX_W = 1e5 + 1;
const int INF = 1 << 30;

int main() {
    // This sample is Atcoder Beginners Contest 38 D
    int N, W, H;
    cin >> N;
    vector<P> box(N);
    for (int i = 0; i < N; i++) {
        cin >> W >> H;
        box[i] = P(W, H);
    }
    sort(box.begin(), box.end(), [](const P& l, const P&r) {
        if (l.first != r.first) return l.first < r.first;
        else return l.second > r.second;
    });
    SegTree<int> seg(MAX_W, INF, [](int a, int b) {return min(a, b);}, [](int a, int b) {return b;});
    vector<int> dp(N, 0);
    seg.change(0, 0);
    for (int i = 0; i < N; i++) {
        dp[i] = -seg.query(0, box[i].second) + 1;
        seg.change(box[i].second, -dp[i]);
    }
    int ans = -INF;
    for (int i = 0; i < N; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}