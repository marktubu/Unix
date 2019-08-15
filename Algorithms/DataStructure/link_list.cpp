#include <iostream>

using namespace std;

typedef struct node
{
    int value;
    struct node* next;
}Node;

void inverse_list_k(Node* pre_head, int k)
{
    Node* head = pre_head->next;
    if(head == nullptr)
    {
        return;
    }

    Node* tail = head;

    Node *tail_next = tail->next;
    
    Node* last_tail = tail;

    for(int i=0;i<k-1;++i)
    {
        if(tail != nullptr)
        {
            tail = tail_next;

            if(tail != nullptr)
            {
                tail_next = tail->next;
                tail->next = last_tail;
            }

            last_tail = tail;
        }
    }
    
    head->next = tail_next;
    pre_head->next = tail;
}

int inverse_list(Node* head, int k)
{
    if(k <= 1)
    {
        return 0;
    }

    if(head == nullptr)
    {
        return 0; 
    }

    Node* next = head->next;
    int count = 1 + inverse_list(next, k);

    if(count > k)
    {
        inverse_list_k(head, k);
        return 1;
    }

    return count;
}

int main()
{
    Node* head = new Node();
    head->value = 0;

    int count = 15;
    int k = 1;

    Node* current = head;
    while(count > 0)
    {
        Node* node = new Node();
        node->next = nullptr;
        node->value = count;
        current->next = node;
        current = node;
        count --;
    }

    inverse_list(head, k);

    current = head;
    while(current != nullptr)
    {
        cout << "node value : " << current->value << endl;
        current = current->next;
    }
}

