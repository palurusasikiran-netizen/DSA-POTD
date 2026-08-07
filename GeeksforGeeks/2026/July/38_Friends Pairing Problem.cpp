class Solution {
public:
    int countFriendsPairings(int n) {
        const int MOD = 1000000007;

        if (n <= 2)
            return n;

        long long prev2 = 1; // f(1)
        long long prev1 = 2; // f(2)

        for (int i = 3; i <= n; i++) {
            long long curr = (prev1 + (i - 1) * prev2) % MOD;
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};
