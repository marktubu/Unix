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

    bool Equal(double param1, double param2)
    {
        if((param1 - param2 > -0.0000001) && (param1 - param2 < 0.0000001))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool DoesTree1HaveTree2(TreeNode* tree1, TreeNode* tree2)
    {
        if(tree2 == nullptr)
            return true;
        if(tree1 == nullptr)
            return false;
        
        if(Equal(tree1->val, tree2->val))
        {
            return DoesTree1HaveTree2(tree1->left, tree2->left)
                && DoesTree1HaveTree2(tree1->right, tree2->right);
        }

        return false;
    }

    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        bool result = false;

        if(pRoot1 != nullptr && pRoot2 != nullptr)
        {
            if(Equal(pRoot1->val, pRoot2->val))
            {
                result = DoesTree1HaveTree2(pRoot1, pRoot2);
            }
            if(!result)
            {
                result = HasSubtree(pRoot1->left, pRoot2)
                    || HasSubtree(pRoot1->right, pRoot2);
            }
        }
        
        return result;
    }
};