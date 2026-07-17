class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int maxVal = *max_element(nums.begin(), nums.end());

        // Frequency of each number
        vector<long long> freq(maxVal + 1, 0);
        for (int x : nums)
            freq[x]++;

        // Count numbers divisible by i
        vector<long long> divisible(maxVal + 1, 0);
        for (int i = 1; i <= maxVal; i++) {
            for (int j = i; j <= maxVal; j += i)
                divisible[i] += freq[j];
        }

        // exactPairs[g] = number of pairs whose gcd is exactly g
        vector<long long> exactPairs(maxVal + 1, 0);

        for (int g = maxVal; g >= 1; g--) {
            long long cnt = divisible[g];
            exactPairs[g] = cnt * (cnt - 1) / 2;

            for (int multiple = 2 * g; multiple <= maxVal; multiple += g)
                exactPairs[g] -= exactPairs[multiple];
        }

        // Prefix count of sorted gcd values
        vector<long long> prefix(maxVal + 1, 0);
        for (int i = 1; i <= maxVal; i++)
            prefix[i] = prefix[i - 1] + exactPairs[i];

        vector<int> ans;

        for (long long q : queries) {
            int l = 1, r = maxVal;

            while (l < r) {
                int mid = l + (r - l) / 2;

                if (prefix[mid] > q)
                    r = mid;
                else
                    l = mid + 1;
            }

            ans.push_back(l);
        }

        return ans;
    }
};
