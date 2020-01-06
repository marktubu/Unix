#include <iostream>

using namespace std;

struct ListNode
{
    int value;
    ListNode* next;
};

ListNode* FindKthToTail(ListNode* phead, unsigned int k)
{
    if(phead == nullptr || k == 0)
        return nullptr;
    
    int count = 0;
    ListNode* node = phead;
    while (node != nullptr)
    { 
        node = node->next;
        ++count;

        if(count == k)
        {
            break;
        }
    }

    if(count < k)
        return nullptr;
    
    ListNode* secondNode = phead;
    while (node != nullptr)
    {
        node = node->next;
        secondNode = secondNode->next;
    }
    
    return secondNode;
}