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
    ListNode* partition(ListNode* start, ListNode* end)
    {
        if(start == nullptr)
            return start;
        if(start == end)
            return start;
        
        ListNode* pivot = start;
        ListNode* pStart = start->next;
        ListNode* pEnd = pStart;
        while (pStart != nullptr && pStart->val <= pivot->val && pStart != end)
        {
            pStart = pStart->next;
        }
        pEnd = pStart;

        while (pStart != end && pEnd != end && pStart != nullptr && pEnd != nullptr)
        {
            while (pStart != nullptr && pStart->val <= pivot->val && pStart != end)
            {
                pStart = pStart->next;
            }
            //pEnd = pStart;
            while (pEnd != nullptr && pEnd->val > pivot->val && pEnd != end)
            {
                pEnd = pEnd->next;
            }
            
            if(pStart != end && pEnd != end && pStart != nullptr && pEnd != nullptr)
                swap(pStart->val, pEnd->val);
        }
        
        if(pStart != end && pStart != nullptr)
            swap(pStart->val, pivot->val);

        return pStart;
    }

    ListNode* quickSort(ListNode* start, ListNode* end)
    {
        if(start != end)
        {
            ListNode* middle = partition(start, end);
            quickSort(start, middle);
            if(middle!=nullptr)
                quickSort(middle->next, end);
        }

        return start;
    }

    ListNode* sortList(ListNode* head) {
        if(head == nullptr || head->next == nullptr)
            return head;
        else if(head->next->next == nullptr)
        {
            if(head->val > head->next->val)
            {
                swap(head->val, head->next->val);
                return head;
            }
        }

        return quickSort(head, nullptr);
    }
};