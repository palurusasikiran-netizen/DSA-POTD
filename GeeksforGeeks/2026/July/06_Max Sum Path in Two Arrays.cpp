class Solution {
public:
    int maxPathSum(vector<int> &a, vector<int> &b) {
        int i = 0, j = 0;
        long long sumA = 0, sumB = 0, result = 0;
        int n = a.size(), m = b.size();

        while (i < n && j < m) {
            if (a[i] < b[j]) {
                sumA += a[i++];
            } else if (a[i] > b[j]) {
                sumB += b[j++];
            } else {
                result += max(sumA, sumB) + a[i];
                sumA = 0;
                sumB = 0;
                i++;
                j++;
            }
        }

        while (i < n) sumA += a[i++];
        while (j < m) sumB += b[j++];

        result += max(sumA, sumB);
        return (int)result;
    }
};
