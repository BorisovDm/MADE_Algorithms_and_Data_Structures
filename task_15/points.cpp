#include "points.h"


double get_random_uniform() {
    // U[0, 1]
    return (std::rand() % RAND_MODULE) / (RAND_MODULE - 1.);
}

std::vector<std::pair<double, double>> generate_2d_points(int n_points) {
    std::vector<std::pair<double, double>> points(n_points);

    for (int i = 0; i < n_points; ) {
        double x = 2 * get_random_uniform() - 1;
        double y = 2 * get_random_uniform() - 1;
        double s = std::pow(x, 2) +  std::pow(y, 2);

        if (0 < s && s <= 1) {
            double p = std::sqrt(-2 * std::log(s) / s);
            points[i] = {x * p, y * p};
            i++;
        }
    }

    return points;
}

double l2_distance(const std::pair<double, double>& point_1, const std::pair<double, double>& point_2) {
    return std::sqrt(std::pow(point_1.first - point_2.first, 2) + std::pow(point_1.second - point_2.second, 2));
}
