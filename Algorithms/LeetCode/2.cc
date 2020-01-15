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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(l1 == nullptr)
            return l2;
        if(l2 == nullptr)
            return l1;
        
        int increment = 0;

        ListNode* head = nullptr;
        ListNode* curnode = nullptr;
        ListNode* curnode1 = l1;
        ListNode* curnode2 = l2;

        while (curnode1 != nullptr || curnode2 != nullptr)
        {
            int curnum1 = 0;
            int curnum2 = 0;
            if(curnode1 != nullptr)
                curnum1 = curnode1->val;
            if(curnode2 != nullptr)
                curnum2 = curnode2->val;
            
            int sum = curnum1 + curnum2 + increment;
            if(sum >= 10)
            {
                sum -= 10;
                increment = 1;
            }
            else
            {
                increment = 0;
            }
            
            ListNode* node = new ListNode(sum);
            if(curnode == nullptr)
            {
                curnode = node;
                head = curnode;
            }
            else
            {
                curnode->next = node;
                curnode = node;
            }
            
            if(curnode1 != nullptr)
                curnode1 = curnode1->next;
            if(curnode2 != nullptr)
                curnode2 = curnode2->next;
        }

        if(increment > 0)
        {
            ListNode* node = new ListNode(1);
            if(curnode != nullptr)
                curnode->next = node;
        }
        return head;
    }
};