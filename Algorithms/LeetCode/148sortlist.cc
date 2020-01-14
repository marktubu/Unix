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
    ListNode* merge(ListNode* list1, ListNode* list2)
    {
        if(list1 == nullptr)
            return list2;
        if(list2 == nullptr)
            return list1;
        
        ListNode* pHead = nullptr;
        ListNode* pCurrent1 = list1;
        ListNode* pCurrent2 = list2;
        ListNode* pCurrent = nullptr;

        while (pCurrent1 != nullptr || pCurrent2 != nullptr)
        {
            if(pCurrent1 == nullptr)
            {
                pCurrent->next = pCurrent2;
                break;
            }  
            if(pCurrent2 == nullptr)
            {
                pCurrent->next = pCurrent1;
                break;
            }

            if(pCurrent1->val < pCurrent2->val)
            {
                if(pCurrent == nullptr)
                {
                    pCurrent = pCurrent1;
                    pHead = pCurrent;
                }
                else
                {
                    pCurrent->next = pCurrent1;
                    pCurrent = pCurrent->next;
                }
                
                pCurrent1 = pCurrent1->next;
            }
            else
            {
                if(pCurrent == nullptr)
                {
                    pCurrent = pCurrent2;
                    pHead = pCurrent;
                }
                else
                {
                    pCurrent->next = pCurrent2;
                    pCurrent = pCurrent->next;
                }
                
                pCurrent2 = pCurrent2->next;
            }
               
        }
        
        return pHead;
    }

    ListNode* mergeSort(ListNode* head)
    {
        if(head == nullptr || head->next == nullptr)
            return head;
        else if (!head->next->next)
        {
            if (head->val > head->next->val)
            {
                swap(head->val, head->next->val);
            }
            return head;
        }

        ListNode* fast = head;
        ListNode* slow = head;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        fast = slow->next;
        slow->next = nullptr;

        ListNode* result1 = mergeSort(head);
        ListNode* result2 = mergeSort(fast);
        ListNode* result = merge(result1, result2);
        return result;
    }

    ListNode* sortList(ListNode* head) {
        if(head == nullptr || head->next == nullptr)
            return head;
        
        return mergeSort(head);
    }
};