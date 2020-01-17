#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr)
    {}
};

struct Compare
{
    bool operator()(struct ListNode* node1, struct ListNode* node2) const
    {
        if(node1 == nullptr || node2 == nullptr)
            return false;
        return node1->val > node2->val;
    }
};

typedef multiset<struct ListNode*, Compare> MySet;

ListNode* mergeKLists(vector<ListNode*> lists)
{
    ListNode* head = nullptr;
    int length = lists.size();
    if(length == 0)
        return head;

    priority_queue <pair<int,ListNode*>, vector<pair<int,ListNode*>>, greater<pair<int,ListNode*>>> pq;
    for (size_t i = 0; i < length; i++)
    {
        if(lists[i] != nullptr)
            pq.push({lists[i]->val, lists[i]});
    }
    
    struct ListNode* curNode = nullptr;
    while (pq.size() > 0)    
    {
        pair<int, ListNode*> pr = pq.top();
        pq.pop();
        ListNode* node = pr.second;

        if(node != nullptr)
        {
            ListNode* next = node->next;
            if(next != nullptr)
            {
                pq.push({next->val, next});
            }
            if(curNode == nullptr)
            {
                curNode = node;
                head = curNode;
            }
            else
            {
                curNode->next = node;
                curNode = node;
            }
        } 
    }
    
    return head;
}


int main()
{
    ListNode* head1 = new ListNode(1);
    ListNode* node1 = new ListNode(4);
    ListNode* node2 = new ListNode(5);

    head1->next = node1;
    node1->next = node2;

    ListNode* head2 = new ListNode(1);
    ListNode* node3 = new ListNode(3);
    ListNode* node4 = new ListNode(4);

    head2->next = node3;
    node3->next = node4;

    ListNode* head3 = new ListNode(2);
    ListNode* node5 = new ListNode(6);

    head3->next = node5;

    vector<ListNode*> lists;
    lists.push_back(head1);
    lists.push_back(head2);
    lists.push_back(head3);

    ListNode* head = mergeKLists(lists);

    while (head != nullptr)
    {
        cout << "node " << head->val << endl;
        head = head->next;
    }
    

    return 0;
}