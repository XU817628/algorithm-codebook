/*
    《翻转整个链表》
*/

#include "../data_struct/ListNode.h"

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        // 边界处理：如果是空链表，直接返回
        if (head == nullptr)
            return head;

        // 双指针初始化
        ListNode *pre = nullptr; // “前指针”pre，初始指向nullptr（头节点前一个为空）
        ListNode *cur = head;    // “当前指针”cur，初始指向head

        // 开始循环
        while (cur)
        {
            // 1.临时指针：存cur的next
            ListNode *tmp_next = cur->next;

            // 2.指针重定向：让当前节点指向上一个节点
            cur->next = pre;

            // 3.指针后移：双指针统一后移1位，下一次再循环
            pre = cur;
            cur = tmp_next;
        }

        return pre; // 此时的pre，就是链表的头节点
    }
};
