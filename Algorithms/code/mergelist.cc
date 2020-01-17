#include <iostream>

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if(pHead1 == nullptr)
            return pHead2;
        if(pHead2 == nullptr)
            return pHead1;
        
        ListNode* mergeNode = nullptr;
        if(pHead1->val > pHead2->val)
        {
            mergeNode = pHead2;
            mergeNode->next = Merge(pHead1, pHead2->next);
        }
        else
        {
            mergeNode = pHead1;
            mergeNode->next = Merge(pHead1->next, pHead2);
        }
        
        return mergeNode;
    }
};