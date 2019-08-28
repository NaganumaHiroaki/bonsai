// Need start
#include<iostream>
// Need end
#include<vector>
using namespace std;

// Copy start
template<typename T, long long modulus=1000000007>
class ModInt {
    private:
        T value_;
    public:
        ModInt() {}
        ModInt(const T& _value) {
            value_ = _value % modulus;
        }
        ModInt(const ModInt& x) {
            value_ = x.value_;
        }
        T getValue() const {
            return value_;
        }
        ModInt& operator=(const ModInt& x) {
            value_ = x.value_;
            return *this;
        }
        ModInt& operator+=(const ModInt& x)  {
            value_ += x.value_;
            if (value_ >= modulus) value_ -= modulus;
            return *this;
        }
        ModInt& operator-=(const ModInt& x) {
            if (value_ < x.value_) value_ += modulus;
            value_ -= x.value_;
            return *this;
        }
        ModInt& operator*=(const ModInt& x) {
            value_ = (value_ * x.value_) % modulus;
            return *this;
        }
        ModInt& operator/=(const ModInt& x) {
            T now_value = x.value_;
            long long cnt = modulus - 2;
            while (cnt > 0) {
                if (cnt & 1) {
                    value_ = (value_ * now_value) % modulus;
                }
                now_value = (now_value * now_value) % modulus;
                cnt /= 2;
            }
            return *this;
        }
        ModInt operator+(const ModInt& x) const {
            return ModInt(*this) += x;
        }
        ModInt operator-(const ModInt& x) const {
            return ModInt(*this) -= x;
        }
        ModInt operator*(const ModInt& x) const {
            return ModInt(*this) *= x;
        }
        ModInt operator/(const ModInt& x) const {
            return ModInt(*this) /= x;
        }
        ModInt operator++(int) {
            ModInt tmp(*this);
            value_ = (value_ + 1 == modulus ? 0 : value_ + 1);
            return tmp;
        }
        ModInt operator--(int) {
            ModInt tmp(*this);
            value_ = (value_ - 1 < 0 ? modulus - 1 : value_ - 1);
            return tmp;
        }
        friend std::istream& operator>>(std::istream& stream, ModInt& x) {
            stream >> x.value_;
            x.value_ %= modulus;
            return stream;
        }
        friend std::ostream& operator<<(std::ostream& stream, const ModInt& x) {
            stream << x.value_;
            return stream;
        }
};
// Copy end

using ll = long long;
using mint = ModInt<ll>;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    // This sample is AtCoder Japan Saikyo Contest 2019 qualification round B
    int N;
    mint K;
    cin >> N >> K;
    vector<ll> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    mint ans = 0;
    mint one(1), two(2);
    for (int i = 0; i < N; ++i) {
        mint prev(0), tail(0);
        for (int j = 0; j < i; ++j) {
            if (A[i] < A[j]) prev++;
        }
        for (int j = i; j < N; ++j) {
            if (A[i] < A[j]) tail++;
        }
        mint sum = K * (two * prev + (K - one) * (prev + tail)) / two;
        ans += sum;
    }
    cout << ans << endl;
    return 0;
}