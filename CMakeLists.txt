cmake_minimum_required(VERSION 3.26)
project(cryptography)

set(CMAKE_CXX_STANDARD 20)

add_executable(cryptography main.cpp
        2_1_brute_force.cpp
        2_5_brute_force_discrete_logarithm.cpp
        2_6_babystep_giantstep.cpp
        2_7_probalistic_collision_method.cpp
        2_8_pollards_pi_method.cpp
        util.cpp
        util.h)
