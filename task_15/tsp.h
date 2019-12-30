#pragma once

#include "points.h"

#include <algorithm>
#include <climits>
#include <vector>

double exact_solution(double** adjacency_matrix, const int size);
double approximate_solution(double** adjacency_matrix, const int size);
std::vector<int> find_eulerian_cycle(std::vector<std::vector<int>>& eulerian_graph);
