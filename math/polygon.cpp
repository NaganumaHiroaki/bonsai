#include<iostream>
// Need start
#include<vector>
#include<algorithm>
// Need end
using namespace std;

// Copy start
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
        return x * p.y - y * p.x;
    }
};

bool cmp_x(const P& p, const P& q) {
    if (p.x != q.x) return p.x < q.x;
    return p.y < q.y;
}

// Graham's scan
vector<P> convex_hull(vector<P> ps, int vertex_num) {
    sort(ps.begin(), ps.end(), cmp_x);
    int k = 0;
    vector<P> qs(vertex_num * 2);
    // bottom
    for (int i = 0; i < vertex_num; i++) {
        while (k > 1 && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    // up
    for (int i = vertex_num - 2, t = k; i >= 0; i--) {
        while (k > t && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    qs.resize(k - 1);
    return qs;
}
// Copy end

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