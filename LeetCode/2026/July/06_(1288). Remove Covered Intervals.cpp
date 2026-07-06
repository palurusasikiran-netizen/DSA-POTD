class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
            if (a[0] != b[0]) return a[0] < b[0];
            return a[1] > b[1];
        });

        int count = 0, maxRight = 0;
        for (auto& interval : intervals) {
            if (interval[1] > maxRight) {
                count++;
                maxRight = interval[1];
            }
        }

        return count;
    }
};
