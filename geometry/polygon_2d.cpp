#include<iostream>
// Need start
#include<cmath>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<functional>
// Need end
using namespace std;

// Copy start
const double EPS = 1e-10;
const double PI = acos(-1.0);

double deg2rad(double degree) {
    return degree * PI / 180.0;
}

double rad2deg(double radian) {
    return radian * 180.0 / PI;
}

template<typename T>
class Polygon2D {
    private:
        T x_, y_;
        int idx_;
    public:
        Polygon2D() {}
        Polygon2D(T x, T y):x_(x), y_(y) {}
        Polygon2D(T x, T y, int idx):x_(x), y_(y), idx_(idx) {}  // for convex-full
        static T dot(const Polygon2D& p1, const Polygon2D& p2) {return p1.x_ * p2.x_ + p1.y_ * p2.y_;}
        static T cross(const Polygon2D& p1, const Polygon2D& p2) {return p1.x_ * p2.y_ - p1.y_ * p2.x_;}
        T norm() const {return dot(*this, *this);}
        T abs() const {return sqrt(this->norm());}
        Polygon2D rot(T radian) const {return Polygon2D(cos(radian) * x_ - sin(radian) * y_, sin(radian) * x_ + cos(radian) * y_, idx_);}
        Polygon2D rot90() const {return Polygon2D(-y_, x_, idx_);}
        static int ccw(const Polygon2D& p1, const Polygon2D& p2, const Polygon2D& p3) {
            if (cross(p2 - p1, p3 - p1) > EPS) return 1;    // p3 is left side
            if (cross(p2 - p1, p3 - p1) < -EPS) return -1;  // p3 is right side
            return 0;                                       // p3 is on the line
        }
        const Polygon2D operator+(const Polygon2D& p) const {Polygon2D<T> res = *this; res.x_ += p.x_; res.y_ += p.y_; return res;}
        const Polygon2D operator-(const Polygon2D& p) const {Polygon2D<T> res = *this; res.x_ -= p.x_; res.y_ -= p.y_; return res;}
        const Polygon2D operator*(const T val) const {Polygon2D<T> res = *this; res.x_ *= val; res.y_ *= val; return res;}
        friend const Polygon2D operator*(const T& val, const Polygon2D& p) {Polygon2D res = p; res.x_ *= val; res.y_ *= val; return res;}
        const Polygon2D operator/(const T val) const {Polygon2D res = *this; res.x_ /= val; res.y_ /= val; return res;}
        T getX() const {return x_;}
        T getY() const {return y_;}
        int getIdx() const {return idx_;}
        friend ostream& operator<<(ostream& stream, const Polygon2D& p) {stream << '(' << p.x_ << ',' << p.y_ << ')'; return stream;}
};

template<typename T>
class Line {
    private:
        Polygon2D<T> a_, b_;
    public:
        Line() {}
        Line(Polygon2D<T> a, Polygon2D<T> b):a_(a), b_(b) {}
        Polygon2D<T> getFirst() const {return a_;}
        Polygon2D<T> getSecond() const {return b_;}
};

template<typename T>
vector<Polygon2D<T>> crosspoints(const Line<T>& l1, const Line<T>& l2) {
    vector<Polygon2D<T>> res;
    T d = Polygon2D<T>::cross(l2.getSecond() - l2.getFirst(), l1.getSecond() - l1.getFirst());
    if (abs(d) < EPS) {
        return vector<Polygon2D<T>>();
    }
    res.push_back(l1.getFirst() + (l1.getSecond() - l1.getFirst()) * cross(l2.getSecond() - l2.getFirst(), l2.getSecond() - l1.getFirst() / d));
    return res;
}

template<typename T>
Polygon2D<T> getCircumCenter(const Polygon2D<T>& p1, const Polygon2D<T>& p2, const Polygon2D<T>& p3) {
    Line<T> p12((p1 + p2) / 2, (p1 + p2) / 2 + Polygon2D<T>::rot90(p1 - p2));
    Line<T> p23((p2 + p3) / 2, (p2 + p3) / 2 + Polygon2D<T>::rot90(p2 - p3));
    return crosspoints(p12, p23)[0];
}

// Graham's scan
template<typename T>
vector<Polygon2D<T>> convex_hull(vector<Polygon2D<T>> ps, int vertex_num) {
    sort(ps.begin(), ps.end(), [](const Polygon2D<T>& p, const Polygon2D<T>& q) {
        if (p.getX() != q.getX()) return p.getX() < q.getX();
        return p.getY() < q.getY();
    });
    int k = 0;
    vector<Polygon2D<T>> qs(vertex_num * 2);
    // bottom
    for (int i = 0; i < vertex_num; i++) {
        while (k > 1 && Polygon2D<T>::cross(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    // up
    for (int i = vertex_num - 2, t = k; i >= 0; i--) {
        while (k > t && Polygon2D<T>::cross(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    qs.resize(k - 1);
    return qs;
}
// Copy end

int main() {
    // This sample is AtCoder Grand Contest 21 B
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<Polygon2D<double>> ps(N);
    double x, y;
    for (int i = 0; i < N; ++i) {
        cin >> x >> y;
        ps[i] = Polygon2D<double>(x, y, i);
    }
    if (N == 2) {
        cout << fixed << setprecision(7);
        cout << 0.5 << endl;
        cout << 0.5 << endl;
        return 0;
    }
    vector<Polygon2D<double> > qs = convex_hull(ps, N);
    qs.push_back(qs[0]);
    qs.push_back(qs[1]);
    vector<double> ans(N, 0.0);
    for (int i = 0; i < (int)qs.size() - 2; i++) {
        Polygon2D<double> pr = qs[i] - qs[i + 1], pq = qs[i + 2] - qs[i + 1];
        double len_pr = pr.norm();
        double len_pq = pq.norm();
        ans[qs[i + 1].getIdx()] = (PI - acos(Polygon2D<double>::dot(pr, pq) / sqrt(len_pr * len_pq))) / (2 * PI);
    }
    cout << fixed << setprecision(7);
    for (int i = 0; i < N; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}