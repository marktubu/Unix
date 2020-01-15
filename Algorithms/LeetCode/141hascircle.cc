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
    bool hasCycle(ListNode *head) {
        if(head == nullptr)
            return false;
        
        ListNode* pBack = head;
        ListNode* pFront = head;

        while (pBack != nullptr && pFront != nullptr)
        {
            pBack = pBack->next;
            pFront = pFront->next;
            if(pFront != nullptr)
            {
                pFront = pFront->next;
            }
            else
            {
                return false;
            }
            if(pBack == pFront)
                return true;
        }
        
        return false;
    }
};