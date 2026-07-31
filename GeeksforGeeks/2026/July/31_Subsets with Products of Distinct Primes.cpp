class Solution {
public:
    static const int MOD = 1000000007;

    int countSubsets(vector<int>& arr) {
        vector<int> prime = {2,3,5,7,11,13,17,19,23,29};
        vector<long long> dp(1 << 10, 0);

        dp[0] = 1;
        int ones = 0;

        for (int num : arr) {
            if (num == 1) {
                ones++;
                continue;
            }

            int x = num;
            int mask = 0;
            bool ok = true;

            for (int i = 0; i < 10; i++) {
                int cnt = 0;
                while (x % prime[i] == 0) {
                    cnt++;
                    x /= prime[i];
                }
                if (cnt > 1) {
                    ok = false;
                    break;
                }
                if (cnt == 1)
                    mask |= (1 << i);
            }

            if (!ok || x > 1)
                continue;

            for (int m = (1 << 10) - 1; m >= 0; m--) {
                if ((m & mask) == 0) {
                    dp[m | mask] = (dp[m | mask] + dp[m]) % MOD;
                }
            }
        }

        long long ans = 0;
        for (int m = 1; m < (1 << 10); m++)
            ans = (ans + dp[m]) % MOD;

        long long mul = 1;
        while (ones--)
            mul = (mul * 2) % MOD;

        ans = (ans * mul) % MOD;

        return ans;
    }
};
