#include <iostream>
#include <functional>
#include <chrono>
#include <random>

bool is_primitive(int p, int g);

long bench_log(std::function<int(int, int, int)> log_func, int g, std::vector<int> &hs, int p) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int h: hs) {
        log_func(g, h, p);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return duration;
}

int brute_force_discrete_logarithm(int g, int h, int p);

int babystep_giantstep_discrete_logarithm(int g, int h, int p);

int probalistic_collision_method_discrete_logarithm(int g, int h, int p);

int pollards_pi_method_discrete_logarithm(int g, int h, int p);

void check_correctness(int g, int h, int p) {
    int res1 = brute_force_discrete_logarithm(g, h, p);
    int res2 = babystep_giantstep_discrete_logarithm(g, h, p);
    int res3 = probalistic_collision_method_discrete_logarithm(g, h, p);
    int res4 = pollards_pi_method_discrete_logarithm(g, h, p);
    if (res1 != res2 || res2 != res3 || res3 != res4) {
        std::cout << "different results for discrete logarithm with g=" << g << ", h=" << h << " and p=" << p << ":\n";
        std::cout << "brute_force -> " << res1 << "\n";
        std::cout << "babystep_giantstep -> " << res2 << "\n";
        std::cout << "probalistic_collision -> " << res3 << "\n";
        std::cout << "pollards_pi_method -> " << res4 << "\n";
    }
}

int main() {
    int p = 1000000007;

    int g;
    for (g = 1; g < p; ++g) {
        if (is_primitive(p, g)) {
            break;
        }
    }

    std::uniform_int_distribution<int> udist(2, p - 1);
    std::mt19937 rng;

    std::vector<int> inputs;
    for (int i = 0; i < 1000; ++i) {
        int h = udist(rng);
        inputs.push_back(h);
        check_correctness(g, h, p);
    }

    printf("brute_force %ld ns", bench_log(brute_force_discrete_logarithm, g, inputs, p));
    printf("babystep_giantstep %ld ns", bench_log(babystep_giantstep_discrete_logarithm, g, inputs, p));
    printf("probalistic_collision_method %ld ns",
           bench_log(probalistic_collision_method_discrete_logarithm, g, inputs, p));
    printf("pollards_pi_method %ld ns", bench_log(pollards_pi_method_discrete_logarithm, g, inputs, p));


    return 0;
}
