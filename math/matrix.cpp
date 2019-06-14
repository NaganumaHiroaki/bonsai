#include<iostream>
// Need start
#include<vector>
// Need end
using namespace std;

template<typename T>
class Matrix {
    private:
        using array = vector<T>;
        using matrix = vector<array>;
        size_t row_size, column_size;
        matrix data;
    public:
        Matrix(size_t row, size_t column):data(row, array(column, T())) {
            row_size = row;
            column_size = column;
        }
        Matrix(matrix new_data):data(new_data){}

        size_t row() const {return row_size;}
        size_t col() const {return column_size;}

        array& operator[] (size_t idx) {
            return data[idx];
        }
        const array& operator[] (size_t idx) const {
            return data[idx];
        }
        const Matrix operator+ (const Matrix& X) const {
            Matrix res(row_size, column_size);
            for (int i = 0; i < (int)res.row(); i++) {
                for (int j = 0; j < (int)res.col(); j++) {
                    res[i][j] = data[i][j] + X[i][j];
                }
            }
            return res;
        }
        Matrix& operator+= (const Matrix& X) {
            for (int i = 0; i < (int)row_size; i++) {
                for (int j = 0; j < (int)column_size; j++) {
                    data[i][j] += X[i][j];
                }
            }
            return *this;
        }
        const Matrix operator- (const Matrix& X) const {
            Matrix res(row_size, column_size);
            for (int i = 0; i < (int)res.row(); i++) {
                for (int j = 0; j < (int)res.col(); j++) {
                    res[i][j] = data[i][j] - X[i][j];
                }
            }
            return res;
        }
        Matrix& operator-= (const Matrix& X) {
            for (int i = 0; i < (int)row_size; i++) {
                for (int j = 0; j < (int)column_size; j++) {
                    data[i][j] -= X[i][j];
                }
            }
            return *this;
        }
        const Matrix operator* (const Matrix& X) const {
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
        const Matrix operator* (T scalar) const {
            Matrix res(row_size, column_size);
            for (int i = 0; i < res.row(); i++) {
                for (int j = 0; j < res.col(); j++) {
                    res[i][j] = data[i][j] * scalar;
                }
            }
            return res;
        }
        Matrix& operator*= (T scalar) {
            for (int i = 0; i < (int)row_size; i++) {
                for (int j = 0; j < (int)column_size; j++) {
                    data[i][j] *= scalar;
                }
            }
            return *this;
        }
        const Matrix operator% (T mod) const {
            Matrix res(data);
            for (int i = 0; i < (int)res.row(); i++) {
                for (int j = 0; j < (int)res.col(); j++) {
                    res[i][j] %= mod;
                }
            }
            return res;
        }
        Matrix& operator%= (T mod) {
            for (int i = 0; i < (int)row_size; i++) {
                for (int j = 0; j < (int)column_size; j++) {
                    data[i][j] %= mod;
                }
            }
            return *this;
        }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    int r, c;
    cout << "Input m1 ->" << endl;
    cin >> r >> c;
    Matrix<int> m1(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> m1[i][j];
        }
    }
    cout << "Input mod ->" << endl;
    int mod;
    cin >> mod;
    m1 %= mod;
    cout << "result" << endl;
    for (int i = 0; i < m1.row(); i++) {
        for (int j = 0; j < m1.col(); j++) {
            cout << m1[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}