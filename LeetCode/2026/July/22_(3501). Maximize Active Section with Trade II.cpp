#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

// Structure to track each contiguous block of '0's
struct ZeroBlock {
    int start;
    int end;
    int length;
};

// Segment Tree for Range Maximum Query (RMQ)
class SegmentTree {
    int n;
    vector<int> tree;

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = start + (end - start) / 2;
        return max(query(2 * node, start, mid, l, r),
                   query(2 * node + 1, mid + 1, end, l, r));
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        if (n > 0) {
            tree.resize(4 * n, 0);
            build(arr, 1, 0, n - 1);
        }
    }

    int query(int l, int r) {
        if (l > r || n == 0) return 0;
        return query(1, 0, n - 1, l, r);
    }
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int total_ones = 0;
        for (char c : s) {
            if (c == '1') total_ones++;
        }

        // Step 1: Extract all global blocks of '0's
        vector<ZeroBlock> blocks;
        for (int i = 0; i < n; ) {
            if (s[i] == '0') {
                int start = i;
                while (i < n && s[i] == '0') i++;
                blocks.push_back({start, i - 1, i - start});
            } else {
                i++;
            }
        }

        int m = blocks.size();
        vector<int> pair_sums;
        if (m > 1) {
            pair_sums.resize(m - 1);
            for (int i = 0; i < m - 1; i++) {
                pair_sums[i] = blocks[i].length + blocks[i + 1].length;
            }
        }

        // Initialize Segment Tree over adjacent pair sums
        SegmentTree segTree(pair_sums);
        vector<int> ans;
        ans.reserve(queries.size());

        // Step 2: Answer each query range [l, r]
        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];

            // Find the first block that ends >= l
            int first_idx = -1;
            int low = 0, high = m - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (blocks[mid].end >= l) {
                    first_idx = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            // Find the last block that starts <= r
            int last_idx = -1;
            low = 0, high = m - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (blocks[mid].start <= r) {
                    last_idx = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            // If no zero blocks overlap with the window range
            if (first_idx == -1 || last_idx == -1 || first_idx > last_idx) {
                ans.push_back(total_ones);
                continue;
            }

            int max_gain = 0;

            // Helper lambda to get the overlapping clipped length of a block inside [l, r]
            auto get_clipped_len = [&](int idx) {
                if (idx < 0 || idx >= m) return 0;
                int overlap_start = max(blocks[idx].start, l);
                int overlap_end = min(blocks[idx].end, r);
                return max(0, overlap_end - overlap_start + 1);
            };

            // Case 1: Only 1 block falls into the window range
            if (first_idx == last_idx) {
                // With at most 1 block, no trade is possible unless it's adjacent to outside blocks
                // But the problem statement dictates the trade is made entirely within s[l...r]
                max_gain = 0; 
            } else {
                // Case 2: Pairs completely enclosed inside [l, r] (indices from first_idx to last_idx)
                // Fully enclosed pairs are from index 'first_idx + 1' to 'last_idx - 1'
                if (first_idx + 1 <= last_idx - 1) {
                    max_gain = max(max_gain, segTree.query(first_idx + 1, last_idx - 2));
                }

                // Case 3: Check combinations involving the clipped boundary blocks
                int len_first = get_clipped_len(first_idx);
                int len_first_next = get_clipped_len(first_idx + 1);
                max_gain = max(max_gain, len_first + len_first_next);

                int len_last = get_clipped_len(last_idx);
                int len_last_prev = get_clipped_len(last_idx - 1);
                max_gain = max(max_gain, len_last + len_last_prev);
            }

            ans.push_back(total_ones + max_gain);
        }

        return ans;
    }
};
