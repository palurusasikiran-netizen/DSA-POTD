class Solution {
  public:
    int maxCharGap(string &s) {
        vector<int> first(26, -1);
        int answer = -1;

        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            if (first[c] == -1)
                first[c] = i;
            else
                answer = max(answer, i - first[c] - 1);
        }

        return answer;
    }
};
