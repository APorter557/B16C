#ifndef __shortest_paths_decode__
#define __shortest_paths_decode__

#include "graph.hpp"
#include <algorithm>
#include <vector>

inline std::vector<int> decode(const std::vector<hop_t> &DP, int v)
{
    // WRITE YOUR CODE HERE
    std::vector<int> path;
    int u = v;

    while (DP[u].vertex != -1) {
        path.push_back(u);
        u = DP[u].vertex;
    }
    path.push_back(u);
    std::reverse(path.begin(), path.end());
    return path;
}

#endif // __shortest_paths_decode__
