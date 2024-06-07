#include <random>
#include <set>

#include "util.h"

int probalistic_collision_method_discrete_logarithm(int g, int h, int p) {
    int n = 1;
    while (n * n < p - 1) {
        ++n;
    }
    n *= 1;

    std::uniform_int_distribution<std::mt19937::result_type> udist(0, p - 2);
    std::mt19937 rng;

    std::set<std::pair<int, int>> list1;
    while (list1.size() < 3 * n) {
        int y = udist(rng);
        int g_y = pow(g, y, p);
        list1.insert({g_y, y});
    }

    std::set<std::pair<int, int>> list2;
    while (list2.size() < 3 * n) {
        int z = udist(rng);
        int h_g_z = mul_mod(h, pow(g, z, p), p);
        list2.insert({h_g_z, z});
    }

    for (const auto &v: list1) {
        auto it = list2.lower_bound({v.first, 0});
        if (it != list2.end() && it->first == v.first) {
            return sub_mod(v.second, it->second, p - 1);
        }
    }
    
    // oops, we didn't find matching elements :-(
    // We could continue process, adding elements and finding them.
    while (true) {
        int y = udist(rng);
        int g_y = pow(g, y, p);
        list1.insert({g_y, y});

        auto it = list2.lower_bound({g_y, 0});
        if (it != list2.end() && it->first == g_y) {
            return sub_mod(y, it->second, p - 1);
        }

        int z = udist(rng);
        int h_g_z = mul_mod(h, pow(g, z, p), p);
        list2.insert({h_g_z, z});

        it = list1.lower_bound({h_g_z, 0});
        if (it != list1.end() && it->first == h_g_z) {
            return sub_mod(it->second, z, p - 1);
        }
    }
}
