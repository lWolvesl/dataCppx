//
// Created by wolves on 2022/4/2.
//

#include "stdlib.h"

typedef struct LinkNode {
    int data;
    struct LinkNode *next;
} LinkNode;

typedef struct {
    LinkNode *front, *rear;
} LinkQueue;

void InitLinkedQueue(LinkQueue &Q) {
    Q.front = Q.rear = (LinkNode *) malloc(sizeof(LinkNode));
    Q.front->next = NULL;
}

bool LinkedQueueEmpty(LinkQueue &Q) {
    return Q.front->next == NULL;
}

void LinkedQueuePush(LinkQueue &Q, int x) {
    LinkNode *node = (LinkNode *) malloc(sizeof(LinkNode));
    node->next = NULL;
    node->data = x;
    Q.rear->next = node;
    Q.rear = node;
}

int LinkedQueuePop(LinkQueue &Q) {
    if (!LinkedQueueEmpty(Q)) {
        return -123456;
    }
    LinkNode *node = Q.front->next;
    Q.front->next = node->next;
    int x = node->data;
    if (Q.rear == node) {
        Q.rear = Q.front;
    }
    free(node);
    return x;
}