class Solution {
public:
    int getCount(int n) {

        int count = 0;
        long long twoN = 2LL * n;

        for (long long k = 2; k * (k + 1) / 2 <= n; k++) {

            if (twoN % k != 0)
                continue;

            long long temp = twoN / k - k + 1;

            if (temp > 0 && temp % 2 == 0)
                count++;
        }

        return count;
    }
};
