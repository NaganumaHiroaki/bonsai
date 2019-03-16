#include<iostream>
using namespace std;

const double EPS = 1e-10;

// two-dimension vector class
struct P {
    double x, y;
    P() {}
    P(double x, double y) : x(x), y(y) {
    }
    P operator+ (P p) {
        return P(x + p.x, y + p.y);
    }
    P operator- (P p) {
        return P(x - p.x, y - p.y);
    }
    P operator* (double d) {
        return P(x * d, y * d);
    }
    double dot(P p) {
        return x * p.x + y * p.y;
    }
    double det(P p) {
        return x * p.y + y * p.x;
    }
};

int main() {
    P pos1(1, 2), pos2(3, 4);
    // add
    cout << '(' << (pos1 + pos2).x << ',' << (pos1 + pos2).y << ')' << endl;
    // minus
    cout << '(' << (pos1 - pos2).x << ',' << (pos1 - pos2).y << ')' << endl;
    // multi
    cout << '(' << (pos1 * 2).x << ',' << (pos1 * 2).y << ')' << endl;
    // dot
    cout << pos1.dot(pos2) << endl;
    // det
    cout << pos1.det(pos2) << endl;
    return 0;
}