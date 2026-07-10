class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                      vector<vector<int>>& queries) {
        // 1. Sort node indices by value.
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(),
             [&](int a, int b) { return nums[a] < nums[b]; });

        vector<int> pos(n), sortedVal(n);
        for (int i = 0; i < n; ++i) {
            pos[order[i]] = i;
            sortedVal[i] = nums[order[i]];
        }

        // 2. Two-pointer: reach[i] = farthest sorted position directly
        //    connected to position i (one edge away).
        vector<int> reach(n);
        int right = 0;
        for (int i = 0; i < n; ++i) {
            if (right < i) right = i;
            while (right + 1 < n && sortedVal[right + 1] - sortedVal[i] <= maxDiff)
                ++right;
            reach[i] = right;
        }

        // 3. Binary lifting on the "jump to farthest reachable" function.
        int LOG = 1;
        while ((1 << LOG) < n) ++LOG;
        vector<vector<int>> up(LOG + 1, vector<int>(n));
        up[0] = reach;
        for (int k = 1; k <= LOG; ++k)
            for (int i = 0; i < n; ++i)
                up[k][i] = up[k - 1][up[k - 1][i]];

        // 4. Answer each query.
        vector<int> answer(queries.size());
        for (int qi = 0; qi < (int)queries.size(); ++qi) {
            int p = pos[queries[qi][0]], q = pos[queries[qi][1]];
            if (p > q) swap(p, q);

            if (p == q) { answer[qi] = 0; continue; }

            int cur = p, steps = 0;
            for (int k = LOG; k >= 0; --k) {
                if (up[k][cur] < q && up[k][cur] > cur) {
                    steps += (1 << k);
                    cur = up[k][cur];
                }
            }

            answer[qi] = (reach[cur] >= q) ? steps + 1 : -1;
        }

        return answer;
    }
};
