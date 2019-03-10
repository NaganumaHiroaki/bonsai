#include<iostream>
#include<utility>
#include<algorithm>
// Need start
#include<limits>
#include<vector>
// Need end
using namespace std;
typedef long long ll;
typedef pair<ll, ll> P;

// Copy start
template <class T>
class SumBIT {
    // 1-indexed
    private:
        T node_num;
        vector<T> bit;
    public:
        SumBIT(T n) {
            node_num = n;
            bit.resize(node_num);
            fill(bit.begin(), bit.end(), 0);
        }
        T get_sum(T idx) {
            T sum_num = 0;
            while (idx > 0) {
                sum_num += bit[idx];
                idx -= idx & -idx;
            }
            return sum_num;
        }
        void update(T idx, T x) {
            while (idx <= node_num) {
                bit[idx] += x;
                idx += idx & -idx;
            }
        }
};

template <class T>
class RangeMinimumQueryBIT {
    // 1-indexed
    private:
        T inf;
        T node_num;
        vector<T> bit;
    public:
        RangeMinimumQueryBIT(T n) {
            inf = numeric_limits<T>::max();  // please pay attention to overflow
            node_num = n;
            bit.resize(node_num + 1);
            fill(bit.begin(), bit.end(), inf);
        }
        T get_min(T idx) {
            T min_num = inf;
            while (idx > 0) {
                min_num = min(min_num, bit[idx]);
                idx -= idx & -idx;
            }
            return min_num;
        }
        void update(T idx, T x) {
            bit[idx] = x;
            while (idx <= node_num) {
                bit[idx] = min(bit[idx], x);
                idx += idx & -idx;
            }
        }
};

template <class T>
class RangeMaxQueryBIT {
    // 1-indexed
    private:
        T min_inf;
        T node_num;
        vector<T> bit;
    public:
        RangeMaxQueryBIT(T n) {
            min_inf = numeric_limits<T>::min();  // please set yourself
            node_num = n;
            bit.resize(node_num + 1);
            fill(bit.begin(), bit.end(), min_inf);
        }
        T get_max(T idx) {
            T max_num = min_inf;
            while (idx > 0) {
                max_num = max(max_num, bit[idx]);
                idx -= idx & -idx;
            }
            return max_num;
        }
        void update(T idx, T x) {
            bit[idx] = x;
            while (idx <= node_num) {
                bit[idx] = max(bit[idx], x);
                idx += idx & -idx;
            }
        }
};
// Copy end

const ll MAX_W = 1e5 + 1;

bool comp(const P& l, const P& r) {
    if (l.first != r.first) return l.first < r.first;
    else return l.second > r.second;
}

int main() {
    // This sample is Atcoder Beginners Contest 38 D
    ll N, W, H;
    cin >> N;
    vector<P> box(N + 1);
    for (ll i = 1; i <= N; i++) {
        cin >> W >> H;
        W++, H++;  // BIT is 1-indexed, so add offset
        box[i] = P(W, H);
    }
    box[0] = P(0, 0);
    sort(box.begin(), box.end(), comp);
    RangeMaxQueryBIT<ll> B(MAX_W);
    vector<ll> dp(N + 1);
    B.update(1, 0);  // H = 1 (H = 0) 
    for (ll i = 1; i <= N; i++) {
        dp[i] = B.get_max(box[i].second - 1) + 1;
        B.update(box[i].second, dp[i]);
    }
    ll ans = numeric_limits<ll>::min();
    for (ll i = 1; i <= N; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}