//
// Created by wolves on 2022/3/24.
//

typedef struct DNode {
    int data;
    struct DNode *prior, *next;
} DNode, *DLinkNode;