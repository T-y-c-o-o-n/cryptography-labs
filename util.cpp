#include <vector>

std::vector<int> divisors(int n) {
    std::vector<int> res;

    int k = 2;
    while (n > 1) {
        if (n % k == 0) {
            res.push_back(k);
            n /= k;
        } else {
            ++k;
        }
    }

    return res;
}

int add_mod(int a, int b, int mod) {
    return int((1ll * a + 1ll * b) % (1ll * mod));
}

int sub_mod(int a, int b, int mod) {
    return int((1ll * a - 1ll * b + 1ll * mod) % (1ll * mod));
}

int mul_mod(int a, int b, int mod) {
    return int((a * 1ll * b) % (1ll * mod));
}

int pow(int a, int n, int p) {
    int res = 1;

        while (n > 0) {
        if (n % 2 == 1) {
            res = int((res * 1ll * a) % (1ll * p));
        }
        a = int((a * 1ll * a) % (1ll * p));
        n >>= 1;
    }

    return res;
}

int gcd_extended(int a, int b, int & x, int & y, int p) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd_extended(b%a, a, x1, y1, p);
    x = sub_mod(y1, mul_mod(b / a, x1, p), p);
    y = x1;
    return d;
}
