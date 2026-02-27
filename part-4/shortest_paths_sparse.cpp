#include "shortest_paths_sparse.hpp"
#include <priority_queue.hpp>

#include <cmath>

std::vector<hop_t> bellman_ford(const SparseGraph &graph, const int source,
                                bool &has_negative_cycle)
{
    const int V = static_cast<int>(graph.size());
    auto DP = std::vector<hop_t>(V, {inf, -1});

    // WRITE YOUR CODE HERE
    has_negative_cycle = false;
    assert(0 <= source && source < V);
    DP[source].weight = 0;
    for (int iter = 0; iter < V-1; ++iter) {
        for (int r = 0; r < V; ++r) {
            for (const auto &hop : graph[r]) {
                int v = hop.vertex;
                float w = hop.weight;
                if ((DP[r].weight + w < DP[v].weight) && (DP[r].weight != inf)) {
                    DP[v] = {DP[r].weight + w, r};
                }
            }
        }
    }

    // Checks for negative cycle by trying to relax one more time (theoretically V-1 relaxations is the max if no negative cycles present)
    for (int r = 0; r < V; ++r) {
        for (const auto &hop : graph[r]) {
            int v = hop.vertex;
            float w = hop.weight;
            if ((DP[r].weight + w < DP[v].weight) && (DP[r].weight != inf)) {
                has_negative_cycle = true;
                break;
            }
        }
        if (has_negative_cycle) {
            break;
        }
    }


    return DP;
}

struct triplet_t {
    float d;
    int r;
    int v;
};

std::vector<hop_t> dijkstra(const SparseGraph &graph, const int source)
{
    assert(source >= 0);
    assert(source < (signed)graph.size());

    auto DP = std::vector<hop_t>(graph.size(), {inf, -1});

    // WRITE YOUR CODE HERE
    DP[source].weight = 0;

    std::vector<bool> visited(graph.size(), false);

    for (int a = 0; a < (signed)graph.size(); ++a) {
        int r = -1;
        float min_d = inf;
        for (int i = 0; i < (signed)graph.size(); ++i) {
            if (!visited[i] && DP[i].weight < min_d) {
                min_d = DP[i].weight;
                r = i;
            }
        }
        if (r == -1) {
            break; // No more reachable vertices
        }
        visited[r] = true;

        for (const auto &hop : graph[r]) {
            int v = hop.vertex;
            float w = hop.weight;
            if (!visited[v] && DP[r].weight + w < DP[v].weight) {
                DP[v] = {DP[r].weight + w, r};
            }
        }
    }



    return DP;
}
