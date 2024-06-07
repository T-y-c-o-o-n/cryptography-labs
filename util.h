#pragma once

#include <vector>

std::vector<int> divisors(int n);

int add_mod(int a, int b, int mod);

int sub_mod(int a, int b, int mod);

int mul_mod(int a, int b, int mod);

int pow(int a, int n, int p);

int gcd_extended(int a, int b, int & x, int & y);
