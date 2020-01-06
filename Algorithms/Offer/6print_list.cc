#include <iostream>
#include <stack>

using namespace std;

struct Node
{
    int key;
    Node* next;
};

void reverse_print(Node* head)
{
    if(head == NULL)
        return;
    reverse_print(head->next);
    cout << "print node: " << head->key << endl;
}

void reverse(Node* head)
{
    if(head == NULL)
        return;
    stack<int> m_stack;
    Node* current = head;
    while (current != NULL)
    {
        m_stack.push(current->key);
        current = current->next;
    }

    while(!m_stack.empty())
    {
        cout << "stack key: " << m_stack.top() << endl;
        m_stack.pop();
    }
}

int main()
{
    Node* head = new Node();
    head->next = NULL;
    head->key = -1;
    Node* current = head;
    for (size_t i = 0; i < 10; i++)
    {
        Node* tmpNode = new Node();
        tmpNode->key = i;
        tmpNode->next = NULL;
        current->next = tmpNode;
        current = tmpNode;
    }

    //reverse_print(head);
    reverse(head);
    
    return 0;
}