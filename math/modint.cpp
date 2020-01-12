// Need start
#include<iostream>
// Need end
using namespace std;

// Copy start
template<typename T, long long MOD_VALUE>
class ModInt {
    static constexpr long long MOD = MOD_VALUE;
    private:
        T value_;
    public:
        ModInt() {}
        ModInt(const T& value) {if (value >= 0) {value_ = value % MOD;} else {T k = (MOD - 1 - value) / MOD; value_ = (value + k * MOD) % MOD;}}
        ModInt& operator+=(const ModInt& x)  {value_ += x.value_; if (value_ >= MOD) value_ -= MOD; return *this;}
        friend ModInt& operator+=(const T& x, const ModInt& y) {ModInt res(x); res.value_ += x.value_; if (res.value_ >= MOD) res.value_ -= MOD; return res;}
        ModInt& operator-=(const ModInt& x) {if (value_ < x.value_) value_ += MOD; value_ -= x.value_; return *this;}
        friend ModInt& operator-=(const T& x, const ModInt& y) {ModInt res(x); if (res.value_ < y.value_) res.value_ += MOD; res.value_ -= y.value_; return res;}
        ModInt& operator*=(const ModInt& x) {value_ = (value_ * x.value_) % MOD; return *this;}
        friend ModInt& operator*=(const T& x, const ModInt& y) {ModInt res(x); res.value_ = (res.value_ * y.value_) % MOD; return res;}
        const ModInt operator+(const ModInt& x) const {return ModInt(*this) += x;}
        friend const ModInt operator+(const T& x, const ModInt& y) {return ModInt(x) += y;}
        const ModInt operator-(const ModInt& x) const {return ModInt(*this) -= x;}
        friend const ModInt operator-(const T& x, const ModInt& y) {return ModInt(x) -= y;}
        const ModInt operator*(const ModInt& x) const {return ModInt(*this) *= x;}
        friend const ModInt operator*(const T& x, const ModInt& y) {return ModInt(x) *= y;}
        static ModInt modpow(ModInt x, long long y) {ModInt z = 1; while (y > 0) {if (y & 1) {z *= x;}x *= x; y /= 2;} return z;}
        ModInt& operator/=(const ModInt& x) {return *this *= modpow(x, MOD - 2);}
        const ModInt operator/(const ModInt& x) const {return ModInt(*this) /= x;}
        friend const ModInt operator/(const T& x, const ModInt& y) {return ModInt(x) /= y;}
        ModInt operator++(int) {ModInt tmp(*this); value_ = (value_ + 1 == MOD ? 0 : value_ + 1); return tmp;}
        ModInt operator--(int) {ModInt tmp(*this); value_ = (value_ - 1 < 0 ? MOD - 1 : value_ - 1); return tmp;}
        friend istream& operator>>(istream& stream, ModInt& x) {stream >> x.value_; x.value_ %= MOD; return stream;}
        friend ostream& operator<<(ostream& stream, const ModInt& x) {stream << x.value_; return stream;}
};

// Need start
#include<vector>
// Need end

template<typename T, long long MOD>
class Combination {
    using mint = ModInt<T, MOD>;
    private:
        vector<mint> factorial_, inv_factorial_, inv_;
    public:
        Combination(int max_num)
            :factorial_(max_num + 1), inv_factorial_(max_num + 1), inv_(max_num + 1) {
            factorial_[0] = factorial_[1] = 1;
            inv_factorial_[0] = inv_factorial_[1] = 1;
            inv_[1] = 1;
            for (int i = 2; i <= max_num; i++) {
                factorial_[i] = factorial_[i - 1] * i;
                inv_[i] = MOD - inv_[MOD % i] * (MOD / i);
                inv_factorial_[i] = inv_factorial_[i - 1] * inv_[i];
            }
        }
        mint calc(int n, int k) {
            if (n < k) return 0;
            if (n < 0 || k < 0) return 0;
            return factorial_[n] * inv_factorial_[k] * inv_factorial_[n - k];
        }
};
// Copy end

using ll = long long;
using mint = ModInt<ll, 1000000007>;

#ifdef ABC_143_E

mint dfs(int k, const vector<vector<int>>& graph, int now, int from) {
    mint can_use_color_num;
    if (from == -1) {
        can_use_color_num = k - 1;
    }
    else {
        can_use_color_num = k - 2;
    }
    if (k < graph[now].size()) {
        return 0;
    }
    mint case_num = 1;
    for (int node : graph[now]) {
        if (node == from) continue;
        case_num *= can_use_color_num;
        can_use_color_num--;
    }
    for (int node : graph[now]) {
        if (node == from) continue;
        case_num *= dfs(k, graph, node, now);
    }
    return case_num;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    // This sample is AtCoder Beginners Contest 133 E
    int N, K;
    cin >> N >> K;
    vector<vector<int>> graph(N);
    int A, B;
    for (int i = 0; i < N - 1; ++i) {
        cin >> A >> B;
        --A, --B;
        graph[A].push_back(B);
        graph[B].push_back(A);
    }
    mint ans = mint(K) * dfs(K, graph, 0, -1);
    cout << ans << endl;
    return 0;
}
#endif

#ifdef JSC_2019_QUAL_B

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    // This sample is AtCoder Japan Saikyo Contest 2019 Qual B
    int N;
    mint K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    mint ans = 0;
    for (int i = 0; i < N; ++i) {
        mint cnt = 0;
        for (int j = 0; j < i; ++j) {
            if (A[j] > A[i]) cnt++;
        }
        ans += K * (2 * cnt + (K - 1) * cnt) / 2;
        cnt = 0;
        for (int j = i + 1; j < N; ++j) {
            if (A[j] > A[i]) cnt++;
        }
        ans += (K - 1) * (2 * cnt + (K - 2) * cnt) / 2;
    }
    cout << ans << endl;
    return 0;
}
#endif

//#ifdef ABC_132_D

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    // This sample is Atcoder Beginners Contest 132 D
    int N, K;
    cin >> N >> K;
    Combination<ll, 1000000007> combination(N);
    for (int i = 1; i <= K; i++) {
        mint k_div = combination.calc(K - 1, i - 1);
        mint all_div = combination.calc(N - K + 1, i);
        cout << k_div * all_div << endl;
    }
    return 0;
}
//#endif