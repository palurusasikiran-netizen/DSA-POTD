class Solution {
public:
    long long sumAndMultiply(int n) {
        long long x = 0;
        long long sum = 0;
        string digits = to_string(n);

        for (char ch : digits) {
            int d = ch - '0';
            if (d != 0) {
                x = x * 10 + d;
                sum += d;
            }
        }

        return x * sum;
    }
};
