#pragma once
#include <iostream>
#include <vector>
using namespace std;
/*
    定义了链表结点的数据结构
    以及各种API
*/

// 【链表结构】（力扣官方定义）
class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void printList(ListNode *head);

void insertBack(ListNode *head, int num);