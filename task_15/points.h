#pragma once

#include <cmath>
#include <cstdlib>
#include <vector>

#define RAND_MODULE 10000

double get_random_uniform();
std::vector<std::pair<double, double>> generate_2d_points(int n_points);
double l2_distance(const std::pair<double, double>& point_1, const std::pair<double, double>& point_2);
