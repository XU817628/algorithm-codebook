#include "../data_struct/ListNode.h"
/*
    链表双指针：合并两个有序链表
*/
class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        ListNode dummy(-1);
        ListNode *p = &dummy;
        ListNode *p1 = l1, *p2 = l2;

        if (p1->val <= p2->val)
        {
            p->next = p1;
            p = p->next;
            p1 = p1->next;
        }
        else
        {
            p->next = p2;
            p = p->next;
            p2 = p2->next;
        }

        if (p1 != nullptr)
            p->next = p1;

        if (p2 != nullptr)
            p->next = p2;

        return dummy.next;
    }
};