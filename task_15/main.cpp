#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#include "points.h"
#include "tsp.h"

#define N_REPEATS 150


int main() {
    std::srand(std::time(nullptr));
    std::ofstream output("results.txt");
    output << "n_points" << " " << "mean_value" << " " << "std_value" << "\n";

    for (int n_points = 3; n_points < 11; n_points++) {
        std::vector<double> path_length_relation(N_REPEATS);

        for (int repeat_number = 0; repeat_number < N_REPEATS; repeat_number++) {
            std::vector<std::pair<double, double>> points = generate_2d_points(n_points);

            double** adjacency_matrix = new double *[n_points];
            for (int i = 0; i < n_points; i++) {
                adjacency_matrix[i] = new double[n_points];
            }

            for (int i = 0; i < n_points; i++) {
                for (int j = i; j < n_points; j++) {
                    double distance = l2_distance(points[i], points[j]);
                    adjacency_matrix[i][j] = distance;
                    adjacency_matrix[j][i] = distance;
                }
            }

            double exact_solution_length = exact_solution(adjacency_matrix, n_points);
            double approximate_solution_length = approximate_solution(adjacency_matrix, n_points);
            path_length_relation[repeat_number] = approximate_solution_length / exact_solution_length;

            for (int i = 0; i < n_points; i++) {
                delete[] adjacency_matrix[i];
            }
            delete[] adjacency_matrix;
        }

        double sum_value = 0;
        double sum_squares_value = 0;

        for (const auto x : path_length_relation) {
            sum_value += x;
            sum_squares_value += std::pow(x, 2);
        }

        double mean_value = sum_value / N_REPEATS;
        double std_value = std::sqrt(sum_squares_value / N_REPEATS - std::pow(mean_value, 2));
        output << n_points << " " << mean_value << " " << std_value << "\n";
    }

    return 0;
}
