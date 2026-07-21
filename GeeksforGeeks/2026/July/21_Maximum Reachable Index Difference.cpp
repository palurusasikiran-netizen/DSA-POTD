class Solution {
public:
    int maxIndexDifference(string &s) {
        int n = s.size();

        vector<int> maxEnd(26, -1);
        int ans = -1;
        bool hasA = false;

        for (int i = n - 1; i >= 0; i--) {
            int c = s[i] - 'a';
            int end = i;

            if (c < 25 && maxEnd[c + 1] != -1) {
                end = maxEnd[c + 1];
            }

            maxEnd[c] = max(maxEnd[c], end);

            if (c == 0) {
                hasA = true;
                ans = max(ans, end - i);
            }
        }

        return hasA ? ans : -1;
    }
};
