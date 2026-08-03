class Solution {
public:
    int maxSumWithK(vector<int>& arr, int k) {
        int n = arr.size();

        // maxSum[i] = Maximum subarray sum ending at i (Kadane)
        vector<int> maxSum(n);
        maxSum[0] = arr[0];

        for (int i = 1; i < n; i++) {
            maxSum[i] = max(arr[i], maxSum[i - 1] + arr[i]);
        }

        // Sum of first window of size k
        int windowSum = 0;
        for (int i = 0; i < k; i++)
            windowSum += arr[i];

        int ans = windowSum;

        // Slide the window
        for (int i = k; i < n; i++) {
            windowSum += arr[i] - arr[i - k];

            // Subarray of exactly k elements
            ans = max(ans, windowSum);

            // Extend the window using previous maximum sum
            ans = max(ans, windowSum + maxSum[i - k]);
        }

        return ans;
    }
};
