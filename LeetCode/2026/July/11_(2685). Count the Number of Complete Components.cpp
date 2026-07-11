class Solution {
public:

    void dfs(int node,
             vector<vector<int>>& graph,
             vector<bool>& visited,
             int &nodes,
             int &edges)
    {
        visited[node] = true;
        nodes++;
        edges += graph[node].size();

        for (int next : graph[node]) {
            if (!visited[next])
                dfs(next, graph, visited, nodes, edges);
        }
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {

        vector<vector<int>> graph(n);

        for (auto &e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        vector<bool> visited(n, false);

        int answer = 0;

        for (int i = 0; i < n; i++) {

            if (visited[i])
                continue;

            int nodes = 0;
            int edgeCount = 0;

            dfs(i, graph, visited, nodes, edgeCount);

            edgeCount /= 2;

            if (edgeCount == nodes * (nodes - 1) / 2)
                answer++;
        }

        return answer;
    }
};
