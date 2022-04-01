//
// Created by wolves on 2022/4/1.
//

#include "cstdio"

#define MaxSize 3

typedef struct {
    int data[MaxSize];
    int front, rear;
    int tag;
} SqQueue;

void initSqQueue(SqQueue &Q) {
    Q.front = 0;
    Q.rear = -1;
    Q.tag = 0;
}

bool isEmpty(SqQueue &Q) {
    return (Q.rear + 1) % MaxSize == Q.front && Q.tag == 0;
}

bool push(SqQueue &Q, int x) {
    if ((Q.rear + 1) % MaxSize == Q.front && Q.tag == 1) {
        return false;
    }
    Q.rear = (Q.rear + 1) % MaxSize;
    Q.data[Q.rear] = x;
    Q.tag = 1;
    return true;
}

int pop(SqQueue &Q) {
    if (isEmpty(Q)) {
        return 100000;
    }
    Q.tag = 0;
    int x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return x;
}

void test() {
    SqQueue Q;
    initSqQueue(Q);
    printf("%d \n", isEmpty(Q));
    printf("%d \n", push(Q, 3));
    printf("%d \n", pop(Q));
    printf("%d \n", isEmpty(Q));
    printf("%d \n", push(Q, 3));
    printf("%d \n", push(Q, 3));
    printf("%d \n", push(Q, 3));
    printf("%d \n", push(Q, 3));
    printf("%d \n", isEmpty(Q));
}

