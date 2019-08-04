#include<iostream>
#include<string>
// Need start
#include<cassert>
#include<vector>
// Need end
using namespace std;

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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    string ptn;
    cin >> ptn;
    KMP<string> kmp(ptn);
    string text;
    cin >> text;
    vector<int> match_pos = kmp.search(text);
    vector<char> mark(text.size(), '.');
    for (int i = 0; i < match_pos.size(); ++i) {
        mark[match_pos[i]] = '*';
    }
    cout << endl;
    cout << "---KMP matching result---" << endl;
    cout << text << endl;
    for (int i = 0; i < text.size(); ++i) {
        cout << mark[i];
    }
    cout << endl;
    cout << "-------------------------" << endl;
    cout << endl;
    vector<int> naive_pos;
    for (int i = 0; i < text.size() - ptn.size() + 1; ++i) {
        bool is_ok = true;
        for (int j = 0; j < ptn.size(); ++j) {
            if (text[i + j] != ptn[j]) {
                is_ok = false;
                break;
            }
        }
        if (is_ok) naive_pos.push_back(i);
    }
    if (naive_pos.size() != match_pos.size()) {
        cout << "mistake size..." << endl;
        return 0;
    }
    for (int i = 0; i < naive_pos.size(); ++i) {
        if (naive_pos[i] != match_pos[i]) {
            cout << "mistake..." << endl;
            return 0;
        }
    }
    cout << "OK" << endl;
    return 0;
}