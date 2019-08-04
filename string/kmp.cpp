#include<iostream>
#include<string>
// Need start
#include<cassert>
#include<vector>
// Need end
using namespace std;

// Copy start
template<typename ITERATOR>
class KMP {
    private:
        ITERATOR pattern;  // iterator
        vector<int> shift_table;
    public:
        KMP(ITERATOR _pattern):pattern(_pattern) {
            // calculate tagged border
            vector<int> tagged_border(pattern.size() + 1);
            tagged_border[0] = -1;  // -1 means that there is no border
            int prev_border = -1;
            for (int i = 0; i < pattern.size(); ++i) {
                while (prev_border >= 0 && pattern[prev_border] != pattern[i]) {
                    prev_border = tagged_border[prev_border];
                }
                prev_border++;
                if (i + 1 < pattern.size() && pattern[i + 1] == pattern[prev_border]) {
                    tagged_border[i + 1] = tagged_border[prev_border];
                }
                else tagged_border[i + 1] = prev_border;
            }
            shift_table = tagged_border;
        }
        vector<int> get_shift_table() {
            return shift_table;
        }
        vector<int> search(ITERATOR target) {
            assert(target.size() >= pattern.size());
            // return matching position
            vector<int> res;
            int target_size = target.size(), pattern_size = pattern.size();
            int target_ptr = 0, pattern_ptr = 0;
            while (target_ptr < target_size) {
                if (target[target_ptr] == pattern[pattern_ptr]) {
                    target_ptr++;
                    pattern_ptr++;
                }
                else {
                    if (pattern_ptr == 0) target_ptr++;
                    else {
                        if (shift_table[pattern_ptr] < 0) {
                            pattern_ptr = 0;
                        }
                        else pattern_ptr = shift_table[pattern_ptr];
                    }
                }
                if (pattern_ptr == pattern_size) {
                    res.push_back(target_ptr - pattern_ptr);
                    if (shift_table[pattern_ptr] < 0) {
                        pattern_ptr = 0;
                    }
                    else pattern_ptr = shift_table[pattern_ptr];
                }
            }
            return res;
        }
};

int N, M;

const int MAX_LEN = 2020202;

bool is_ok[MAX_LEN], is_visited[MAX_LEN];
int period[MAX_LEN];

void dfs(int idx) {
    is_visited[idx] = true;
    period[idx] = -1;
    int next_idx = (idx + M) % N;
    if (!is_ok[next_idx]) {
        period[idx] = 1;
        return;
    }
    if (is_visited[next_idx]) {
        if (period[next_idx] < 0) {
            period[idx] = -1;
            return;
        }
        else {
            period[idx] = period[next_idx] + 1;
            return;
        }
    }
    dfs(next_idx);
    if (period[next_idx] >= 0) period[idx] = period[next_idx] + 1;
}
// Copy end

int main() {
    // This sample is Atcode Beginners Contest 135 F
    cin.tie(0);
    ios::sync_with_stdio(false);
    string S, T;
    cin >> S >> T;
    M = T.size();
    string SS = S;
    while (SS.size() < T.size()) {
        SS += S;
    }
    N = SS.size();
    KMP<string> kmp(T);
    vector<int> result = kmp.search(SS + SS);
    for (int i = 0; i < result.size(); ++i) {
        is_ok[result[i]] = true;
    }
    for (int i = 0; i < N; ++i) {
        if (is_ok[i] && !is_visited[i]) dfs(i);
    }
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (period[i] < 0) {
            cout << -1 << endl;
            return 0;
        }
        ans = max(period[i], ans);
    }
    cout << ans << endl;
    return 0;
}