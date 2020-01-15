/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == nullptr)
            return l2;
        if(l2 == nullptr)
            return l1;

        ListNode* pNode = nullptr;
        if(l1->val < l2->val)
        {
            pNode = l1;
            pNode->next = mergeTwoLists(l1->next, l2);
        }
        else
        {
            pNode = l2;
            pNode->next = mergeTwoLists(l1, l2->next);
        }
        return pNode;
    }
};