class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const long long MOD = 1000000007LL;
        int m = s.size();

        vector<long long> V(m + 1, 0);       // value mod p of non-zero digits so far
        vector<long long> cnt(m + 1, 0);     // count of non-zero digits so far
        vector<long long> prefSum(m + 1, 0); // running digit sum
        vector<long long> pow10(m + 1, 1);   // powers of 10 mod p (indexed by digit count)

        for (int i = 0; i < m; i++) {
            pow10[i + 1] = (pow10[i] * 10) % MOD;
            int d = s[i] - '0';
            prefSum[i + 1] = prefSum[i] + d;
            if (d != 0) {
                V[i + 1] = (V[i] * 10 + d) % MOD;
                cnt[i + 1] = cnt[i] + 1;
            } else {
                V[i + 1] = V[i];
                cnt[i + 1] = cnt[i];
            }
        }

        vector<int> answer;
        answer.reserve(queries.size());

        for (auto& q : queries) {
            int l = q[0], r = q[1];
            long long diffCnt = cnt[r + 1] - cnt[l];
            long long x = ((V[r + 1] - (V[l] * pow10[diffCnt]) % MOD) % MOD + MOD) % MOD;
            long long sum = (prefSum[r + 1] - prefSum[l]) % MOD;
            long long ans = (x * sum) % MOD;
            answer.push_back((int)ans);
        }

        return answer;
    }
};
