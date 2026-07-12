class Solution {
public:
    int maxAmount(vector<int>& arr, int k) {
        const int MOD = 1e9 + 7;

        priority_queue<int> pq;

        for (int x : arr) {
            if (x > 0)
                pq.push(x);
        }

        long long ans = 0;

        while (k > 0 && !pq.empty()) {
            int x = pq.top();
            pq.pop();

            ans = (ans + x) % MOD;

            if (x - 1 > 0)
                pq.push(x - 1);

            k--;
        }

        return ans % MOD;
    }
};
