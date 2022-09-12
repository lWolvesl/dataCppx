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
 * 打印遍历队列
 * @重载方法
 * @param node
 */
void visitQueue(tStack<BitTree> stack) {
    tPrintTimeInfo();
    auto node = stack.node;
    for (int i = 0; i < size(stack); ++i) {
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
 * 此函数非考试需要，仅方便测试代码
 * 创建一棵节点总数为maxNode的随机树（全随机）
 * @param maxNode
 * @return
 */
BitTree CreateRandomTree(int maxNode) {
    if (maxNode == 0) {
        return BitTree{};
    }
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
 * 此函数非考试需要，仅方便测试代码
 * 创建一棵总节点数为maxNode的完全二叉树,节点值100内不重复，当节点树为 2^n - 1 个时为满二叉树
 * @原理：创建节点后入队，然后出队再左右节点，依次循环，类似创建一个层序遍历。
 * @param maxNode
 * @return
 */
BitTree CreateFullTree(int maxNode) {
    if (maxNode == 0) {
        return BitTree{};
    }
    tLog("创建树");
    BitTree root = CreateNode(tRandomNoSame());
    tLog(tStrCat(2, "节点 1 ", tIntToString(root->data)));
    tQueue<BitTree> queue = tCreateQueue<BitTree>();
    push(queue, root);
    for (int i = 1; i < maxNode;) {
        auto node = pop(queue);
        if (node->LNode == NULL) {
            node->LNode = CreateNode(tRandomNoSame());
            tLog(tStrCat(4, "节点 ", tIntToString(i + 1), " ", tIntToString(node->LNode->data)));
            push(queue, node->LNode);
            i++;
        }
        if (i < maxNode && node->RNode == NULL) {
            node->RNode = CreateNode(tRandomNoSame());
            tLog(tStrCat(4, "节点 ", tIntToString(i + 1), " ", tIntToString(node->RNode->data)));
            push(queue, node->RNode);
            i++;
        }
    }
    return root;
}

/**
 * 二叉树层次遍历，第一个队列暂存节点，第二个队列为最终返回节点
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
        先序遍历为 中->左->右 ，即为对每个节点来说，先遍历自己，再遍历其左，最后再遍历其右。
     实现时①因为要先输出左节点，然后再遍历左节点，就可以把右节点先入栈，再把左节点入栈。
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
 * @thinking 中序遍历的顺序为 左中右 ，即为对每个节点来说，先遍历其左，再遍历自己，最后再遍历其右。
 *          对于整颗树来说，第一个节点就应该是整个树的最左边的节点，第二个节点就是他的父节点
 *          然后再遍历父节点的右子树的最左边的节点，当此节点遍历完之后再向上遍历，因此实现时先找到最左节点，
 *          即一直向左孩子走，沿途的节点依次入栈，由于一直向左走，当发现自己变成空值时,栈顶的节点就是最左节
 *          点，此时栈顶出栈即为此树中序遍历第一个节点，然后从栈中再出栈，即为最左节点的父节点，也是中序遍历
 *          第二个节点，再访问此节点的右子树，重复上述过程。当右子树遍历完时，依旧是正常出栈，此时出栈的就是
 *          第二个节点的父节点，然后再其右子树遍历，直到完成遍历。
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

/**
 * @brief 递归式二叉树后序遍历核心部分
 *
 * @param node
 * @param queue
 */
void PostOrder_rf(BitTree node, tQueue<BitTree> &queue) {
    if (node != NULL) {
        PostOrder_rf(node->LNode, queue);
        PostOrder_rf(node->RNode, queue);
        push(queue, node);
    }
}

/**
 * @brief 递归式二叉树后序遍历
 *
 * @param root
 * @return tQueue<BitTree>
 */
tQueue<BitTree> PostOrder_r(BitTree root) {
    tQueue<BitTree> queue = tCreateQueue<BitTree>();
    PostOrder_rf(root, queue);
    tLog("后序遍历完成");
    return queue;
}

/**
 * @brief 非递归式后序遍历算法
 * @thinking 后序遍历顺序为 左右中 ，即为对每个节点来说，先遍历其左，再遍历其右，最后再遍历自己。
 *          对于整颗树来说，①先走到树的最左边，沿途节点依次入栈，然后当自己为空时，②栈顶节点出栈，
 *          此节点对应左右中的 左 。此出栈的节点即为最左节点，然后检查此节点的右兄弟节点，即检查目
 *          前栈顶节点的右节点，若此右节点不空，则继续执行①，即走到此子树的最左节点，然后继续执行
 *          ②，当其右兄弟节点为空时，则栈顶节点出栈，即为此节点的父节点出栈，对应左右中的 中 。
 *          依次遍历，直到整颗树结束。与前中序遍历不同的是，由于中节点在其右节点后出，因此访问到中
 *          节点时不能将其出栈，若直接判断左右是否为空将会陷入死循环，因此创建一个标记保存他，当节
 *          点出栈时，将此节点标记。当从栈顶读到的的节点的右孩子值为此节点时，表示左右均已遍历或为
 *          空即出中节点。并将节点置，这样下次遍历就会读栈顶。
 * @param root
 * @return tQueue<BitTree>
 */
tQueue<BitTree> PostOrder(BitTree root) {
    tQueue<BitTree> queue = tCreateQueue<BitTree>();
    tStack<BitTree> stack = tCreateStack<BitTree>();
    BitTree node = root;
    BitTree temp = NULL;
    while (node != NULL || !empty(stack)) {
        if (node != NULL) {
            push(stack, node);                                  //一路向左
            node = node->LNode;
        } else {
            node = peek(stack);                                 //此处读取栈顶
            if (node->RNode != NULL && node->RNode != temp) {   //判断此节点是否存在左节点并且此节点是否被读取过
                node = node->RNode;
            } else {
                node = pop(stack);                              //此时代表无右节点或右节点被读取,即出栈
                push(queue, node);
                temp = node;                                    //保存此节点表示已访问
                node = NULL;                                    //此时下轮循环便会读从栈顶出栈，然后判断右节点是否访问
            }                                                   //注意：左兄弟节点一定先于右兄弟节点出栈
        }
    }
    tLog("非递归式后遍历完成");
    return queue;
}

/**
 * @brief 释放树
 * @思路 释放树要释放完全，不能留下未引用节点造成内存泄漏，此算法采用层次遍历入栈，再依次出栈free
 * @param tree
 */
void freeTree(BitTree tree) {
    tQueue<BitTree> queue = tCreateQueue<BitTree>();
    tStack<BitTree> stack = tCreateStack<BitTree>();
    push(queue, tree);
    BitTree node;
    while (!empty(queue)) {
        node = pop(queue);
        push(stack, node);
        if (node->LNode != NULL) {
            push(queue, node->LNode);
        }
        if (node->RNode != NULL) {
            push(queue, node->RNode);
        }
    }
    while (!empty(stack)) {
        free(pop(stack));
    }
}

/**
 * @brief 寻找对于层次遍历中第i个节点
 *
 * @param index
 * @return BitTree
 */
BitTree findNode(BitTree root, int index) {
    auto queue = LevelOrder(root);
    BitTree p = root;
    for (int i = 0; i < index; i++) {
        p = pop(queue);
    }
    return p;
}

/**
 * 获取树总节点数
 * @param root
 * @return
 */
int getSize(BitTree root) {
    tQueue<BitTree> queue = LevelOrder(root);
    return queue.size;
}

/**
 * 此函数非考试需要，仅方便测试代码
 * 创建一棵二叉排序树
 * @param maxNode
 * @return
 */
BitTree CreateAVLTree(int maxNode) {
    if (maxNode == 0) {
        return BitTree{};
    }
    tLog("创建二叉排序树,以下输出为如树顺序");
    BitTree root = CreateNode(tRandomNoSame());
    tLog(root->data);
    BitTree node;
    while (maxNode) {
        node = root;
        BitTree temp = CreateNode(tRandomNoSame());
        tLog(temp->data);
        while (true) {
            if (temp->data == node->data) {
                break;
            }
            if (temp->data < node->data) {
                if (node->LNode == NULL) {
                    node->LNode = temp;
                    maxNode--;
                    break;
                }
                node = node->LNode;
            }
            if (temp->data > node->data) {
                if (node->RNode == NULL) {
                    node->RNode = temp;
                    maxNode--;
                    break;
                }
                node = node->RNode;
            }
        }
    }
    return root;
}

int getDepth(BitTree node) {                               //获取节点深度
    if (node == NULL)
        return 0;
    int Left_Depth = getDepth(node->LNode);
    int Right_Depth = getDepth(node->RNode);
    return Left_Depth > Right_Depth ? Left_Depth + 1 : Right_Depth + 1;
}