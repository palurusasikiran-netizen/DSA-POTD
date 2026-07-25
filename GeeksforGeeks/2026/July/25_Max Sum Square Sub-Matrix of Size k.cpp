class Solution {
public:
    int maximumSum(vector<vector<int>>& mat, int k) {
        int n = mat.size();

        vector<vector<int>> pre(n + 1, vector<int>(n + 1, 0));

        // Build prefix sum
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                pre[i][j] = mat[i - 1][j - 1]
                          + pre[i - 1][j]
                          + pre[i][j - 1]
                          - pre[i - 1][j - 1];
            }
        }

        int ans = INT_MIN;

        // Check every k x k submatrix
        for (int i = k; i <= n; i++) {
            for (int j = k; j <= n; j++) {
                int sum = pre[i][j]
                        - pre[i - k][j]
                        - pre[i][j - k]
                        + pre[i - k][j - k];

                ans = max(ans, sum);
            }
        }

        return ans;
    }
};
