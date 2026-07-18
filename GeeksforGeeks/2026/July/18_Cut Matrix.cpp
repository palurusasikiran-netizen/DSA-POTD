class Solution {
public:
    int findWays(vector<vector<int>>& matrix, int k) {
        int n = matrix.size(), m = matrix[0].size();
        const long long MOD = 1e9 + 7;

        // For each (i,j): first row >= i with a 1 in cols [j..m-1]; first col >= j with a 1 in rows [i..n-1]
        vector<vector<int>> rowSuffixOnes(n, vector<int>(m + 1, 0));
        for (int i = 0; i < n; i++)
            for (int j = m - 1; j >= 0; j--)
                rowSuffixOnes[i][j] = rowSuffixOnes[i][j+1] + matrix[i][j];

        vector<vector<int>> colSuffixOnes(n + 1, vector<int>(m, 0));
        for (int j = 0; j < m; j++)
            for (int i = n - 1; i >= 0; i--)
                colSuffixOnes[i][j] = colSuffixOnes[i+1][j] + matrix[i][j];

        vector<vector<int>> nextRowWithOne(n + 1, vector<int>(m, n));
        for (int j = 0; j < m; j++)
            for (int i = n - 1; i >= 0; i--)
                nextRowWithOne[i][j] = (rowSuffixOnes[i][j] > 0) ? i : nextRowWithOne[i+1][j];

        vector<vector<int>> nextColWithOne(n, vector<int>(m + 1, m));
        for (int i = 0; i < n; i++)
            for (int j = m - 1; j >= 0; j--)
                nextColWithOne[i][j] = (colSuffixOnes[i][j] > 0) ? j : nextColWithOne[i][j+1];

        vector<vector<int>> pre(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                pre[i+1][j+1] = pre[i][j+1] + pre[i+1][j] - pre[i][j] + matrix[i][j];

        // flat, reused buffers -- avoids reallocating on every p level
        vector<long long> dpPrev((n + 1) * (m + 1), 0);
        vector<long long> dpCur((n + 1) * (m + 1), 0);
        vector<long long> suffRow((n + 1) * m, 0);
        vector<long long> suffCol(n * (m + 1), 0);
        auto idxP  = [&](int i, int j) { return i * (m + 1) + j; };
        auto idxSR = [&](int i, int j) { return i * m + j; };
        auto idxSC = [&](int i, int j) { return i * (m + 1) + j; };

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                int total = pre[n][m] - pre[i][m] - pre[n][j] + pre[i][j];
                dpPrev[idxP(i,j)] = (total > 0) ? 1 : 0;
            }

        if (k == 1) return (int)dpPrev[idxP(0,0)];

        for (int p = 2; p <= k; p++) {
            for (int j = 0; j < m; j++) suffRow[idxSR(n,j)] = 0;
            for (int j = 0; j < m; j++)
                for (int i = n - 1; i >= 0; i--)
                    suffRow[idxSR(i,j)] = suffRow[idxSR(i+1,j)] + dpPrev[idxP(i,j)];

            for (int i = 0; i < n; i++) suffCol[idxSC(i,m)] = 0;
            for (int i = 0; i < n; i++)
                for (int j = m - 1; j >= 0; j--)
                    suffCol[idxSC(i,j)] = suffCol[idxSC(i,j+1)] + dpPrev[idxP(i,j)];

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    long long total = 0;
                    int r0 = nextRowWithOne[i][j];
                    if (r0 < n) { int sr = r0 + 1; total += suffRow[idxSR(sr,j)]; }
                    int c0 = nextColWithOne[i][j];
                    if (c0 < m) { int sc = c0 + 1; total += suffCol[idxSC(i,sc)]; }
                    dpCur[idxP(i,j)] = total % MOD;
                }
            }
            swap(dpPrev, dpCur);
        }

        return (int)dpPrev[idxP(0,0)];
    }
};
