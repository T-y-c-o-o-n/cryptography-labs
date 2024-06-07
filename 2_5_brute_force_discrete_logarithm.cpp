#include <stdexcept>

#include "util.h"

int brute_force_discrete_logarithm(int g, int h, int p) {
    int degree = 0;
    int elem = 1;
    while (elem != h) {
        degree++;
        elem = mul_mod(elem, g, p);
        if (elem == 1) {
            throw std::runtime_error("no degree of g is equal to a");
        }
    }
    return degree;
}