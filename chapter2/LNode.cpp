//
// Created by wolves on 2022/3/17.
//

#include <cstdio>
#include <cstdlib>

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *ListNode;

bool initLinkList(ListNode &L) {
    L = NULL;
    return true;
}

bool Empty(ListNode &L) {
    return L == NULL;
}

bool initLinkedList(ListNode &L) {
    L = (LNode *) malloc(sizeof(LNode));
    if (L == NULL) {
        return false;
    }
    L->next = NULL;
    return true;
}

