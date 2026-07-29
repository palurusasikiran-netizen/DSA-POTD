class Solution {
public:
    int minSubsets(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        int cnt = 0;

        for (int i = 0; i < arr.size(); i++) {
            if (i == 0 || arr[i] != arr[i - 1] + 1)
                cnt++;
        }

        return cnt;
    }
};
