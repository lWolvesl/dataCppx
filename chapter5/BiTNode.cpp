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
    auto node = queue.head;
    for (int i = 0; i < queue.size; ++i) {
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

/**
 * 创建一棵节点总数为maxNode的随机树（全随机）
 * @param maxNode
 * @return
 */
BitTree CreateRandomTree(int maxNode) {
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
 * 创建一棵总节点数为maxNode的满二叉树
 * @原理：创建节点后入队，然后出队再左右节点，依次循环，类似创建一个层序遍历。
 * @param maxNode
 * @return
 */
BitTree CreateFullTree(int maxNode) {
    tLog("创建树");
    BitTree root = CreateNode(tRandom100());
    tLog(tStrCat(2, "节点 1 ", tIntToString(root->data)));
    tQueue<BitTree> queue = tCreateQueue<BitTree>();
    push(queue, root);
    for (int i = 1; i < maxNode;) {
        auto node = pop(queue);
        if (node->LNode == NULL) {
            node->LNode = CreateNode(tRandom100());
            tLog(tStrCat(4, "节点 ", tIntToString(i + 1), " ", tIntToString(node->LNode->data)));
            push(queue, node->LNode);
            i++;
        }
        if (i < maxNode && node->RNode == NULL) {
            node->RNode = CreateNode(tRandom100());
            tLog(tStrCat(4, "节点 ", tIntToString(i + 1), " ", tIntToString(node->RNode->data)));
            push(queue, node->RNode);
            i++;
        }
    }
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
    push(queue, root);
    BitTree node;
    while (!empty(queue)) {
        node = pop(queue);
        push(ret, node);
        if (node->LNode != NULL) {
            push(queue, node->LNode);
        }
        if (node->RNode != NULL) {
            push(queue, node->RNode);
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
        push(queue, node);
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
    tLog("递归式先序遍历完成");
    return queue;
}

/**
 * 非递归式先序遍历
 * @思想 可以参考代码加快理解
        先序遍历为 中->左->右 ，实现时①因为要先输出左节点，然后再遍历左节点，就可以把右节点先入栈，再把左节点入栈。
     此时栈中左节点就在右节点之上，此时再从栈取，取到的栈顶元素就是左节点，此时输出左节点值，再对左节点进行①操作，即可
     连续读取到树的最左节点，然后此时左节点下已经没有左节点，即开始读取他的右节点并执行①，当左右节点都为空时，即开始读
     他的右兄弟节点并执行①，依此逻辑，即可实现非递归式先序遍历。
 * @param node
 * @return
 */
tQueue<BitTree> PreOrder(BitTree root) {
    tQueue<BitTree> queue = tCreateQueue<BitTree>();    //初始化队列
    tStack<BitTree> stack = tCreateStack<BitTree>();    //初始化栈
    push(stack, root);                        //将跟节点放入栈中
    while (!empty(stack)) {                         //当栈不空时，代表还有节点未遍历
        TreeNode *node = pop(stack);                //节点出栈
        push(queue, node);                    //节点输出入队
        if (node->RNode != NULL) {                      //先判断是否存在右节点
            push(stack, node->RNode);         //存在即将右节点入队
        }                                               //若下面没有左节点了，即下次循环就会对右节点操作，即先序遍历右子树
        if (node->LNode != NULL) {                      //判断是否存在左节点
            push(stack, node->LNode);         //此时左节点入栈
        }                                               //下次递归这个左节点就在栈顶，然后继续对此节点向下遍历
    }
    tLog("非递归式先序遍历完成");
    return queue;
}

/**
 * 递归中序遍历核心部分
 * @param node
 * @param queue
 */
void InOrder_rf(BitTree node, tQueue<BitTree> &queue) {
    if (node != NULL) {
        InOrder_rf(node->LNode, queue);
        push(queue, node);
        InOrder_rf(node->RNode, queue);
    }
}

/**
 * 递归中序遍历
 * @param root
 * @return
 */
tQueue<BitTree> InOrder_r(BitTree root) {
    tQueue<BitTree> queue = tCreateQueue<BitTree>();
    if (root != NULL) {
        InOrder_rf(root, queue);
    }
    tLog("递归式中序遍历完成");
    return queue;
}

/**
 * 非递归实现中序遍历
 * @param root
 * @return
 */
tQueue<BitTree> InOrder(BitTree root) {
    tQueue<BitTree> queue = tCreateQueue<BitTree>();
    tStack<BitTree> stack = tCreateStack<BitTree>();
    BitTree node = root;
    while (node != NULL || !empty(stack)) {
        if (node != NULL) {
            push(stack, node);
            node = node->LNode;
        } else {
            node = pop(stack);
            push(queue, node);
            node = node->RNode;
        }
    }
    tLog("非递归式中序遍历完成");
    return queue;
}