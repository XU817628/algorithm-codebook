#include "../data_struct/ListNode.h"
#include <vector>
#include <queue>
/*
    《合并K个有序链表》
    -优先级队列/二叉堆
    ?【历史最佳】12min09s
*/

// 共【4个】阶段
class Solution
{
public:
    ListNode *mergeKList(vector<ListNode *> &lists)
    {
        // 边界检查：若链表数组为空，直接返回空指针
        if (lists.empty())
            return nullptr;

        // 【阶段一：准备阶段】
        ListNode dummy(-1);   // 创建虚拟头节点
        ListNode *p = &dummy; // 创建"目标链表"指针p

        // 【阶段二；定义优先级队列（小顶堆）】
        // 自定义比较器(lambda)：按节点值构建"小顶堆"
        auto cmp = [](ListNode *p1, ListNode *p2)
        {
            return p1->val > p2->val; // 大的节点往后走，小的节点浮上来———小顶堆
        };
        // 定义优先级队列/小顶堆-pq
        // [priority_queue的模板参数]
        // 1. 元素类型 ListNode*
        // 2. 底层容器 vector<ListNode*>
        // 3. 比较器"类型" decltype(cmp)
        priority_queue<ListNode *, vector<ListNode *>, decltype(cmp)> pq(cmp); // 构造时，传入cmp对象

        // 【阶段三：小顶堆初始化（头节点入堆）】
        for (ListNode *origin_head : lists) // 将k个链表"最初的头节点"放入最小堆
        {
            if (origin_head != nullptr)
                pq.push(origin_head);
        }

        // 【阶段四：正式构造目标链表】（比较节点大小，循环挂节点）
        while (!pq.empty())
        {
            // 1.弹出堆顶：取出堆顶的节点
            ListNode *top_node = pq.top(); // 用临时变量接收堆顶节点，可读性好
            pq.pop();                      // 弹出堆顶节点（pop只做删除，返回void）

            // 2.挂节点：用p挂到目标链表尾部
            p->next = top_node;
            p = p->next;

            // 3.补货：如果这个堆顶节点，对应链表后续还有节点，就把后一个"补进堆中"，参加后续比较
            if (top_node->next != nullptr)
                pq.push(top_node->next);
        }

        return dummy.next;
    }
};