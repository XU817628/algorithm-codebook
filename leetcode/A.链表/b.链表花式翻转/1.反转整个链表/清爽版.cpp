/*
    《翻转整个链表》
*/

#include "../data_struct/ListNode.h"

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (!head)
            return nullptr;

        ListNode *pre = nullptr;
        ListNode *cur = head;

        while (cur)
        {
            ListNode *tmp_next = cur->next;

            cur->next = pre;
            pre = cur;
            cur = tmp_next;
        }

        return pre;
    }
};