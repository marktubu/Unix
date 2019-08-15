#include <iostream>

using namespace std;

typedef struct node
{
    int value;
    struct node* next;
}Node;

Node* reverse_list(Node* pre_head, int k)
{
    Node* head = pre_head->next;
    if(head == NULL)
    {
        return NULL;
    }

    Node* tail = head;

    Node *tail_next = tail->next;
    
    Node* last_tail = tail;

    for(int i=0;i<k-1;++i)
    {
        if(tail != NULL)
        {
            tail = tail_next;

            if(tail != NULL)
            {
                tail_next = tail->next;
                tail->next = last_tail;
            }

            last_tail = tail;
        }
    }
    
    head->next = tail_next;
    pre_head->next = tail;
    return head;
}

void reverseKGroup(Node* head, int k)
{
    if(k <= 1)
    {
        return;
    }

    Node* pre_head = head;
    head = head->next;

    int count = 0;

    while(head != NULL)
    {
        count ++;
        if(count == k)
        {
            count = 0;

            Node* new_head = pre_head->next;

            Node* tail = new_head;

            Node *tail_next = tail->next;
            
            Node* last_tail = tail;

            for(int i=0;i<k-1;++i)
            {
                if(tail != NULL)
                {
                    tail = tail_next;

                    if(tail != NULL)
                    {
                        tail_next = tail->next;
                        tail->next = last_tail;
                    }

                    last_tail = tail;
                }
            }
            
            new_head->next = tail_next;
            pre_head->next = tail;

            pre_head = new_head;
            head = new_head->next;
        }
        else
        {
            head = head->next;
        }
    }
}

int main()
{
    Node* head = new Node();
    head->value = 0;

    int count = 16;
    int k = 3;

    Node* current = head;
    while(count > 0)
    {
        Node* node = new Node();
        node->next = NULL;
        node->value = count;
        current->next = node;
        current = node;
        count --;
    }

    reverseKGroup(head, k);
    current = head;
    while(current != NULL)
    {
        cout << "node value : " << current->value << endl;
        current = current->next;
    }
}