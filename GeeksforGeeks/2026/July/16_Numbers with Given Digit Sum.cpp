class Solution {
public:
    int dp[101][901];

    int solve(int pos, int sum, int n) {
        if (sum < 0)
            return 0;

        if (pos == n)
            return (sum == 0);

        if (dp[pos][sum] != -1)
            return dp[pos][sum];

        int ways = 0;

        int start = (pos == 0) ? 1 : 0;

        for (int d = start; d <= 9; d++) {
            ways += solve(pos + 1, sum - d, n);
        }

        return dp[pos][sum] = ways;
    }

    int countWays(int n, int sum) {

        if (sum > 9 * n || sum == 0)
            return -1;

        memset(dp, -1, sizeof(dp));

        int ans = solve(0, sum, n);

        return (ans == 0) ? -1 : ans;
    }
};
