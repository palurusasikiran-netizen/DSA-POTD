class Solution {
public:
    int maxSumSubarray(vector<int>& arr) {

        int keep = arr[0];
        int remove = 0;

        int ans = arr[0];

        for (int i = 1; i < arr.size(); i++) {

            int newKeep = max(arr[i], keep + arr[i]);

            int newRemove = max(keep, remove + arr[i]);

            keep = newKeep;
            remove = newRemove;

            ans = max(ans, max(keep, remove));
        }

        return ans;
    }
};
