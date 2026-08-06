class Solution {
public:
    int countMinOperations(vector<int>& arr) {
        int operations = 0;

        while (true) {
            bool allZero = true;

            // Handle odd numbers (Increment operations in reverse)
            for (int i = 0; i < arr.size(); i++) {
                if (arr[i] % 2 == 1) {
                    arr[i]--;
                    operations++;
                }

                if (arr[i] != 0)
                    allZero = false;
            }

            if (allZero)
                break;

            // Divide all elements by 2 (Reverse of doubling)
            for (int i = 0; i < arr.size(); i++) {
                arr[i] /= 2;
            }

            operations++;
        }

        return operations;
    }
};
