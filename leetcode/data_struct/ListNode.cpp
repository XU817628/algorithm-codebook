#define _CRT_SECURE_NO_WARNINGS 1
#include "ListNode.h"

// 【遍历打印】
void printList(ListNode *head)
{
    int i = 1;
    cout << "开始遍历" << endl;
    for (ListNode *p = head; p != nullptr; p = p->next)
    {
        cout << "结点" << i << "=" << p->val << endl;
        i++;
    }
}

// 【增：尾插法】
void insertBack(ListNode *head, int val)
{
    ListNode *tail = head;
    // 遍历，找到尾结点
    while (tail->next != nullptr)
    {
        tail = tail->next;
    }
    // 尾插连招
    tail->next = new ListNode(val); // 1.挂节点
    tail = tail->next;              // 2.尾指针后移

    cout << "插入节点，val=：" << val << endl;
}

// 【删】
void deleteNode() {}