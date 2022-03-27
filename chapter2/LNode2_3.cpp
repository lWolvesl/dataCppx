//
// Created by wolves on 2022/3/27.
//

#include "LNode.cpp"

void exercises1(LinkNode &L, int x) {
    LNode *node = L;
    while (node->data == x) {
        node = node->next;
        L = node;
    }
    while (node->next != NULL) {
        if (node->next->data == x) {
            node->next = node->next->next;
        }
        node = node->next;
    }
}

void exercises2(LinkNode &L, int x) {
    LNode *node = L;
    while (node->next != NULL) {
        LNode *p = node->next;
        if (p->data == x) {
            node->next = p->next;
            free(p);
        }
        node = node->next;
    }
}

void exercises3(LinkNode &L) {
    if (L->next != NULL) {
        exercises3(L->next);
    }
    printf("%d ", L->data);
}

void test() {
    //LinkNode L1 = createLinkList();
    LinkNode L2 = createLinkedList();

    //exercises1(L1, 2);
    //exercises2(L2, 2);
    exercises3(L2->next);


    printf("\n");
    //PrintLinkList(L1);
    PrintLinkList(L2);
}