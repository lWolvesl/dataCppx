//
// Created by wolves on 2022/3/17.
//

#include <cstdio>
#include <cstdlib>
#include <ctime>

typedef struct LNode {
    bool head = false;
    int data;
    struct LNode *next;
} LNode, *LinkNode;


bool initLinkList(LinkNode &L) {
    L = NULL;
    return true;
}

bool Empty(LinkNode &L) {
    return L == NULL;
}

void PrintNode(LNode *node) {
    printf("node{data:%d ,next:%d} ", node->data, node->next->data);
}

void PrintLinkList(LinkNode &L) {
    LinkNode node = L;
    if (L->head) {
        node = node->next;
    }
    while (node->next != NULL) {
        PrintNode(node);
        node = node->next;
    }
    printf("\n");
}

bool initLinkedList(LinkNode &L) {
    L = (LNode *) malloc(sizeof(LNode));
    if (L == NULL) {
        return false;
    }
    L->head = true;
    L->next = NULL;
    return true;
}

void LinkedListHeadInsert(LinkNode &L, LNode *Node) {
    Node->next = L->next;
    L->next = Node;
}

void ListHeadInsert(LinkNode &L, LNode *Node) {
    Node->next = L;
    L = Node;
}

void ListTailInsert(LinkNode &L, LNode *Node) {
    LinkNode head = L;
    while (head->next != NULL) {
        head = head->next;
    }
    head->next = Node;
    Node->next = NULL;
}

LNode *GetElemByValue(LinkNode &L, int x) {
    LinkNode node = L;
    while (node->data != x) {
        node = node->next;
    }
    return node;
}

LNode *GetElemByIndex(LinkNode &L, int i) {
    LinkNode node = L;
    if (i < 1) {
        return NULL;
    }
    while (node && i != 1) {
        node = node->next;
        --i;
    }
    return node;
}

bool LinkedListInsert(LinkNode &L, int i, LNode *node) {
    LNode *p = GetElemByIndex(L, i - 1);
    if (!p) {
        return false;
    }
    node->next = p->next;
    p->next = node;
    return true;
}

LNode *ListDeleteByIndex(LinkNode &L, int i) {
    LNode *p = GetElemByIndex(L, i);
    GetElemByIndex(L, i - 1)->next = p->next;
    return p;
}

int ListGetLength(LinkNode &L) {
    int length = -1;
    LinkNode node = L;
    while (node != NULL) {
        length++;
        node = node->next;
    }
    return length;
}

LinkNode createLinkedList() {
    LinkNode L;
    initLinkedList(L);
    LinkNode node = L;
    for (int i = 0; i < 10; ++i) {
        srand(time(NULL) + i);
        int rands = rand() % 10;
        LNode *p = (LNode *) malloc(sizeof(LNode *));
        p->next = NULL;
        p->data = rands;
        node->next = p;
        node = node->next;
    }
    PrintLinkList(L);
    return L;
}

LinkNode createLinkList() {
    LinkNode L;
    initLinkList(L);
    LNode *node;
    node = (LNode *) malloc(sizeof(LNode));
    node->head = false;
    srand(time(NULL) - 1);
    node->data = rand() % 10;
    L = node;
    for (int i = 0; i < 9; ++i) {
        srand(time(NULL) + i);
        int rands = rand() % 10;
        LNode *p = (LNode *) malloc(sizeof(LNode *));
        p->next = NULL;
        p->data = rands;
        node->next = p;
        node = node->next;
    }
    PrintLinkList(L);
    return L;
}

