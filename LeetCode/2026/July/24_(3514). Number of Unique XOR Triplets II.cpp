class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();

        unordered_set<int> ans;

        // Triplets with all three indices equal (or two equal)
        // produce the element itself.
        for (int x : nums)
            ans.insert(x);

        // Store all unique XORs of two different elements.
        unordered_set<int> pairXor;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                pairXor.insert(nums[i] ^ nums[j]);
            }
        }

        // Combine every pair XOR with every element.
        for (int px : pairXor) {
            for (int x : nums) {
                ans.insert(px ^ x);
            }
        }

        return ans.size();
    }
};
