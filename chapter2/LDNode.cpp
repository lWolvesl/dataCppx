//
// Created by wolves on 2022/3/27.
//
#include "LNode.cpp"

bool IniDLNode(LinkNode &L) {
    L = (LNode *) malloc(sizeof(LNode));
    if (L == NULL){
        return false;
    }
    L->next = L;
    return true;
}