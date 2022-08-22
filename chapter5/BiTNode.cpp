//
// Created by wolves on 2022/8/18.
//
#include "../tools.cpp"

/**
 * 二叉树节点定义
 * 数据 data
 * 左孩子/右孩子 LNode/RNode
 */
typedef struct TreeNode {
    int data;
    struct TreeNode *LNode, *RNode;
} BiTNode;

/**
 * 打印节点值
 * @param node
 */
void visitNode(TreeNode &node) {
    tLog(node.data);
}

/**
 * 打印遍历队列
 * @param node
 */
void visitQueue(tQueue<TreeNode> queue) {
    tPrintTimeInfo();
    tDNode<TreeNode> *node = queue.head;
    while (node != NULL) {
        tPrint(node->value.data);
        tPrint(" ");
        node = node->next;
    }
    tEnter();
}

/**
 * 创建一个二叉树节点
 * @重载方法
 * @return
 */
TreeNode *CreateNode() {
    TreeNode *root = (TreeNode *) malloc(sizeof(TreeNode));
    root->LNode = NULL;
    root->RNode = NULL;
    root->data = -1;
    return root;
}

/**
 * 创建一个二叉树节点并设置data值
 * @重载方法
 * @param data
 * @return
 */
TreeNode *CreateNode(int data) {
    TreeNode *root = (TreeNode *) malloc(sizeof(TreeNode));
    root->LNode = NULL;
    root->RNode = NULL;
    root->data = data;
    return root;
}

/**
 * 创建一个二叉树节点并设置节点的全部属性
 * @重载方法
 * @param data
 * @param lNode
 * @param rNode
 * @return
 */
TreeNode *CreateNode(int data, TreeNode &lNode, TreeNode &rNode) {
    TreeNode *root = (TreeNode *) malloc(sizeof(TreeNode));
    root->LNode = &lNode;
    root->RNode = &rNode;
    root->data = data;
    return root;
}

TreeNode *CreateTree(int maxNode) {
    tLog("创建树");
    TreeNode *root = CreateNode(tRandom100());
    --maxNode;
    TreeNode *temp = root;
    tPrintTime();
    tPrintInfo();
    tPrint("根节点 ");
    tPrintln(temp->data);
    for (int i = 0; i < maxNode;) {
        if (tRandom10() % 2) {
            if (temp->LNode && tRandom10() % 2) {
                temp = temp->LNode;
                tLog("转向左子树");
            }
            if (!temp->LNode) {
                temp->LNode = CreateNode(tRandom100());
                ++i;
                tPrintTime();
                tPrintInfo();
                tPrint("左孩子 ");
                tPrintln(temp->LNode->data);
            }
        } else {
            if (temp->RNode && tRandom10() % 2) {
                temp = temp->RNode;
                tLog("转向右子树");
            }
            if (!temp->RNode) {
                temp->RNode = CreateNode(tRandom100());
                ++i;
                tPrintTime();
                tPrintInfo();
                tPrint("右孩子 ");
                tPrintln(temp->RNode->data);
            }
        }
    }
    tLog("创建完成");
    return root;
}

/**
 * 二叉树层次遍历打印节点值并返回节点队列
 * @param root
 * @return
 */
tQueue<TreeNode> LevelOrder(TreeNode &root) {
    tQueue<TreeNode> queue = tCreateQueue<TreeNode>();
    tQueue<TreeNode> ret = tCreateQueue<TreeNode>();
    tPush(queue, root);
    TreeNode node;
    while (!tEmpty(queue)) {
        node = tPop(queue);
        tPush(ret, node);
        if (node.LNode != NULL) {
            tPush(queue, *node.LNode);
        }
        if (node.RNode != NULL) {
            tPush(queue, *node.RNode);
        }
    }
    return ret;
}