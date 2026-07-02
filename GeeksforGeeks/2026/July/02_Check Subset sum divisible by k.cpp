class Solution {
public:
    bool divisibleByK(vector<int>& arr, int k) {

        vector<bool> dp(k, false);

        for (int num : arr) {

            vector<bool> next = dp;

            next[num % k] = true;

            for (int rem = 0; rem < k; rem++) {

                if (dp[rem]) {
                    int newRem = (rem + num) % k;
                    next[newRem] = true;
                }
            }

            dp = next;

            if (dp[0])
                return true;
        }

        return false;
    }
};
