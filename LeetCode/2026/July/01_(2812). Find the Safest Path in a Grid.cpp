class Solution {
public:
    int n;

    bool isValid(int r, int c) {
        return r >= 0 && c >= 0 && r < n && c < n;
    }

    bool canReach(vector<vector<int>>& dist, int limit) {

        if (dist[0][0] < limit)
            return false;

        queue<pair<int,int>> q;
        vector<vector<bool>> vis(n, vector<bool>(n, false));

        q.push({0,0});
        vis[0][0] = true;

        int dr[] = {-1,1,0,0};
        int dc[] = {0,0,-1,1};

        while (!q.empty()) {

            auto [r,c] = q.front();
            q.pop();

            if (r == n - 1 && c == n - 1)
                return true;

            for (int k = 0; k < 4; k++) {

                int nr = r + dr[k];
                int nc = c + dc[k];

                if (isValid(nr,nc) &&
                    !vis[nr][nc] &&
                    dist[nr][nc] >= limit) {

                    vis[nr][nc] = true;
                    q.push({nr,nc});
                }
            }
        }

        return false;
    }

    int maximumSafenessFactor(vector<vector<int>>& grid) {

        n = grid.size();

        vector<vector<int>> dist(n, vector<int>(n, -1));

        queue<pair<int,int>> q;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i,j});
                }
            }
        }

        int dr[] = {-1,1,0,0};
        int dc[] = {0,0,-1,1};

        while (!q.empty()) {

            auto [r,c] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++) {

                int nr = r + dr[k];
                int nc = c + dc[k];

                if (isValid(nr,nc) && dist[nr][nc] == -1) {

                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr,nc});
                }
            }
        }

        int low = 0;
        int high = 2 * n;
        int ans = 0;

        while (low <= high) {

            int mid = low + (high - low) / 2;

            if (canReach(dist, mid)) {
                ans = mid;
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        return ans;
    }
};
