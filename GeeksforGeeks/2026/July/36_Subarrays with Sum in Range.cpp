class Solution {
public:
    long long countAtMost(vector<int>& arr, int x) {
        if (x < 0) return 0;

        int n = arr.size();
        int left = 0;
        long long count = 0;
        long long sum = 0;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            while (sum > x) {
                sum -= arr[left];
                left++;
            }

            count += (right - left + 1);
        }

        return count;
    }

    int countSubarray(vector<int>& arr, int l, int r) {
        return (int)(countAtMost(arr, r) - countAtMost(arr, l - 1));
    }
};
