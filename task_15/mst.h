#pragma once

#include <algorithm>
#include <cassert>
#include <climits>
#include <numeric>
#include <set>
#include <tuple>
#include <vector>

std::vector<std::tuple<int, int, double>> get_mst(double** adjacency_matrix, const int graph_size);
