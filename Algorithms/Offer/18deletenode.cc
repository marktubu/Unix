#include <iostream>
using namespace std;

struct ListNode
{
    int value;
    ListNode* next;
};

void delete_node(ListNode** phead, ListNode* beDeleted)
{
    if(phead == nullptr || beDeleted == nullptr)
        return;
    
    if(beDeleted->next != nullptr)
    {
        ListNode* next = beDeleted->next;
        ListNode* nnext = beDeleted->next->next;
        beDeleted->value = next->value;
        beDeleted->next = nnext;
        delete next;
        next = nullptr;
    }
    else if(*phead == beDeleted)
    {
        delete beDeleted;
        beDeleted = nullptr;
        *phead = nullptr;
    }
    else
    {
        ListNode* node = *phead;
        while (node->next != beDeleted)
        {
            node = node->next;
        }
        
        node->next = nullptr;
        delete beDeleted;
        beDeleted = nullptr
    }
    
}