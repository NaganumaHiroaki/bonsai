#include<iostream>
#include<utility>
#include<algorithm>
// Need start
#include<vector>
#include<functional>
// Need end
using namespace std;
typedef pair<int, int> P;

// Copy start
template <typename T>
class BIT {
    // 1-indexed
    private:
        size_t node_size;
        vector<T> node;
        T identity;
        function<T(T, T)> operation;
        function<T(T, T)> update;
    public:
        BIT(size_t _node_size, T _identity, function<T(T, T)> _operation, function<T(T, T)> _update):
        node_size(_node_size), identity(_identity), operation(_operation), update(_update) {
            node = vector<T>(node_size + 1, identity);
        }
        void change(int idx, T new_value) {
            node[idx] = update(node[idx], new_value);
            while (idx <= node_size) {
                idx += idx & -idx;
                if (idx > node_size) break;
                node[idx] = operation(node[idx], new_value);
            }
        }
        T query(int idx) {
            T res = identity;
            while (idx > 0) {
                res = operation(res, node[idx]);
                idx -= idx & -idx;
            }
            return res;
        }
};
// Copy end

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
    vector<P> box(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> W >> H;
        W++, H++;  // BIT is 1-indexed, so add offset
        box[i] = P(W, H);
    }
    box[0] = P(0, 0);
    sort(box.begin(), box.end(), comp);
    BIT<int> B(MAX_W, -INF, 
                [](int a, int b) {return max(a, b);},
                [](int a, int b) {return b;});
    vector<int> dp(N + 1);
    B.change(1, 0);  // H = 1 (H = 0) 
    for (int i = 1; i <= N; i++) {
        dp[i] = B.query(box[i].second - 1) + 1;
        B.change(box[i].second, dp[i]);
    }
    int ans = -INF;
    for (int i = 1; i <= N; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}