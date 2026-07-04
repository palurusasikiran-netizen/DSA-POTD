class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> graph(n + 1);
        for (auto& r : roads) {
            graph[r[0]].push_back({r[1], r[2]});
            graph[r[1]].push_back({r[0], r[2]});
        }

        vector<bool> visited(n + 1, false);
        int answer = INT_MAX;
        queue<int> q;
        q.push(1);
        visited[1] = true;

        while (!q.empty()) {
            int city = q.front();
            q.pop();
            for (auto& [next, dist] : graph[city]) {
                answer = min(answer, dist);
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }

        return answer;
    }
};
