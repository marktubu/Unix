#include <iostream>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};

class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        if(pRoot == nullptr)
            return;
        
        TreeNode* pLeft = pRoot->left;
        pRoot->left = pRoot->right;
        pRoot->right = pLeft;

        Mirror(pRoot->left);
        Mirror(pRoot->right);
    }
};