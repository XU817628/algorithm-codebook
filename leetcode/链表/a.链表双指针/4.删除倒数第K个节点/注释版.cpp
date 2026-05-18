#include "../data_struct/ListNode.h"
/*
    找到+删除倒数第n个节点
    
*/
class Solution
{
public:
    // 1.公有函数：“删除”倒数第n个节点
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        // 【创建虚拟头节点】
        ListNode dummy(-1);
        dummy.next = head;

        // 【找到倒数第n+1】
        ListNode *x = findNthFromEnd(&dummy, n + 1);

        // 【删除倒数第n个】
        x->next = x->next->next;

        return dummy.next;
    }

private:
    // 2.私有函数：“查找”倒数第n个节点
    ListNode *findNthFromEnd(ListNode *head, int k)
    {
        // 【阶段1：指针p1走k步】
        ListNode *p1 = head; // 创建“先行指针”p1
        // 本次用for循环：k次
        for (int i = 0; i < k; i++)
        {
            p1 = p1->next;
        }

        // 【阶段2：指针p2和p1一起走 length-k 步】
        // (p1走到尾部-nullptr)
        ListNode *p2 = head; // 创建“后行指针”p2
        // 本次用while循环：“p1走到头”
        while (p1 != nullptr)
        {
            p1 = p1->next;
            p2 = p2->next;
        }

        // 此时，p2就指向倒数第k个节点
        return p2;
    }
};