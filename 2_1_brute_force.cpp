#include <vector>
#include <stdexcept>

#include "util.h"

bool is_primitive(int p, int g) {
    std::vector<int> degrees = divisors(p - 1);

    for (int degree: degrees) {
        if (pow(g, degree, p) == 1) {
            return false;
        }
    }

    return true;
}

int brute_force(int p, int g, int a) {
    int degree = 0;
    int elem = 1;
    while (elem != a) {
        degree++;
        elem = (int((elem * 1ll * g) % (1ll * p)));
        if (elem == 1) {
            throw std::runtime_error("no degree of g is equal to a");
        }
    }
    return degree;
}