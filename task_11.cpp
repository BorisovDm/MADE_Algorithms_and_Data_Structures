/*
 * Задача 11_2. Количество различных путей (5 баллов)
 *
 * Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
 * Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).
 *
 * Ввод:
 *     v: кол-во вершин (макс. 50000),
 *     n: кол-во ребер (макс. 200000),
 *     n пар реберных вершин,
 *     пара вершин v, w для запроса.
 *
 * Вывод: количество кратчайших путей от v к w.
 */


#include <iostream>
#include <vector>
#include <queue>


struct Node {
    std::vector<int> adjacency_list;
    int n_paths = 0;
    int path_length = 0;
};

int main() {
    int n_vertices, n_edges;
    std::cin >> n_vertices >> n_edges;
    std::vector<Node> graph(n_vertices);

    int v, w;
    for (int i = 0; i < n_edges; i++) {
        std::cin >> v >> w;
        graph[v].adjacency_list.push_back(w);
        graph[w].adjacency_list.push_back(v);
    }

    std::cin >> v;
    graph[v].n_paths = 1;

    std::queue<int> vertices_queue;
    vertices_queue.push(v);

    while (!vertices_queue.empty()) {
        int current_node = vertices_queue.front();
        vertices_queue.pop();

        for (const auto neighbor : graph[current_node].adjacency_list) {
            // ещё не посещённая вершина
            if (graph[neighbor].n_paths == 0) {
                graph[neighbor].path_length = graph[current_node].path_length + 1;
                graph[neighbor].n_paths = graph[current_node].n_paths;
                vertices_queue.push(neighbor);
                continue;
            }

            // если вершина neighbor достижима из current_node по ещё одному кратчайшему пути
            if (graph[neighbor].path_length == graph[current_node].path_length + 1) {
                graph[neighbor].n_paths += graph[current_node].n_paths;
            }
        }
    }

    std::cin >> w;
    std::cout << graph[w].n_paths << std::endl;
    return 0;
}
