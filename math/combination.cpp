#include<iostream>
// Need start
#include<vector>
// Need end
using namespace std;

template<typename T>
class Combination {
    private:
        T mod;
        vector<T> factorial, inv_factorial, inv;
    public:
        Combination(int max_number, T _mod):
        mod(_mod), factorial(max_number + 1), inv_factorial(max_number + 1), inv(max_number + 1) {
            factorial[0] = factorial[1] = 1;
            inv_factorial[0] = inv_factorial[1] = 1;
            inv[1] = 1;
            for (int i = 2; i <= max_number; i++) {
                factorial[i] = (factorial[i - 1] * i) % mod;
                inv[i] = mod - inv[mod % i] * (mod / i) % mod;
                inv_factorial[i] = inv_factorial[i - 1] * inv[i] % mod;
            }
        }
        T calc(int n, int k) {
            if (n < k) return 0;
            if (n < 0 || k < 0) return 0;
            return factorial[n] * (inv_factorial[k] * inv_factorial[n - k] % mod) % mod;
        }
};

using ll = long long;

const ll MOD = 1e9 + 7;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    // This sample is Atcoder Beginners Contest 132 D
    ll N, K;
    cin >> N >> K;
    Combination<ll> comb(N, MOD);
    for (int i = 1; i <= K; i++) {
        ll k_div = comb.calc(K - 1, i - 1);
        ll all_div = comb.calc(N - K + 1, i);
        cout << (k_div * all_div) % MOD << endl;
    }
    return 0;
}