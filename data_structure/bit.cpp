#include<iostream>
#include<utility>
#include<algorithm>
// Need start
#include<vector>
// Need end
using namespace std;
typedef long long ll;
typedef pair<ll, ll> P;

// Copy start
class SumBIT {
    // 1-indexed
    private:
        ll node_num;
        vector<ll> bit;
    public:
        SumBIT(ll n) {
            node_num = n;
            bit.resize(node_num);
        }
        ll get_sum(ll idx) {
            ll sum_num = 0;
            while (idx > 0) {
                sum_num += bit[idx];
                idx -= idx & -idx;
            }
            return sum_num;
        }
        void update(ll idx, ll x) {
            while (idx <= node_num) {
                bit[idx] += x;
                idx += idx & -idx;
            }
        }
};

class RangeMinimumQueryBIT {
    // 1-indexed
    private:
        ll INF;
        ll node_num;
        vector<ll> bit;
    public:
        RangeMinimumQueryBIT(ll n) {
            INF = 1LL << 40;  // please pay attention to overflow
            node_num = n;
            bit.resize(node_num + 1);
        }
        ll get_min(ll idx) {
            ll min_num = INF;
            while (idx > 0) {
                min_num = min(min_num, bit[idx]);
                idx -= idx & -idx;
            }
            return min_num;
        }
        void update(ll idx, ll x) {
            bit[idx] = x;
            while (idx <= node_num) {
                bit[idx] = min(bit[idx], x);
                idx += idx & -idx;
            }
        }
};

class RangeMaxQueryBIT {
    // 1-indexed
    private:
        ll node_num;
        vector<ll> bit;
    public:
        RangeMaxQueryBIT(ll n) {
            node_num = n;
            bit.resize(node_num + 1);
        }
        ll get_max(ll idx) {
            ll max_num = 0;
            while (idx > 0) {
                max_num = max(max_num, bit[idx]);
                idx -= idx & -idx;
            }
            return max_num;
        }
        void update(ll idx, ll x) {
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
        box[i] = P(W, H);
    }
    box[0] = P(0, 0);
    sort(box.begin(), box.end(), comp);
    RangeMaxQueryBIT B(MAX_W);
    vector<ll> dp(N + 1);
    for (ll i = 1; i <= N; i++) {
        dp[i] = B.get_max(box[i].second - 1) + 1;
        B.update(box[i].second, dp[i]);
    }
    ll ans = 0;
    for (ll i = 1; i <= N; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}