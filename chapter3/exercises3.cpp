//
// Created by wolves on 2022/3/31.
//

#include "cstdio"
#include "SqStack.cpp"
#include "../chapter2/LNode.cpp"

/**
* 4
*/
bool exercises4(LinkNode &L) {
    SqStack stack;
    InitStack(stack);
    int length = GetListLength(L);
    for (int i = 0; i < (length / 2); ++i) {
        Push(stack, L->data);
        L = L->next;
    }
    if (length % 2) {
        L = L->next;
    }
    for (int i = 0; i < length / 2; ++i) {
        if (pop(stack) != L->data) {
            return false;
        }
        L = L->next;
    }
    return true;
}