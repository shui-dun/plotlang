#include "list.h"
#include <malloc.h>

List createList() {
    List lst = (List) malloc(sizeof(ListNode));
    lst->next = NULL;
    return lst;
}

void insertList(List lst, int x, int y, int r, int g, int b) {
    List temp = lst->next;
    lst->next = (List) malloc(sizeof(ListNode));
    List cur = lst->next;
    cur->next = temp;
    cur->x = x;
    cur->y = y;
    cur->r = r;
    cur->g = g;
    cur->b = b;
}

void destroyList(List *lst) {
    List cur = *lst, pre = *lst;
    while (cur) {
        cur = cur->next;
        free(pre);
        pre = cur;
    }
    *lst = NULL;
}