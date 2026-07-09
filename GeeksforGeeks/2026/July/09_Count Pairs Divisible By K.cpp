class Solution {
public:
    int countKdivPairs(vector<int>& arr, int k) {
        vector<long long> count(k, 0);
        for (int x : arr) {
            count[x % k]++;
        }

        long long result = 0;

        // remainder 0 pairs with itself
        result += (count[0] * (count[0] - 1)) / 2;

        // remainder r pairs with remainder k-r
        for (int r = 1; r * 2 < k; r++) {
            result += count[r] * count[k - r];
        }

        // if k is even, the middle remainder k/2 pairs with itself
        if (k % 2 == 0) {
            result += (count[k / 2] * (count[k / 2] - 1)) / 2;
        }

        return (int)result;
    }
};
