//
// Created by wolves on 2022/3/31.
//

#include "cstdio"

#define MaxSize 50

typedef struct {
    int data[MaxSize];
    int top;
} SqStack;

void InitStack(SqStack &S) {
    S.top = -1;
}

bool isEmpty(SqStack &S) {
    if (S.top == -1) {
        return true;
    }
    return false;
}

bool Push(SqStack &S, int x) {
    if (S.top == MaxSize - 1) {
        return false;
    }
    S.data[++S.top] = x;
    return true;
}

int pop(SqStack &S) {
    if (S.top == -1) {
        return false;
    }
    return S.data[S.top--];
}

int peek(SqStack &S) {
    if (S.top == -1) {
        return false;
    }
    return S.data[S.top];
}

