

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x):val(x), next(nullptr)
    {}
};

void swap(int *a,int *b){
    int t=*a;
    *a=*b;
    *b=t;
}
struct ListNode *partion(struct ListNode *pBegin,struct ListNode *pEnd){
        if(pBegin==pEnd||pBegin->next==pEnd)    return pBegin;
        int key=pBegin->val;    //选择pBegin作为基准元素
        struct ListNode *p=pBegin,*q=pBegin;
        while(q!=pEnd){   //从pBegin开始向后进行一次遍历
            if(q->val<key){
                p=p->next;
                swap(&p->val,&q->val);
            }
            q=q->next;
        }
        swap(&p->val,&pBegin->val);
        return p;
    }

void quick_sort(struct ListNode *pBegin,struct ListNode *pEnd){
        if(pBegin==pEnd||pBegin->next==pEnd)    return;
       struct ListNode *mid=partion(pBegin,pEnd);
        quick_sort(pBegin,mid);
        quick_sort(mid->next,pEnd);
    }

struct ListNode* sortList(struct ListNode* head)
{
    if( head == NULL || head->next == NULL )
        return head;

        quick_sort(head,NULL);
        return head;
}
