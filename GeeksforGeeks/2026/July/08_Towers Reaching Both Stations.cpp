class Solution {
public:
    int countCoordinates(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<bool>> reachP(n, vector<bool>(m, false));
        vector<vector<bool>> reachQ(n, vector<bool>(m, false));

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        auto bfs = [&](vector<pair<int,int>>& sources, vector<vector<bool>>& reach) {
            queue<pair<int,int>> q;
            for (auto& p : sources) {
                if (!reach[p.first][p.second]) {
                    reach[p.first][p.second] = true;
                    q.push(p);
                }
            }
            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if (reach[nx][ny]) continue;
                    // reverse edge: original edge (nx,ny) -> (x,y) requires mat[x][y] <= mat[nx][ny]
                    if (mat[nx][ny] >= mat[x][y]) {
                        reach[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        };

        vector<pair<int,int>> pSources, qSources;
        for (int j = 0; j < m; j++) pSources.push_back({0, j});
        for (int i = 0; i < n; i++) pSources.push_back({i, 0});
        for (int j = 0; j < m; j++) qSources.push_back({n - 1, j});
        for (int i = 0; i < n; i++) qSources.push_back({i, m - 1});

        bfs(pSources, reachP);
        bfs(qSources, reachQ);

        int count = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (reachP[i][j] && reachQ[i][j]) count++;

        return count;
    }
};
