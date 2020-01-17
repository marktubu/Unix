#include <iostream>
#include <vector>
#include <deque>

using namespace std;

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
    vector<int> PrintFromTopToBottom(TreeNode* root) {
		vector<int> ret;
		if(root == nullptr)
			return ret;
		
		std::deque<TreeNode*> dequeTreeNode;

		dequeTreeNode.push_back(root);

		while (dequeTreeNode.size() > 0)
		{
			TreeNode* node = dequeTreeNode.front();
			dequeTreeNode.pop_front();
			ret.push_back(node->val);
			if(node->left != nullptr)
				dequeTreeNode.push_back(node->left);
			if(node->right != nullptr)
				dequeTreeNode.push_back(node->right);
		}	
		
		return ret;
    }
};