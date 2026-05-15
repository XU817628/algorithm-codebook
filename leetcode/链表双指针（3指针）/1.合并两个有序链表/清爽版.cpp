#include "../data_struct/ListNode.h"
/*
    《链表双指针：合并两个有序链表》
    【题干】将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
    【输入】两个链表的头节点指针list1和list2
    【输出】目标链表的头节点指针
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