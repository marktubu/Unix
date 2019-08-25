#include <iostream>

using namespace std;

#define KEY(node) (node->key)
#define GET(pptr) (*pptr)
#define ADDR(ptr) (&ptr)

//efine nullptr NULL

typedef struct node
{
    int key;
    struct node* parent;
    struct node* left;
    struct node* right;
    int data;
} Node;

Node* search(Node* node, int key)
{
    Node* current = node;
    while (current != nullptr)
    {
        if(KEY(current) == key)
        {
            return current;
        }
        else if(KEY(current) < key)
        {
            current = current->right;
        }
        else 
        {
            current = current->left;
        }
    }

    return current;
}

Node* tree_minimum(Node* node)
{
    Node* current = node;
    Node* ret = nullptr;
    while(current != nullptr)
    {
        ret = current;
        current = current->left;
    }

    return ret;
}

Node* tree_maximum(Node* node)
{
    Node* current = node;
    Node* ret = nullptr;
    while (current != nullptr)
    {
        ret = current;
        current = current->right;
    }
    
    return ret;
}

//中序遍历情况下的前驱
//找出小于node的key值de所有节点中key值最大的节点最为前驱
Node* tree_presuccessor(Node* node)
{
    if(node == nullptr)
        return nullptr;

    if(node->left != nullptr)
        return tree_maximum(node->left);
    
    Node* current = node;
    Node* parent = current->parent;

    while(parent != nullptr && current == parent->left)
    {
        current = parent;
        parent = parent->parent;
    }

    return parent;
}

//中序遍历情况下的后驱
//如果node为树最右的叶子节点，则返回为nullptr
//中序遍历时该节点为最后一个节点，所以没有后驱
Node* tree_successor(Node* node)
{
    if(node == nullptr)
        return nullptr;

    if(node->right != nullptr)
        return tree_minimum(node->right);
    
    Node* current = node;
    Node* parent = current->parent;
    while(parent != nullptr && current == parent->right)
    {
        current = parent;
        parent = parent->parent;
    }

    return parent;
}

void insert(Node** root, Node* node)
{
    Node** current = root;
    Node* parent = nullptr;
    int key = KEY(node);

    while (GET(current) != nullptr)
    {
        parent = GET(current);
        if(KEY(GET(current)) > key)
        {
            current = ADDR(GET(current)->left);
        }
        else
        {
            current = ADDR(GET(current)->right);
        }
    }
    
    GET(current) = node;
    node->parent = parent;
}

void transplant(Node** root, Node* u, Node* v)
{
    if(u->parent == nullptr)
    {
        GET(root) = v;
    }
    else if(u->parent->left == u)
    {
        u->parent->left = v;
    }
    else if(u->parent->right == u)
    {
        u->parent->right = v;
    }

    if(v != nullptr)
    {
        v->parent = u->parent;
    }
}

void remove_child(Node* child)
{
    if(child == nullptr)
        return;
    
    Node* parent = child->parent;

    if(parent != nullptr)
    {
        if(parent->left == child)
        {
            parent->left = nullptr;
        }
        else if(parent->right == child)
        {
            parent->right = nullptr;
        }
    }

    delete child;
}

void remove(Node** root, int key)
{
    Node* result = search(GET(root), key);
    if(result == nullptr)
        return;
    
    if(result->left == nullptr)
    {
        transplant(root, result, result->right);
    }
    else if(result->right == nullptr)
    {
        transplant(root, result, result->left);
    }
    else
    {
        Node* successor = tree_successor(result);
        if(successor->parent != result)
        {
            transplant(root, successor, successor->right);
            successor->right = result->right;
            successor->right->parent = successor;
        }
        transplant(root, result, successor);
        successor->left = result->left;
        successor->left->parent = successor;
    }
    
}

void inorder_iterate(Node* node)
{

}

void inorder(Node* node)
{
    Node* current = node;
    if (current != nullptr)
    {
        inorder(current->left);
        cout << "key is : " << KEY(current) << endl;
        inorder(current->right); 
    }
}

int main()
{
    Node* proot = nullptr;
    Node** pproot = &proot;

    for (size_t i = 5; i < 10; i++)
    {
        //Node node = {i+5, nullptr, nullptr, nullptr, i};
        Node* node = new Node();
        node->key = i+5;
        node->data = i;
        insert(pproot, node); 
    }

    for (size_t i = 0; i < 5; i++)
    {
        //Node node = {i+5, nullptr, nullptr, nullptr, i};
        Node* node = new Node();
        node->key = i+5;
        node->data = i;
        insert(pproot, node); 
    }

    Node* current = proot;
    while (current != nullptr)
    {
        cout<< "left current is : " << KEY(current) <<endl;
        current = current->left;
    }

    current = proot;
    while (current != nullptr)
    {
        cout<< "right current is : " << KEY(current) <<endl;
        current = current->right;
    }

    inorder(proot);
    
    Node* ret = search(proot, 12);
    if(ret != nullptr)
    {
        cout<<"search result : key "<< ret->key <<" data : " << ret->data << endl;
        inorder(ret);
    }
    else
    {
        cout << "key not found : " << 12 << endl;
    }

    ret = search(proot, 122);
    if(ret != nullptr)
    {
        cout<<"search result : key "<< ret->key <<" data : " << ret->data << endl;
    }
    else
    {
        cout << "key not found : " << 122 << endl;
    }
    
    
    return 0;
}