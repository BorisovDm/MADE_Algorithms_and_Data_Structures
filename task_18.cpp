/*
 * Задача 18. Построение выпуклой оболочки (5 баллов)
 * Вариант 2. С помощью алгоритма Джарвиса.
 *
 * Дано множество точек на плоскости (x, y).
 * Постройте выпуклую оболочку этого множества и вычислите ее периметр.
 * Обратите внимание: три и более точки из множества могут лежать на одной прямой.
 *
 * Формат входного файла
 * Количество точек, далее на каждой строке координаты точек x, y.
 * Общее количество точек не превосходит 100000.
 * Координаты точек - числа с плавающей точкой в диапазоне [-1000, 1000].
 *
 * Формат выходного файла
 * Выведите периметр выпуклой оболочки.
 */


#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <unordered_set>


const double EPS = 1e-15;


double squared_l2_norm(const std::pair<double, double>& point) {
    return std::pow(point.first, 2) + std::pow(point.second, 2);
}

double l2_distance(const std::pair<double, double>& point_1, const std::pair<double, double>& point_2) {
    return std::sqrt(std::pow(point_1.first - point_2.first, 2) + std::pow(point_1.second - point_2.second, 2));
}

int vector_product_sign(const std::pair<double, double>& vector_1, const std::pair<double, double>& vector_2) {
    const double vector_product_value = vector_1.first * vector_2.second - vector_1.second * vector_2.first;
    if (std::abs(vector_product_value) < EPS) {
        return 0;
    } else {
        return vector_product_value > 0 ? 1 : -1;
    }
}

std::vector<int> convex_hull_jarvis(const std::vector<std::pair<double, double>>& points) {
    std::vector<bool> is_used(points.size(), false);
    std::vector<int> convex_hull_indexes;

    int starter_point_idx = 0;
    for (int i = 1; i < points.size(); i++) {
        if (points[i].second < points[starter_point_idx].second
            || (points[i].second == points[starter_point_idx].second
                && points[i].first > points[starter_point_idx].first)) {
            starter_point_idx = i;
        }
    }
    convex_hull_indexes.push_back(starter_point_idx);

    while (!is_used[convex_hull_indexes.front()]) {
        int next_best_point_idx = convex_hull_indexes.front();
        for (int temp_point_idx = 0; temp_point_idx < points.size(); temp_point_idx++) {
            if (is_used[temp_point_idx] || temp_point_idx == convex_hull_indexes.front()) {
                continue;
            }

            const std::pair<double, double> vector_1 = {
                    points[temp_point_idx].first - points[convex_hull_indexes.back()].first,
                    points[temp_point_idx].second - points[convex_hull_indexes.back()].second};

            const std::pair<double, double> vector_2 = {
                    points[next_best_point_idx].first - points[convex_hull_indexes.back()].first,
                    points[next_best_point_idx].second - points[convex_hull_indexes.back()].second};

            const double vector_product_sign_value = vector_product_sign(vector_1, vector_2);
            if (vector_product_sign_value == 1 || (vector_product_sign_value == 0 && squared_l2_norm(vector_1) > squared_l2_norm(vector_2))) {
                next_best_point_idx = temp_point_idx;
            }
        }

        convex_hull_indexes.push_back(next_best_point_idx);
        is_used[next_best_point_idx] = true;
    }

    return convex_hull_indexes;
}

int main() {
    int n_points;
    std::cin >> n_points;

    std::vector<std::pair<double, double>> points(n_points);
    for (int i = 0; i < n_points; i++) {
        double x, y;
        std::cin >> x >> y;
        points[i] = {x, y};
    }

    std::vector<int> convex_hull_indexes = convex_hull_jarvis(points);
    double convex_hull_perimeter = 0;
    for (int i = 0; i < convex_hull_indexes.size() - 1; i++) {
        convex_hull_perimeter += l2_distance(points[convex_hull_indexes[i]], points[convex_hull_indexes[i + 1]]);
    }

    std::cout << std::setprecision(15) << convex_hull_perimeter << std::endl;
    return 0;
}
