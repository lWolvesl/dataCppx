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
} *BitTree;

/**
 * 打印节点值
 * @param node
 */
void visitNode(TreeNode &node) {
    tLog(node.data);
}

/**
 * 打印遍历队列
 * @重载方法
 * @param node
 */
void visitQueue(tQueue<BitTree> queue) {
    tPrintTimeInfo();
    tDNode<BitTree> *node = queue.head;
    while (node != nullptr) {
        tPrint(node->value->data);
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
BitTree CreateNode() {
    BitTree root = (BitTree) malloc(sizeof(BitTree));
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
BitTree CreateNode(int data) {
    TreeNode *root = (TreeNode *) malloc(sizeof(TreeNode));
    root->LNode = root->RNode = NULL;
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
BitTree CreateNode(int data, TreeNode &lNode, TreeNode &rNode) {
    BitTree root = (BitTree) malloc(sizeof(BitTree));
    root->LNode = &lNode;
    root->RNode = &rNode;
    root->data = data;
    return root;
}

BitTree CreateTree(int maxNode) {
    tLog("创建树");
    BitTree root = CreateNode(tRandom100());
    BitTree node = root;
    tLog(tStrCat(2, "根节点 ", tIntToString(node->data)));
    for (int i = 1; i < maxNode;) {
        if (tRandom100() % 2) {
            if (!node->LNode) {
                node->LNode = CreateNode(tRandom100());
                i++;
                tLog(tStrCat(2, "左节点 ", tIntToString(node->LNode->data)));
            }
            if (tRandom100() % 2) {
                node = node->LNode;
                tLog("转向左子树");
            }
        } else {
            if (!node->RNode) {
                node->RNode = CreateNode(tRandom100());
                i++;
                tLog(tStrCat(2, "右节点 ", tIntToString(node->RNode->data)));
            }
            if (tRandom100() % 2) {
                node = node->RNode;
                tLog("转向右子树");
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
tQueue<BitTree> LevelOrder(BitTree root) {
    tQueue<BitTree> queue = tCreateQueue<BitTree>();
    tQueue<BitTree> ret = tCreateQueue<BitTree>();
    tPush(queue, root);
    BitTree node;
    while (!tEmpty(queue)) {
        node = tPop(queue);
        tPush(ret, node);
        tLog(node->data);
        if (node->LNode != NULL) {
            tPush(queue, node->LNode);
        }
        if (node->RNode != NULL) {
            tPush(queue, node->RNode);
        }
    }
    tLog("完成层序遍历");
    return ret;
}

/**
 * 递归式先序遍历
 * 辅助函数
 * @param node
 * @return
 */
void PreOrder_rf(BitTree node, tQueue<BitTree> &queue) {
    if (node != NULL) {
        tPush(queue, node);
        PreOrder_rf(node->LNode, queue);
        PreOrder_rf(node->RNode, queue);
    }
}

/**
 * 递归式先序遍历
 * 主函数
 * @param node
 * @return
 */
tQueue<BitTree> PreOrder_r(BitTree node) {
    tQueue<BitTree> queue = tCreateQueue<BitTree>();
    if (node != NULL) {
        PreOrder_rf(node, queue);
    }
    return queue;
}

/**
 * 非递归式先序遍历
 * @param node
 * @return
 */
tQueue<BitTree> PreOrder(BitTree root) {
    tQueue<BitTree> queue = tCreateQueue<BitTree>();
    tStack<BitTree> stack = tCreateStack<BitTree>();
    tPush(stack, root);
    if (!tEmpty(stack)) {
        auto node = tPop(stack);
        if (node->RNode) {
            tPush(stack, node->RNode);
        }
        if (node->LNode) {
            tPush(stack, node->LNode);
        }
    }
    return queue;
}