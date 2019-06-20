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
        size_t row_size, column_size;
        matrix data;
    public:
        Matrix(size_t _row_size, size_t _column_size):
        data(_row_size, array(_column_size, T())), row_size(_row_size), column_size(_column_size) {}
        Matrix(const Matrix<T>& matrix):
        data(matrix.data), row_size(matrix.row_size), column_size(matrix.column_size){}

        size_t row() const {return row_size;}
        size_t col() const {return column_size;}

        array& operator[](size_t idx) {
            return data[idx];
        }
        const array& operator[](size_t idx) const {
            return data[idx];
        }
        const Matrix operator+(const Matrix& X) const {
            Matrix res(row_size, column_size);
            for (int i = 0; i < (int)res.row(); i++) {
                for (int j = 0; j < (int)res.col(); j++) {
                    res[i][j] = data[i][j] + X[i][j];
                }
            }
            return res;
        }
        Matrix& operator+=(const Matrix& X) {
            for (int i = 0; i < (int)row_size; i++) {
                for (int j = 0; j < (int)column_size; j++) {
                    data[i][j] += X[i][j];
                }
            }
            return *this;
        }
        const Matrix operator-(const Matrix& X) const {
            Matrix res(row_size, column_size);
            for (int i = 0; i < (int)res.row(); i++) {
                for (int j = 0; j < (int)res.col(); j++) {
                    res[i][j] = data[i][j] - X[i][j];
                }
            }
            return res;
        }
        Matrix& operator-=(const Matrix& X) {
            for (int i = 0; i < (int)row_size; i++) {
                for (int j = 0; j < (int)column_size; j++) {
                    data[i][j] -= X[i][j];
                }
            }
            return *this;
        }
        const Matrix operator*(const Matrix& X) const {
            size_t new_row = row_size, new_column = X.col();
            Matrix res(new_row, new_column);
            for (int i = 0; i < (int)res.row(); i++) {
                for (int j = 0; j < (int)res.col(); j++) {
                    for (int k = 0; k < (int)column_size; k++) {
                        res[i][j] += data[i][k] * X[k][j];
                    }
                }
            }
            return res;
        }
        const Matrix operator*(T scalar) const {
            Matrix res(row_size, column_size);
            for (int i = 0; i < res.row(); i++) {
                for (int j = 0; j < res.col(); j++) {
                    res[i][j] = data[i][j] * scalar;
                }
            }
            return res;
        }
        Matrix& operator*=(T scalar) {
            for (int i = 0; i < (int)row_size; i++) {
                for (int j = 0; j < (int)column_size; j++) {
                    data[i][j] *= scalar;
                }
            }
            return *this;
        }
        const Matrix operator%(T mod) const {
            Matrix res(*this);
            for (int i = 0; i < (int)res.row(); i++) {
                for (int j = 0; j < (int)res.col(); j++) {
                    res[i][j] %= mod;
                }
            }
            return res;
        }
        Matrix& operator%=(T mod) {
            for (int i = 0; i < (int)row_size; i++) {
                for (int j = 0; j < (int)column_size; j++) {
                    data[i][j] %= mod;
                }
            }
            return *this;
        }

        static Matrix identity(size_t row, size_t col) {
            Matrix<T> res(row, col);
            for (int i = 0; i < (int)res.row(); i++) {
                res[i][i] = 1;
            }
            return res;
        }
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