#include "../data_struct/ListNode.h"
/*
    链表双指针：合并两个有序链表
*/

// 共【4个】阶段
class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        // 【阶段一：创建1+2个指针】
        ListNode dummy(-1);          // 创建虚拟头节点（构造目标链表）
        ListNode *p = &dummy;        // 1个"目标链表-构造指针"
        ListNode *p1 = l1, *p2 = l2; // 2个"已有链表-游走指针"

        // 【阶段二：挂节点】
        // while循环何时结束：当p1/p2其中一个为空时，说明有一条链表的节点已经处理完了

        while (p1 != nullptr && p2 != nullptr)
        {
            if (p1->val <= p2->val) // 比大小：若“L1节点 ≤ L2节点”，就把L1节点挂上
            {
                // 前两行：利用构造指针p挂节点，构造新链表
                p->next = p1; // 连招1：挂节点
                p = p->next;  // 连招2：指针后移

                // 第三行：挂完这个节点后，p1向后游走，再往后走一个节点
                p1 = p1->next; //
            }
            else
            {
                p->next = p2;
                p = p->next;
                p2 = p2->next;
            }
        }
        // 【阶段三：收尾工作】
        // 把最后一个节点处理掉：
        // -谁不为空，就说明哪条链表还有剩余———整条直接挂上即可（本来就是有序的）

        if (p1 != nullptr)
            p->next = p1;

        if (p2 != nullptr)
            p->next = p2;

        // 【阶段四：返回新链表】
        // 即：返回新链表的第一个节点（dummy后一个节点）
        return dummy.next;
    }
};