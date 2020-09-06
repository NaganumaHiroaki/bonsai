#include<numeric>
#include<vector>

class Osak {
private:
    std::vector<int> min_factor_;
public:
    Osak(int n) {
        min_factor_ = std::vector<int>(n);
        std::iota(min_factor_.begin(), min_factor_.end(), 0);
        for (int i = 2; i * i < n; ++i) {
            if (min_factor_[i] < i) {
                continue;
            }
            for (int j = i * i; j < n; ++j) {
                if (min_factor_[j] == j) {
                    min_factor_[j] = i;
                }
            }
        }
    }
    std::vector<int> factorize(int x) {
        std::vector<int> res;
        while (x > 1) {
            res.push_back(min_factor_[x]);
            x /= min_factor_[x];
        }
        return res;
    }
};