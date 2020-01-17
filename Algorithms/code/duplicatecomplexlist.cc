#include <iostream>

using namespace std;

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {
    }
};

class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if(pHead == nullptr)
            return nullptr;
        
        RandomListNode* pCurrent = pHead;
        while (pCurrent != nullptr)
        {
            RandomListNode* pNext = pCurrent->next;
            RandomListNode* pRandom = pCurrent->random;

            RandomListNode* newNode = new RandomListNode(pCurrent->label);
            pCurrent->next = newNode;
            newNode->next = pNext;
            newNode->random = pRandom;

            pCurrent = pNext;
        }
        
        pCurrent = pHead;
        int count = 1;
        while (pCurrent != nullptr)
        {
            pCurrent = pCurrent->next;
            ++count;
         
            if(count % 2 == 0)
            {
                if(pCurrent != nullptr && pCurrent->random != nullptr)
                {
                    pCurrent->random = pCurrent->random->next;
                }
            }
        }
        
        pCurrent = pHead;
        RandomListNode* newList = pCurrent->next;
        RandomListNode* pNewCurrent = newList;
        while (pCurrent != nullptr && pNewCurrent != nullptr)
        {
            RandomListNode* pOldNext = pNewCurrent->next;
            if(pOldNext != nullptr)
            {
                RandomListNode* pNewNext = pOldNext->next;
                pCurrent->next = pOldNext;
                pNewCurrent->next = pNewNext;
                pCurrent = pOldNext;
                pNewCurrent = pNewNext;
            }
            else
            {
                pCurrent->next = nullptr;
                pNewCurrent->next = nullptr;
                break;
            }
            
        }
        
        return newList;
    }
};