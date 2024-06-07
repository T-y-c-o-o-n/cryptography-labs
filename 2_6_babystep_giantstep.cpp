#include <vector>
#include <stdexcept>

#include "util.h"

// g is primitive element, so order(g) = p - 1
int babystep_giantstep_discrete_logarithm(int g, int h, int p) {
    int n = 1;
    while (n * n <= p - 1) {
        ++n;
    }

    std::vector<std::pair<int, int>> babies;
    std::vector<int> giants;
    babies.reserve(n + 1);
    giants.reserve(n + 1);

    int g_degree = 1;
    for (int i = 0; i <= n; ++i) {
        babies.emplace_back(g_degree, i);
        g_degree = mul_mod(g_degree, g, p);
    }

    int g_neg_n = pow(g, p - 1 - n, p);

    int g_neg_n_degree = 1;
    for (int i = 0; i <= n; ++i) {
        giants.push_back(mul_mod(g_neg_n_degree, h, p));
        g_neg_n_degree = mul_mod(g_neg_n_degree, g_neg_n, p);
    }

    std::sort(babies.begin(), babies.end());

    for (int j = 0; j < giants.size(); ++j) {
        std::pair<int, int> elem = {giants[j], 0};
        auto it = std::lower_bound(babies.begin(), babies.end(), elem);
        if (it != babies.end() && it->first == elem.first) {
            int i = it->second;
            return add_mod(i, mul_mod(j, n, p), p);
        }
    }

    throw std::runtime_error("inner invariant violation: there is no equal giant and baby");
}
