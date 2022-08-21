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
    tLog("根节点");
    tLog(temp->data);
    for (int i = 0; i < maxNode;) {
        if (tRandom10() % 2) {
            if (temp->LNode && tRandom10() % 2) {
                temp = temp->LNode;
                tLog("左子树");
            }
            if (!temp->LNode) {
                temp->LNode = CreateNode(tRandom100());
                ++i;
                tLog("左孩子");
                tLog(temp->LNode->data);
            }
        } else {
            if (temp->RNode && tRandom10() % 2) {
                temp = temp->RNode;
                tLog("右子树");
            }
            if (!temp->RNode) {
                temp->RNode = CreateNode(tRandom100());
                ++i;
                tLog("右孩子");
                tLog(temp->RNode->data);
            }
        }
    }
    tLog("创建完成");
    return root;
}

struct tDNodeT {
    TreeNode value;
    tDNodeT *next;
    tDNodeT *prior;
};

struct tQueueT {
    int size;
    struct tDNodeT *head, *tail;
};

tQueueT tCreateQueueT() {
    tQueueT queue;
    queue.size = 0;
    return queue;
}

/**
 * 创建双向链表节点并为value赋值
 * @重载函数
 * @param value
 * @return
 */
tDNodeT *tCreateDNodeT(TreeNode value) {
    tDNodeT *node = (tDNodeT *) malloc(sizeof(tDNodeT));
    node->value = value;
    return node;
}


/**
 * 判断队列是否为空
 * @重载函数
 * @param stack
 * @return
 */
bool tEmpty(tQueueT &queue) {
    return !queue.size;
}

void tPush(tQueueT &queue, TreeNode &value) {
    tDNodeT *node = tCreateDNodeT(value);
    if (queue.size == 0) {
        queue.head = node;
    } else {
        node->prior = queue.tail;
        queue.tail->next = node;
    }
    queue.tail = node;
    queue.size++;
}

TreeNode tPop(tQueueT &queue) {
    if (tEmpty(queue)) {
        tLog("此队列中已无数据");
        return TreeNode{};
    }
    tDNodeT *node = queue.head;
    queue.head = node->next;
    TreeNode value = node->value;
    free(node);
    queue.size--;
    if (queue.size == 0) {
        queue.tail = queue.head;
    }
    return value;
}

TreeNode tPeek(tQueueT &queue) {
    if (tEmpty(queue)) {
        tLog("此队列中已无数据");
        return TreeNode{};
    }
    return queue.head->value;
}

/**
 * 二叉树的层次遍历/层序遍历
 */
void LevelOrder(TreeNode root) {
    tQueueT queue = tCreateQueueT();
    tPush(queue, root);
    TreeNode node;
    while (!tEmpty(queue)) {
        node = tPop(queue);
        visitNode(node);
        if (node.LNode != NULL){
            tPush(queue,*node.LNode);
        }
        if (node.RNode != NULL){
            tPush(queue,*node.RNode);
        }
    }
}