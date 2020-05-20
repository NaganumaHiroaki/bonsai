#include<iostream>
// Need start
#include<vector>
// Need end
using namespace std;
typedef long long ll;

// Copy start
template<typename T>
class Matrix {
private:
    using array = vector<T>;
    using matrix = vector<array>;
    matrix data_;
public:
    Matrix() {}
    Matrix(size_t row, size_t col):data_(row, array(col)) {}
    Matrix(const Matrix<T>& mat):data_(mat.data_) {}
    size_t row() const {return data_.size();}
    size_t col() const {return data_.front().size();}
    array& operator[](int idx) {return data_[idx];}
    const array& operator[](int idx) const {return data_[idx];}
    Matrix& operator+=(const Matrix& mat) {for (int i = 0; i < (int)data_.size(); i++) for (int j = 0; j < (int)data_[i].size(); j++) {data_[i][j] += mat[i][j];} return *this;}
    Matrix& operator-=(const Matrix& mat) {for (int i = 0; i < (int)data_.size(); i++) for (int j = 0; j < (int)data_[i].size(); j++) {data_[i][j] -= mat[i][j];} return *this;}
    Matrix operator*(const Matrix& mat) const {size_t row = data_.size(); size_t col = mat.col(); Matrix res(row, col); for (int i = 0; i < (int)res.row(); i++) for (int j = 0; j < (int)res.col(); j++) for (int k = 0; k < (int)data_.front().size(); k++) {res[i][j] += data_[i][k] * mat[k][j];} return res;}
    Matrix& operator*=(T scalar) {for (int i = 0; i < (int)data_.size(); i++) for (int j = 0; j < (int)data_[i].size(); j++) {data_[i][j] *= scalar;} return *this;}
    Matrix& operator%=(T mod) {for (int i = 0; i < (int)data_.size(); i++) for (int j = 0; j < (int)data_[i].size(); j++) {data_[i][j] %= mod;} return *this;}
    const Matrix operator+(const Matrix& mat) const {return Matrix(*this) += mat;}
    const Matrix operator-(const Matrix& mat) const {return Matrix(*this) -= mat;}
    const Matrix operator*(T scalar) const {return Matrix(*this) *= scalar;}
    const Matrix operator%(T mod) const {return Matrix(*this) %= mod;}
    static Matrix identity(size_t row, size_t col) {Matrix<T> res(row, col);for (int i = 0; i < (int)res.row(); i++) {res[i][i] = 1;} return res;}
};
// Copy end


ll MOD;

ll lower_num(ll a, ll d, ll x) {
    if (x <= a) return a;
    return (x - a + d - 1) / d * d + a;
}

Matrix<ll> calc_pow(Matrix<ll> x, ll y) {
    Matrix<ll> z = Matrix<ll>::identity(x.row(), x.col());
    while (y > 0) {
        if (y & 1) {
            z = z * x;
            z %= MOD;
        }
        x = x * x;
        x %= MOD;
        y /= 2;
    }
    return z;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    // This sample is Atcoder Beginners Contest 129 F
    ll L, A, B;
    cin >> L >> A >> B >> MOD;
    Matrix<ll> X(1, 3), Y(3, 3);
    // X
    X[0][0] = 0;
    X[0][1] = A;
    X[0][2] = 1;
    // Y
    Y[1][0] = 1;
    Y[1][1] = 1;
    Y[2][2] = 1;
    Y[2][1] = B;
    ll pow_num = 1;
    for (int d = 1; d <= 18; d++) {
        if (L == 0) break;
        Y[0][0] = (pow_num * 10) % MOD;
        ll high = lower_num(A, B, pow_num * 10);
        ll low = lower_num(A, B, pow_num);
        ll Cd = min((high - low) / B, L);
        L -= Cd;
        Matrix<ll> Z = calc_pow(Y, Cd);
        X = (X * Z) % MOD;
        pow_num *= 10;
    }
    cout << X[0][0] << endl;
    return 0;
}