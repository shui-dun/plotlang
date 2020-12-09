#ifndef PLOTLANG_LIST_H

/*
 * 单链表
 */
typedef struct ListNode {
    int x; // x坐标
    int y; // y坐标
    int r; // red值
    int g; // green值
    int b; // blue值
    struct ListNode *next; // 下一个节点
} ListNode, *List;

/*
 * 创建单链表
 */
List createList();

/*
 * 在头结点后插入一个节点
 */
void insertList(List lst, int x, int y, int r, int g, int b);

/*
 * 销毁链表
 */
void destroyList(List *lst);

#define PLOTLANG_LIST_H

#endif //PLOTLANG_LIST_H
