class Solution {
public:
    int largestArea(int n, int m, vector<vector<int>> &arr) {
        vector<bool> rowBlocked(n + 1, false);
        vector<bool> colBlocked(m + 1, false);

        for (auto& cell : arr) {
            rowBlocked[cell[0]] = true;
            colBlocked[cell[1]] = true;
        }

        int maxRows = 0, cur = 0;
        for (int r = 1; r <= n; r++) {
            cur = rowBlocked[r] ? 0 : cur + 1;
            maxRows = max(maxRows, cur);
        }

        int maxCols = 0;
        cur = 0;
        for (int c = 1; c <= m; c++) {
            cur = colBlocked[c] ? 0 : cur + 1;
            maxCols = max(maxCols, cur);
        }

        return maxRows * maxCols;
    }
};
