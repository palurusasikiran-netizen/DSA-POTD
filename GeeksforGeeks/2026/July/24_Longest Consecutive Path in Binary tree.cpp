/* Structure of Binary Tree Node
class Node {
  public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};
*/
class Solution {
public:
    int ans = 0;

    void dfs(Node* root, int prev, int len) {
        if (root == NULL)
            return;

        if (root->data == prev + 1)
            len++;
        else
            len = 1;

        ans = max(ans, len);

        dfs(root->left, root->data, len);
        dfs(root->right, root->data, len);
    }

    int longestConsecutive(Node* root) {
        if (root == NULL)
            return -1;

        ans = 0;
        dfs(root, root->data - 1, 0);

        return (ans > 1) ? ans : -1;
    }
};
