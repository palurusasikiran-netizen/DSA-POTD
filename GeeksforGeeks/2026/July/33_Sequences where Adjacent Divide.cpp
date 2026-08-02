class Solution {
public:
    static const int MOD = 1000000007;

    int count(int n, int m) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int j = 1; j <= m; j++)
            dp[1][j] = 1;

        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                long long ways = 0;

                // divisors of j
                for (int d = 1; d * d <= j; d++) {
                    if (j % d == 0) {
                        ways = (ways + dp[i - 1][d]) % MOD;

                        if (d != j / d)
                            ways = (ways + dp[i - 1][j / d]) % MOD;
                    }
                }

                // multiples of j
                for (int k = 2 * j; k <= m; k += j) {
                    ways = (ways + dp[i - 1][k]) % MOD;
                }

                dp[i][j] = ways;
            }
        }

        long long ans = 0;
        for (int j = 1; j <= m; j++)
            ans = (ans + dp[n][j]) % MOD;

        return ans;
    }
};
