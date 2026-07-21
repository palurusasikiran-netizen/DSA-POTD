class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();
        int ones = 0;
        int pre = INT_MIN;
        int mx = 0;

        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i])
                j++;

            int len = j - i;

            if (s[i] == '1') {
                ones += len;
            } else {
                mx = max(mx, pre + len);
                pre = len;
            }

            i = j;
        }

        return ones + mx;
    }
};
