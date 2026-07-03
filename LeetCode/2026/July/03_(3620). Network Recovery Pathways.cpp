class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges,
                         vector<bool>& online,
                         long long k) {

        int n = online.size();

        vector<vector<pair<int, int>>> graph(n);
        vector<int> indegree(n, 0);

        int maxEdge = 0;

        for (auto &e : edges) {
            graph[e[0]].push_back({e[1], e[2]});
            indegree[e[1]]++;
            maxEdge = max(maxEdge, e[2]);
        }

        auto check = [&](int limit) {

            vector<long long> dist(n, LLONG_MAX);
            vector<int> deg = indegree;

            queue<int> q;

            for (int i = 0; i < n; i++) {
                if (deg[i] == 0)
                    q.push(i);
            }

            dist[0] = 0;

            while (!q.empty()) {

                int u = q.front();
                q.pop();

                for (auto &[v, cost] : graph[u]) {

                    deg[v]--;

                    if (deg[v] == 0)
                        q.push(v);

                    if (cost < limit)
                        continue;

                    if (v != n - 1 && !online[v])
                        continue;

                    if (dist[u] == LLONG_MAX)
                        continue;

                    dist[v] = min(dist[v], dist[u] + cost);
                }
            }

            return dist[n - 1] <= k;
        };

        int low = 0;
        int high = maxEdge;
        int ans = -1;

        while (low <= high) {

            int mid = low + (high - low) / 2;

            if (check(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};
