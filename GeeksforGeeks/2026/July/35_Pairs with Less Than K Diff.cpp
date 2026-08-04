class Solution {
public:
    int countPairs(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end());

        int n = arr.size();
        int left = 0, right = 1;
        int count = 0;

        while (right < n) {
            if (arr[right] - arr[left] < k) {
                count += (right - left);
                right++;
            } else {
                left++;
                if (left == right)
                    right++;
            }
        }

        return count;
    }
};
