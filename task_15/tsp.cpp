#include "tsp.h"
#include "mst.h"

#include <stack>

double exact_solution(double** adjacency_matrix, const int size) {
    const int starter_idx = 0;
    std::vector<int> path_edges(size - 1);
    for (int i = 1; i < size; i++) {
        path_edges[i - 1] = i;
    }

    double min_path_length = INT_MAX;
    do {
        double path_length = 0;
        path_length += adjacency_matrix[starter_idx][path_edges.front()];
        path_length += adjacency_matrix[starter_idx][path_edges.back()];

        for (int i = 0; i < path_edges.size() - 1; i++) {
            path_length += adjacency_matrix[path_edges[i]][path_edges[i + 1]];
        }

        if (path_length < min_path_length) {
            min_path_length = path_length;
        }
    } while(std::next_permutation(path_edges.begin(), path_edges.end()));

    return min_path_length;
}

std::vector<int> find_eulerian_cycle(std::vector<std::vector<int>>& eulerian_graph) {
    std::vector<int> eulerian_cycle;
    std::stack<int> s;
    s.push(0);

    while(!s.empty()) {
        int w = s.top();

        if (eulerian_graph[w].size() > 0) {
            s.push(eulerian_graph[w].back());
            eulerian_graph[w].pop_back();
        }

        if (w == s.top()) {
            s.pop();
            eulerian_cycle.push_back(w);
        }
    }

    return eulerian_cycle;
}

double approximate_solution(double** adjacency_matrix, const int size) {
    // find MST
    std::vector<std::tuple<int, int, double>> mst = get_mst(adjacency_matrix, size);

    // find Eulerian cycle
    std::vector<std::vector<int>> eulerian_graph(size);
    for (const auto& [i, j, w] : mst) {
        eulerian_graph[i].push_back(j);
        eulerian_graph[j].push_back(i);
    }
    std::vector<int> eulerian_cycle = find_eulerian_cycle(eulerian_graph);

    // find Hamiltonian cycle
    std::vector<bool> is_edge_visited(size, false);
    std::vector<int> hamiltonian_cycle;
    for (const int edge : eulerian_cycle) {
        if (!is_edge_visited[edge]) {
            is_edge_visited[edge] = true;
            hamiltonian_cycle.push_back(edge);
        }
    }
    hamiltonian_cycle.push_back(hamiltonian_cycle.front());

    // calculate path length
    double path_length = 0;
    for (int i = 0; i < hamiltonian_cycle.size() - 1; i++) {
        path_length += adjacency_matrix[hamiltonian_cycle[i]][hamiltonian_cycle[i + 1]];
    }

    return path_length;
}
