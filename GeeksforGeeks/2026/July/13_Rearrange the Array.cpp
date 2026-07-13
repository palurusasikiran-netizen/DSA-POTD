class Solution {
public:
    const int MOD = 1000000007;

    long long modPow(long long a, long long b) {
        long long res = 1;
        while (b) {
            if (b & 1)
                res = (res * a) % MOD;
            a = (a * a) % MOD;
            b >>= 1;
        }
        return res;
    }

    int minOperations(vector<int> &b) {
        int n = b.size();

        vector<bool> vis(n, false);

        unordered_map<int, int> primePower;

        for (int i = 0; i < n; i++) {
            if (vis[i]) continue;

            int len = 0;
            int cur = i;

            while (!vis[cur]) {
                vis[cur] = true;
                cur = b[cur] - 1;   // 1-based to 0-based
                len++;
            }

            int x = len;

            for (int p = 2; p * p <= x; p++) {
                if (x % p == 0) {
                    int cnt = 0;
                    while (x % p == 0) {
                        x /= p;
                        cnt++;
                    }
                    primePower[p] = max(primePower[p], cnt);
                }
            }

            if (x > 1)
                primePower[x] = max(primePower[x], 1);
        }

        long long ans = 1;

        for (auto &it : primePower) {
            ans = (ans * modPow(it.first, it.second)) % MOD;
        }

        return (int)ans;
    }
};
