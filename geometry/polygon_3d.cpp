#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class Polygon3D {
    private:
        T x, y, z;
    public:
        Polygon3D():x(0), y(0), z(0) {}
        Polygon3D(T _x, T _y, T _z):x(_x), y(_y), z(_z) {}
        static T dot(const Polygon3D<T>& p1, const Polygon3D<T>& p2) {
            return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
        }
        static Polygon3D<T> det(const Polygon3D<T>& p1, const Polygon3D<T>& p2) {
            T x3 = p1.y * p2.z - p1.z * p2.y;
            T y3 = p1.z * p2.x - p1.x * p2.z;
            T z3 = p1.x * p2.y - p1.y * p2.x;
            return Polygon3D(x3, y3, z3);
        }
        static T pow_dist(const Polygon3D<T>& p1) {
            return dot(p1, p1);
        }
        const Polygon3D<T> operator=(const Polygon3D<T>& p) {
            x = p.x;
            y = p.y;
            z = p.z;
            return *this;
        }
        const Polygon3D<T> operator+(const Polygon3D<T>& p) const {
            Polygon3D<T> res = *this;
            res.x += p.x;
            res.y += p.y;
            res.z += p.z;
            return res;
        }
        const Polygon3D<T> operator-(const Polygon3D<T>& p) const {
            Polygon3D<T> res = *this;
            res.x -= p.x;
            res.y -= p.y;
            res.z -= p.z;
            return res;
        }
        void show() {
            // for debug
            cout << '(' << x << ',' << y << ',' << z << ')' << endl;
        }
};

template<typename T>
bool line_and_sphere_intersect(const Polygon3D<T>& line_start, const Polygon3D<T>& line_end, const Polygon3D<T>& sphere_center, const T& radius) {
            // This function returns whether line-segment and sphere intersect or not.
            Polygon3D<T> v = line_end - line_start;
            Polygon3D<T> c = sphere_center - line_start;
            T vc_dot = Polygon3D<T>::dot(v, c);
            if (vc_dot <= 0) {
                return Polygon3D<T>::pow_dist(c) <= radius * radius;
            }
            else {
                if (vc_dot > Polygon3D<T>::pow_dist(v)) {
                    Polygon3D<T> start_to_center = sphere_center - line_start;
                    return Polygon3D<T>::pow_dist(start_to_center) <= radius * radius;
                }
                else {
                    T c_dist = Polygon3D<T>::pow_dist(c);
                    T v_dist = Polygon3D<T>::pow_dist(v);
                    return c_dist * v_dist - vc_dot * vc_dot <= radius * radius * v_dist;
                }
            }
        }

typedef long long ll;

int main() {
    // This sample is AOJ ICPC 2641 (Magic Bullet)
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    vector<Polygon3D<ll> > obj(N);
    vector<ll> R(N), L(N);
    vector<Polygon3D<ll> > red_obj(Q), blue_obj(Q);
    ll x, y, z;
    for (int i = 0; i < N; ++i) {
        cin >> x >> y >> z >> R[i] >> L[i];
        obj[i] = Polygon3D<ll>(x, y, z);
    }
    for (int i = 0; i < Q; ++i) {
        cin >> x >> y >> z;
        red_obj[i] = Polygon3D<ll>(x, y, z);
        cin >> x >> y >> z;
        blue_obj[i] = Polygon3D<ll>(x, y, z);
    }
    for (int i = 0; i < Q; ++i) {
        ll magic_sum = 0;
        for (int j = 0; j < N; ++j) {
            if (line_and_sphere_intersect<ll>(red_obj[i], blue_obj[i], obj[j], R[j])) {
                magic_sum += L[j];
            }
        }
        cout << magic_sum << endl;
    }
    return 0;
}