#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using hop_t = struct {
    double weight;
    int vertex;
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

void print_matrices_latex(const std::vector<std::vector<hop_t>> &DP,
                          const std::vector<std::vector<hop_t>> &DP_prev,
                          int step, int V)
{
    std::cout << "\nD^{(" << step << ")} = \\begin{bmatrix}\n";
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            bool changed = (DP_prev.empty())
                               ? false
                               : (DP[u][v].weight != DP_prev[u][v].weight);
            std::cout << format_value(DP[u][v].weight, changed);
            if (v < V - 1) std::cout << " & ";
        }
        std::cout << " \\\\\n";
    }
    std::cout << "\\end{bmatrix}\n";

    std::cout << "\nP^{(" << step << ")} = \\begin{bmatrix}\n";
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            bool changed = (DP_prev.empty())
                               ? false
                               : (DP[u][v].vertex != DP_prev[u][v].vertex);
            std::cout << format_vertex(DP[u][v].vertex, changed);
            if (v < V - 1) std::cout << " & ";
        }
        std::cout << " \\\\\n";
    }
    std::cout << "\\end{bmatrix}\n";
}

std::vector<std::vector<hop_t>> floyd_warshall(const Graph &graph)
{
    const auto V = static_cast<int>(graph.size());

    auto DP =
        std::vector<std::vector<hop_t>>(V, std::vector<hop_t>(V, {inf, -1}));

    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (u == v) {
                DP[u][v].weight = 0;
                DP[u][v].vertex = -1;
            } else if (std::isfinite(graph[u][v])) {
                DP[u][v].weight = graph[u][v];
                DP[u][v].vertex = u;
            }
        }
    }

    std::vector<std::vector<hop_t>> empty;
    print_matrices_latex(DP, empty, 0, V);

    for (int r = 0; r < V; ++r) {
        auto DP_prev = DP;
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                auto duv = DP[u][v].weight;
                auto dur = DP[u][r].weight;
                auto drv = DP[r][v].weight;
                if (dur + drv < duv) {
                    DP[u][v].weight = dur + drv;
                    DP[u][v].vertex = DP[r][v].vertex;
                }
            }
        }
        print_matrices_latex(DP, DP_prev, r + 1, V);
    }

    return DP;
}

int main()
{
    // Test graph: D^(0) matrix as given
    Graph graph = {{0, 1, inf, inf, inf},
                   {inf, 0, 2, 4, inf},
                   {3, inf, 0, inf, 2},
                   {6, inf, inf, 0, 1},
                   {inf, inf, inf, inf, 0}};

    std::cout << "Floyd-Warshall Algorithm Execution\n";
    std::cout << "===================================\n";

    auto result = floyd_warshall(graph);

    return 0;
}
