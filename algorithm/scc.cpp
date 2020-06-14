// Need start
#include<algorithm>
#include<vector>
// Need end

// Copy start
class SCC {
private:
    int group_num_;
    std::vector<int> groups_;

    void dfs1(const std::vector<std::vector<int>>& graph, std::vector<bool>& visited, int node, std::vector<int>& tsorted_nodes) {
        visited[node] = true;
        for (auto& next_node : graph[node]) {
            if (!visited[next_node]) {
                dfs1(graph, visited, next_node, tsorted_nodes);
            }
        }
        tsorted_nodes.push_back(node);
    }

    void dfs2(const std::vector<std::vector<int>>& graph, int node) {
        groups_[node] = group_num_;
        for (auto& next_node : graph[node]) {
            if (groups_[next_node] < 0) {
                dfs2(graph, next_node);
            }
        }
    }
public:
    SCC(const std::vector<std::vector<int>>& graph, const std::vector<std::vector<int>>& rev_graph) {
        int N = (int)graph.size();
        std::vector<int> tsorted_nodes;
        std::vector<bool> visited(N, false);
        for (int node = 0; node < N; ++node) {
            if (!visited[node]) {
                dfs1(graph, visited, node, tsorted_nodes);
            }
        }
        std::reverse(tsorted_nodes.begin(), tsorted_nodes.end());
        groups_ = std::vector<int>(N, -1);
        group_num_ = 0;
        for (auto& node : tsorted_nodes) {
            if (groups_[node] < 0) {
                dfs2(rev_graph, node);
                ++group_num_;
            }
        }
    }

    int getGroupNum() const {
        return group_num_;
    }

    std::vector<int> getSCC() const {
        return groups_;
    }
};
// Copy end

#include<iostream>

int main() {
    // This sample is yosupo judge (https://judge.yosupo.jp/problem/scc)
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> graph(N);
    std::vector<std::vector<int>> rev_graph(N);
    int a, b;
    for (int i = 0; i < M; ++i) {
        std::cin >> a >> b;
        graph[a].push_back(b);
        rev_graph[b].push_back(a);
    }
    SCC scc(graph, rev_graph);
    std::vector<int> groups = scc.getSCC();
    std::vector<std::vector<int>> components(scc.getGroupNum());
    for (int node = 0; node < N; ++node) {
        components[groups[node]].push_back(node);
    }
    std::cout << scc.getGroupNum() << std::endl;
    for (auto& nodes : components) {
        std::cout << nodes.size() << ' ';
        for (auto& node : nodes) {
            std::cout << node << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}