#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

struct hop_t {
    double weight;
    int vertex;
    
    bool operator==(const hop_t& other) const {
        return weight == other.weight && vertex == other.vertex;
    }
    
    bool operator!=(const hop_t& other) const {
        return !(*this == other);
    }
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
                        const std::vector<hop_t> &DP_prev,
                        const std::vector<bool> &is_open,
                        int v_star, int V)
{
    std::cout << "\nD^{(" << (v_star + 1) << ")} = \\begin{bmatrix}\n";
    for (int v = 0; v < V; ++v) {
        bool changed =
            (DP_prev.empty()) ? false : (DP[v].weight != DP_prev[v].weight);
        std::cout << format_value(DP[v].weight, changed);
        if (v < V - 1) std::cout << " & ";
    }
    std::cout << "\n\\end{bmatrix}\n";

    std::cout << "\nP^{(" << (v_star + 1) << ")} = \\begin{bmatrix}\n";
    for (int v = 0; v < V; ++v) {
        bool changed =
            (DP_prev.empty()) ? false : (DP[v].vertex != DP_prev[v].vertex);
        std::cout << format_vertex(DP[v].vertex, changed);
        if (v < V - 1) std::cout << " & ";
    }
    std::cout << "\n\\end{bmatrix}\n";

    std::cout << "\n\\text{Open} = \\{";
    bool first = true;
    for (int v = 0; v < V; ++v) {
        if (is_open[v]) {
            if (!first) std::cout << ", ";
            std::cout << (v + 1);
            first = false;
        }
    }
    std::cout << "\\}\n";
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

std::vector<hop_t> dijkstra(const Graph &graph, const int source)
{
    const int V = static_cast<int>(graph.size());
    assert(0 <= source && source < V);

    auto DP = std::vector<hop_t>(V, {inf, -1});
    DP[source].weight = 0;

    std::vector<bool> is_open(V, true);

    std::vector<hop_t> empty;
    print_vector_latex(DP, empty, is_open, source, V);

    while (true) {
        float D_star = inf;
        int v_star = -1;
        for (int v = 0; v < V; ++v) {
            if (is_open[v] && DP[v].weight < D_star) {
                D_star = DP[v].weight;
                v_star = v;
            }
        }

        if (v_star < 0) {
            break; // all closed, stop
        }

        is_open[v_star] = false;

        auto DP_prev = DP;
        for (int v = 0; v < V; ++v) {
            if (is_open[v] && std::isfinite(graph[v_star][v])) {
                relax(graph, DP, v_star, v);
            }
        }
        print_vector_latex(DP, DP_prev, is_open, v_star, V);
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

    std::cout << "Dijkstra Algorithm Execution\n";
    std::cout << "=============================\n";
    std::cout << "Source vertex: 1\n";

    auto result = dijkstra(graph, 0);

    return 0;
}
