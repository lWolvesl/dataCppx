//
// Created by wolves on 2022/8/18.
//
#include "../tools.cpp"
typedef struct TreeNode {
    int data;
    struct TreeNode *LNode,*RNode;
}BiTNode;

void visitNode(TreeNode *node){
    printf("%d ",node->data);
}

