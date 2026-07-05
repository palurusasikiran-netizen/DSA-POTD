class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        const int MOD = 1e9 + 7;
        int n = board.size();
        vector<vector<int>> best(n + 1, vector<int>(n + 1, -1));
        vector<vector<int>> ways(n + 1, vector<int>(n + 1, 0));

        best[n - 1][n - 1] = 0;
        ways[n - 1][n - 1] = 1;

        int dx[] = {1, 0, 1};
        int dy[] = {0, 1, 1};

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (board[i][j] == 'X' || board[i][j] == 'S') continue;

                int bestSum = -1, count = 0;
                for (int d = 0; d < 3; d++) {
                    int ni = i + dx[d], nj = j + dy[d];
                    if (ni >= n || nj >= n || best[ni][nj] < 0) continue;
                    if (best[ni][nj] > bestSum) {
                        bestSum = best[ni][nj];
                        count = ways[ni][nj];
                    } else if (best[ni][nj] == bestSum) {
                        count = (count + ways[ni][nj]) % MOD;
                    }
                }

                if (bestSum < 0) continue;
                int add = (board[i][j] == 'E') ? 0 : board[i][j] - '0';
                best[i][j] = bestSum + add;
                ways[i][j] = count;
            }
        }

        if (best[0][0] < 0) return {0, 0};
        return {best[0][0], ways[0][0]};
    }
};
