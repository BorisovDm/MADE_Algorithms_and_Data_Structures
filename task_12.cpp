/*
 * Задача 12. Мосты (5 баллов)
 *
 * Ребро неориентированного графа называется мостом,
 * если удаление этого ребра из графа увеличивает число компонент связности.
 * Дан неориентированный граф, требуется найти в нем все мосты.
 *
 * Ввод: Первая строка входного файла содержит два целых числа n и m — количество вершин и ребер графа соответственно
 * (1 <= n <= 20000, 1 <= m <= 200000).
 * Следующие m строк содержат описание ребер по одному на строке.
 * Ребро номер i описывается двумя натуральными числами b_i, e_i — номерами концов ребра (1 <= b_i, e_i <= n).
 *
 * Вывод: Первая строка выходного файла должна содержать одно натуральное число b — количество мостов в заданном графе.
 * На следующей строке выведите b целых чисел — номера ребер, которые являются мостами, в возрастающем порядке.
 * Ребра нумеруются с единицы в том порядке, в котором они заданы во входном файле.
 */


#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <vector>


std::set<int> find_bridges(const std::vector<std::vector<std::pair<int, int>>>& graph) {
    std::vector<int> bridges;
    std::vector<int> entry_time(graph.size(), 0);
    std::vector<int> lowest_time(graph.size(), 0);

    for (int i = 0; i < graph.size(); i++) {
        if (entry_time[i] == 0) {
            std::stack<std::pair<int, int>> stack;
            stack.push({i, -1});
            int timer = 0;

            while (!stack.empty()) {
                auto [v, transition_edge] = stack.top();
                if (entry_time[v] == 0) {
                    timer++;
                    entry_time[v] = timer;
                    lowest_time[v] = timer;

                    for (const auto [to_vertex, to_edge] : graph[v]) {
                        if (to_edge != transition_edge && entry_time[to_vertex] == 0) {
                            stack.push({to_vertex, to_edge});
                        }
                    }
                } else {
                    stack.pop();
                    for (const auto [to_vertex, to_edge] : graph[v]) {
                        if (to_edge == transition_edge) {
                            continue;
                        }

                        lowest_time[v] = std::min(lowest_time[v], lowest_time[to_vertex]);

                        if (lowest_time[to_vertex] > entry_time[v]) {
                            bridges.push_back(to_edge);
                        }
                    }
                }
            }
        }
    }

    return std::set<int> (bridges.begin(), bridges.end());
}


int main() {
    std::ifstream input("bridges.in");
    std::ofstream output("bridges.out");

    int n_vertices, n_edges;
    input >> n_vertices >> n_edges;
    std::vector<std::vector<std::pair<int, int>>> graph(n_vertices);

    for (int i = 1; i < n_edges + 1; i++) {
        int b, e;
        input >> b >> e;
        b--;
        e--;
        graph[b].push_back({e, i});
        graph[e].push_back({b, i});
    }

    std::set<int> bridges = find_bridges(graph);
    output << bridges.size() << "\n";
    for (const auto x : bridges) {
        output << x << "\n";
    }

    return 0;
}
