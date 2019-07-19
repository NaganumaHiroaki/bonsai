#include<iostream>
// Need start
#include<cassert>
#include<vector>
#include<queue>
#include<functional>
// Need end
using namespace std;
typedef long long ll;

template <typename T>
class SlideMinimum {
    private:
        deque<int> dq;
        vector<T> array;
        int window_size;
        function<bool(T, T)> comp;
        int now_pos;
    public:
        SlideMinimum(const vector<T>& _array, int _window_size, function<bool(T, T)> _comp, int start_pos):
        array(_array), window_size(_window_size), comp(_comp), now_pos(start_pos) {}
        void slide() {
            assert(now_pos < (int)array.size());
            while (!dq.empty() && comp(array[dq.back()], array[now_pos])) {
                dq.pop_back();
            }
            dq.push_back(now_pos);
            if (dq.front() == now_pos - window_size) {
                dq.pop_front();
            }
            now_pos++;
        }
        T get_min() {
            return array[dq.front()];
        }
};

/*
If you want use this class for get minimum,
comp-function is defined as `[](T a, T b) {return a > b;}`.
If you want use this class for SlideMaximum,
comp-function is defined as `[](T a, T b) {return a < b;}`.
*/

ll g[10101010];

int main() {
    // This sample is Codeforces Round #574 E
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N, M, A, B;
    ll X, Y, Z;
    cin >> N >> M >> A >> B >> g[0] >> X >> Y >> Z;
    vector<vector<ll> > grid(N + 1, vector<ll>(M + 1));
    for (int i = 1; i <= N * M; i++) {
        g[i] = (g[i - 1] * X + Y) % Z;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            grid[i][j] = g[(i - 1) * M + j - 1];
        }
    }
    vector<vector<ll> > mn(N - A + 2, vector<ll>(M + 1));
    for (int i = 1; i <= M; i++) {
        vector<ll> now_array(N + 1);
        for (int j = 1; j <= N; j++) {
            now_array[j] = grid[j][i];
        }
        SlideMinimum<ll> sm(now_array, A, [](ll a, ll b){return a > b;}, 1);
        for (int j = 0; j < A - 1; j++) sm.slide();
        for (int j = A; j <= N; j++) {
            sm.slide();
            mn[j - A + 1][i] = sm.get_min();
        }
    }
    ll ans = 0;
    for (int i = 1; i <= N - A + 1; i++) {
        vector<ll> now_array(M + 1);
        for (int j = 1; j <= M; j++) {
            now_array[j] = mn[i][j];
        }
        SlideMinimum<ll> sm(now_array, B, [](ll a, ll b){return a > b;}, 1);
        for (int j = 0; j < B - 1; j++) sm.slide();
        for (int j = B; j <= M; j++) {
            sm.slide();
            ans += sm.get_min();
        }
    }
    cout << ans << endl;
    return 0;
}