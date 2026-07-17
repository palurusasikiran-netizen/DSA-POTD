class Solution {
public:
    int maxDiffSubArrays(vector<int>& arr) {
        int n = arr.size();

        vector<int> leftMax(n), rightMax(n);
        vector<int> leftMin(n), rightMin(n);

        // Maximum subarray from left
        int cur = arr[0], best = arr[0];
        leftMax[0] = arr[0];
        for (int i = 1; i < n; i++) {
            cur = max(arr[i], cur + arr[i]);
            best = max(best, cur);
            leftMax[i] = best;
        }

        // Minimum subarray from left
        cur = arr[0];
        best = arr[0];
        leftMin[0] = arr[0];
        for (int i = 1; i < n; i++) {
            cur = min(arr[i], cur + arr[i]);
            best = min(best, cur);
            leftMin[i] = best;
        }

        // Maximum subarray from right
        cur = arr[n - 1];
        best = arr[n - 1];
        rightMax[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            cur = max(arr[i], cur + arr[i]);
            best = max(best, cur);
            rightMax[i] = best;
        }

        // Minimum subarray from right
        cur = arr[n - 1];
        best = arr[n - 1];
        rightMin[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            cur = min(arr[i], cur + arr[i]);
            best = min(best, cur);
            rightMin[i] = best;
        }

        int ans = 0;

        for (int i = 0; i < n - 1; i++) {
            ans = max(ans, abs(leftMax[i] - rightMin[i + 1]));
            ans = max(ans, abs(leftMin[i] - rightMax[i + 1]));
        }

        return ans;
    }
};
