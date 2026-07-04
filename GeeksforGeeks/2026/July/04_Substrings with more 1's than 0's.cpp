class Solution {
public:
    int countSubstring(string& s) {
        int n = s.size();
        int size = 2 * n + 2;
        vector<int> bit(size + 1, 0);

        auto update = [&](int i) {
            for (i++; i <= size; i += i & (-i))
                bit[i]++;
        };
        auto query = [&](int i) {
            int sum = 0;
            for (i++; i > 0; i -= i & (-i))
                sum += bit[i];
            return sum;
        };

        long long answer = 0;
        int prefix = 0;
        int base = n;

        update(prefix + base);
        for (char c : s) {
            prefix += (c == '1') ? 1 : -1;
            answer += query(prefix + base - 1);
            update(prefix + base);
        }

        return (int)answer;
    }
};
