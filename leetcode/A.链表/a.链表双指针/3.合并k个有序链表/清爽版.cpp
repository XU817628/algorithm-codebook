#include "../data_struct/ListNode.h"
/*
    《合并K个有序链表》
    【题干】将K个升序链表合并为一个新的 升序 链表并返回。
    【输入】一个链表节点指针数组lists，存的元素只有————“链表的头节点指针”
    【输出】目标链表的头节点指针，指向合并后的升序链表，比如：1->1->2->3->4->4->5->6

    时间复杂度：O(NlogK)
    其中：N是所有链表中节点的总数，K是链表的数量。
    每个节点被处理一次，使用优先队列（最小堆）进行合并操作，每次插入和删除操作的时间复杂度为O(logK)。
*/

#include "../data_struct/ListNode.h"
#include <vector>
#include <queue>
/*
    《合并K个有序链表》
    -优先级队列/二叉堆
*/

// 共【4个】阶段
class Solution
{
public:
    ListNode *mergeKList(vector<ListNode *> &lists)
    {
        if (lists.empty())
            return nullptr;

        ListNode dummy(-1);
        ListNode *p = &dummy;

        auto cmp = [](ListNode *p1, ListNode *p2)
        {
            return p1->val > p2->val;
        };

        priority_queue<ListNode *, vector<ListNode *>, decltype(cmp)> pq(cmp); // 构造时，传入cmp对象

        for (ListNode *origin_head : lists)
        {
            if (origin_head != nullptr)
                pq.push(origin_head);
        }

        while (!pq.empty())
        {
            ListNode *top_node = pq.top();
            pq.pop();

            p->next = top_node;
            p = p->next;

            if (top_node->next != nullptr)
                pq.push(top_node->next);
        }

        return dummy.next;
    }
};