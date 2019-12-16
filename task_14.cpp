/*
 * Задача 14_1. MST с помощью алгоритма Прима (5 баллов)
 *
 * Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе.
 *
 * Формат ввода:
 * Первая строка содержит два натуральных числа n и m — количество вершин и ребер графа соответственно
 *  (1 <= n <= 20000, 0 <= m <= 100000).
 * Следующие m строк содержат описание ребер по одному на строке.
 * Ребро номер i описывается тремя натуральными числами b_i, e_i и w_i — номера концов ребра и его вес соответственно
 *  (1 <= b_i, e_i <= n, 0 <= w_i <= 100000).
 *
 * Формат вывода:
 * Выведите единственное целое число - вес минимального остовного дерева.
 */


#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>


int get_mst_weight(const std::vector<std::vector<std::pair<int, int>>>& graph) {
    std::set<std::pair<int, int>> priority_set;
    std::vector<bool> is_in_mst(graph.size(), false);
    std::vector<int> min_edge_weight(graph.size(), INT_MAX);

    priority_set.insert({0, 0});
    min_edge_weight[0] = 0;

    while (!priority_set.empty()) {
        int next_mst_vertex = priority_set.begin()->second;
        is_in_mst[next_mst_vertex] = true;
        priority_set.erase(priority_set.begin());

        for (const auto& [vertex, edge_weight] : graph[next_mst_vertex]) {
            if (!is_in_mst[vertex] && min_edge_weight[vertex] > edge_weight) {
                priority_set.erase({min_edge_weight[vertex], vertex});
                min_edge_weight[vertex] = edge_weight;
                priority_set.insert({min_edge_weight[vertex], vertex});
            }
        }
    }

    assert(std::count(min_edge_weight.begin(), min_edge_weight.end(), INT_MAX) == 0);
    return std::accumulate(min_edge_weight.begin(), min_edge_weight.end(), 0);
}

int main() {
    int n_vertices, n_edges;
    std::cin >> n_vertices >> n_edges;
    std::vector<std::vector<std::pair<int, int>>> graph(n_vertices);

    int b, e, w;
    for (int i = 0; i < n_edges; i++) {
        std::cin >> b >> e >> w;
        b--;
        e--;
        graph[b].push_back({e, w});
        graph[e].push_back({b, w});
    }

    std::cout << get_mst_weight(graph) << std::endl;
    return 0;
}
