#include "mst.h"


std::vector<std::tuple<int, int, double>> get_mst(double** adjacency_matrix, const int graph_size) {
    std::vector<bool> is_in_mst(graph_size, false);
    std::vector<int> reachable_from(graph_size, INT_MIN);
    std::vector<double> min_edge_weight(graph_size, INT_MAX);
    std::set<std::pair<double, int>> priority_set;

    // init starter point
    priority_set.insert({0., 0});
    min_edge_weight[0] = 0.;

    while (!priority_set.empty()) {
        int next_mst_vertex_idx = priority_set.begin()->second;
        is_in_mst[next_mst_vertex_idx] = true;
        priority_set.erase(priority_set.begin());

        for (int vertex = 0; vertex < graph_size; vertex++) {
            double edge_weight = adjacency_matrix[next_mst_vertex_idx][vertex];
            if (edge_weight > 0 && !is_in_mst[vertex] && min_edge_weight[vertex] > edge_weight) {
                priority_set.erase({min_edge_weight[vertex], vertex});
                reachable_from[vertex] = next_mst_vertex_idx;
                min_edge_weight[vertex] = edge_weight;
                priority_set.insert({min_edge_weight[vertex], vertex});
            }
        }
    }
    assert(std::count(min_edge_weight.begin(), min_edge_weight.end(), INT_MAX) == 0);

    std::vector<std::tuple<int, int, double>> mst(graph_size - 1);
    for (int i = 0, mst_idx = 0; i < graph_size; i++) {
        if (reachable_from[i] != INT_MIN) {
            mst[mst_idx++] = {reachable_from[i], i, min_edge_weight[i]};
        }
    }

    return mst;
}
