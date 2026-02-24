#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

struct hop_t {
    double weight;
    int vertex;

    bool operator==(const hop_t &other) const
    {
        return weight == other.weight && vertex == other.vertex;
    }

    bool operator!=(const hop_t &other) const { return !(*this == other); }
};

constexpr double inf = std::numeric_limits<double>::infinity();

using Graph = std::vector<std::vector<double>>;

std::string format_value(double val, bool changed = false)
{
    std::string color_start = changed ? "\\color{green}" : "";
    if (std::isinf(val)) { return color_start + "\\color{AAAAAA}\\infty"; }
    return color_start + std::to_string(static_cast<int>(val));
}

std::string format_vertex(int v, bool changed = false)
{
    std::string color_start = changed ? "\\color{green}" : "";
    if (v == -1) { return color_start + "\\color{AAAAAA}-1"; }
    return color_start + std::to_string(v + 1);
}

void print_vector_latex(const std::vector<hop_t> &DP,
                        const std::vector<hop_t> &DP_prev, int r, int v, int V)
{
    std::cout << "\n(" << r + 1 << ", " << v + 1 << ")\n";

    std::cout << "\nD = \\begin{bmatrix}\n";
    for (int v = 0; v < V; ++v) {
        bool changed =
            (DP_prev.empty()) ? false : (DP[v].weight != DP_prev[v].weight);
        std::cout << format_value(DP[v].weight, changed);
        if (v < V - 1) std::cout << " & ";
    }
    std::cout << "\n\\end{bmatrix}\n";

    std::cout << "\nP = \\begin{bmatrix}\n";
    for (int v = 0; v < V; ++v) {
        bool changed =
            (DP_prev.empty()) ? false : (DP[v].vertex != DP_prev[v].vertex);
        std::cout << format_vertex(DP[v].vertex, changed);
        if (v < V - 1) std::cout << " & ";
    }
    std::cout << "\n\\end{bmatrix}\n";
}

bool relax(const Graph &graph, std::vector<hop_t> &DP, int u, int v)
{
    if (std::isfinite(graph[u][v]) &&
        DP[u].weight + graph[u][v] < DP[v].weight) {
        DP[v].weight = DP[u].weight + graph[u][v];
        DP[v].vertex = u;
        return true;
    }
    return false;
}

std::vector<hop_t> bellman_ford(const Graph &graph, const int source,
                                bool &has_negative_cycle)
{
    const int V = static_cast<int>(graph.size());
    assert(0 <= source && source < V);

    auto DP = std::vector<hop_t>(V, {inf, -1});
    DP[source].weight = 0;

    std::vector<hop_t> empty;
    print_vector_latex(DP, empty, 0, 0, V);

    for (int iter = 0; iter < V - 1; ++iter) {
        has_negative_cycle = false;
        for (int r = 0; r < V; ++r) {
            for (int v = 0; v < V; ++v) {
                auto DP_prev = DP;
                has_negative_cycle |= relax(graph, DP, r, v);
                if (DP != DP_prev) { print_vector_latex(DP, DP_prev, r, v, V); }
            }
        }
    }

    return DP;
}

int main()
{
    // Test graph: same as Floyd-Warshall example
    Graph graph = {{0, 1, inf, inf, inf},
                   {inf, 0, 2, 4, inf},
                   {3, inf, 0, inf, 8},
                   {6, inf, inf, 0, 1},
                   {inf, inf, inf, inf, 0}};

    std::cout << "Bellman-Ford Algorithm Execution\n";
    std::cout << "=================================\n";
    std::cout << "Source vertex: 1\n";

    bool has_negative_cycle = false;
    auto result = bellman_ford(graph, 0, has_negative_cycle);

    if (has_negative_cycle) { std::cout << "\nNegative cycle detected!\n"; }

    return 0;
}
