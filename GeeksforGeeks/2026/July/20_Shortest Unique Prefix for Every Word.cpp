class TrieNode {
public:
    TrieNode* child[26];
    int count;

    TrieNode() {
        count = 0;
        for (int i = 0; i < 26; i++)
            child[i] = NULL;
    }
};

class Solution {
public:
    vector<string> findPrefixes(vector<string>& arr) {

        TrieNode* root = new TrieNode();

        // Insert all words into Trie
        for (string word : arr) {
            TrieNode* curr = root;

            for (char ch : word) {
                int index = ch - 'a';

                if (curr->child[index] == NULL)
                    curr->child[index] = new TrieNode();

                curr = curr->child[index];
                curr->count++;
            }
        }

        vector<string> ans;

        // Find shortest unique prefix
        for (string word : arr) {
            TrieNode* curr = root;
            string prefix = "";

            for (char ch : word) {
                int index = ch - 'a';

                curr = curr->child[index];
                prefix += ch;

                if (curr->count == 1)
                    break;
            }

            ans.push_back(prefix);
        }

        return ans;
    }
};
