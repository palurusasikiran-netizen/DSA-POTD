class Solution {
public:

    int n, m;
    int ans = -1;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    void dfs(vector<vector<int>> &mat,
             vector<vector<bool>> &visited,
             int row,
             int col,
             int xd,
             int yd,
             int length)
    {
        if (row == xd && col == yd) {
            ans = max(ans, length);
            return;
        }

        visited[row][col] = true;

        for (int k = 0; k < 4; k++) {

            int newRow = row + dr[k];
            int newCol = col + dc[k];

            if (newRow >= 0 &&
                newRow < n &&
                newCol >= 0 &&
                newCol < m &&
                mat[newRow][newCol] == 1 &&
                !visited[newRow][newCol])
            {
                dfs(mat, visited, newRow, newCol, xd, yd, length + 1);
            }
        }

        // Backtrack
        visited[row][col] = false;
    }

    int longestPath(vector<vector<int>>& mat,
                    int xs,
                    int ys,
                    int xd,
                    int yd)
    {
        n = mat.size();
        m = mat[0].size();

        if (mat[xs][ys] == 0 || mat[xd][yd] == 0)
            return -1;

        vector<vector<bool>> visited(n, vector<bool>(m, false));

        dfs(mat, visited, xs, ys, xd, yd, 0);

        return ans;
    }
};
