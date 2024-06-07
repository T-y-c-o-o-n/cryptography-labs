#include <stdexcept>

#include "util.h"

int pollards_pi_method_discrete_logarithm(int g, int h, int p) {
    int p_1_3 = p / 3, p_2_3 = p * 2 / 3;

    auto f = [g, h, p_1_3, p_2_3](int &x, int &g_degree, int &h_degree) {
        if (x < p_1_3) {
            ++g_degree;
            x *= g;
        } else if (x < p_2_3) {
            g_degree *= 2;
            h_degree *= 2;
            x *= x;
        } else {
            ++h_degree;
            x *= h;
        }
    };

    int a = 1, b = 1;
    int i = 0, j = 0, k = 0, l = 0;
    do {
        f(a, i, j);
        f(b, k, l);
    } while (a != b);

    // g^i * h^j = g^k * h^l
    // g^(i-k) = h^(l-j)
    // g^(i-k) = g^(ans*(l-j))
    // (i-k) = ans * (l-j) (mod p-1)

    int s, unused;
    int d = gcd_extended(l - j, p - 1, s, unused);

    // (i-k) * s = ans * d (mod p-1)

    int w = (i - k) * s;

    if (w % d != 0) {
        throw std::runtime_error("inner property violation: w not divided by d");
    }

    int candidate = w / d;
    for (int t = 0; t < d; ++t) {
        if (h == pow(g, candidate, p)) {
            return candidate;
        }
        candidate += (p - 1) / d;
    }

    throw std::runtime_error("inner property violation: no solutions found among {w/d + k * (p-1)/d  |  k = 0, 1, 2 ..., d-1 }");
}