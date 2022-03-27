//
// Created by wolves on 2022/3/27.
//
#include "cstdio"
#define MaxSize 10

typedef struct Node{
    int data;
    int next;
} SListNode[MaxSize];

void test(){
    struct Node x;
    printf("%lu\n", sizeof(x));
    struct Node a[MaxSize];
    printf("%lu\n", sizeof(a));
    SListNode b;
    printf("%lu\n", sizeof(b));
}