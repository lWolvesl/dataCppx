#include "../chapter5/BiTNode.cpp"

//习题 二

// 3. 详见 chapter5/BiTNode.cpp 的 PostOrder 函数

/**
 * @brief 自下而上，自左至右的层次遍历算法
 * 
 * @分析 1.正常执行层序遍历。然后将队列入栈，输出栈即为从下至上，从左到右的的遍历序列。（终极取巧)
 *      2.与上述方法类似，将层序遍历的队列改为栈即可
 *      3.书目上的方法思想为每次层序遍历找最后一个节点，方法的时间复杂度为 N² ,消耗时间过高不建议采取
 */
tStack<BitTree> exercises4_1(BitTree root) {
    auto queue = LevelOrder(root);
    auto stack = tCreateStack<BitTree>();
    while (!empty(queue)) {
        push(stack, pop(queue));
    }
    return stack;
}

//测试第四题第一种方法
void run_4_1() {
    auto tree = CreateRandomTree(10);  //创建随机树
    auto queue = exercises4_1(tree);
    visitQueue(queue);
    tLog(size(queue));
}

/**
 * @brief 5.求二叉树高度,非递归
 * @thinking 1.最容易想到的就是层次遍历，但此层次遍历将每层存为一个队列，然后进入另一个大队列，
 *          最后获取到大队列的长度，就是层次遍历的长度。
 *           2.后序遍历时，树的节点会一直进栈出栈直到最低端的节点入栈再出栈，因此后序遍历时，栈
 *          最大的时候，就是树的深度
 * @注：未使用动态数组，最大节点数为100
 * @param root 
 * @return int 
 */
int exercises5_1(BitTree root) {
    if (root == NULL) {
        return 0;
    }
    BitTree node = root;
    BitTree nodes[100];
    int front = -1, rear = -1, last = 0, level = 0;
    nodes[++rear] = node;
    while (front < rear) {
        node = nodes[++front];
        if (node->LNode)
            nodes[++rear] = node->LNode;
        if (node->RNode)
            nodes[++rear] = node->RNode;
        if (front == last) {
            last = rear;
            level++;               //层次+1 
        }
    }
    return level;
}


/**
 * @brief 测试第五题第一个方法
 */
void run5_1() {
    auto tree = CreateRandomTree(10);  //创建随机树
    auto depth = exercises5_1(tree);
    tLog_f("树的深度为");
    tPrintln(depth);
}

/**
 * @brief 此为第五题的思路2，用后序遍历
 * @提示   非递归后序遍历的详细思路在 chapter5/BiTNode.cpp 中的后序遍历函数 PostOrder
 * @return int 
 */
int exercises5_2(BitTree root) {
    int level = 0;
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
                level = tMaxInt(size(stack), level);             //tMaxInt 函数在tools.cpp中
                node = pop(stack);                              //此时代表无右节点或右节点被读取,即出栈
                temp = node;                                    //保存此节点表示已访问
                node = NULL;                                    //此时下轮循环便会读从栈顶出栈，然后判断右节点是否访问
            }                                                   //注意：左兄弟节点一定先于右兄弟节点出栈
        }
    }
    tLog("非递归式后遍历完成");
    return level;
}

/**
 * @brief 测试第五题第二个方法
 */
void run5_2() {
    auto tree = CreateRandomTree(10);  //创建随机树
    auto depth = exercises5_2(tree);
    tLog_f("树的深度为");
    tPrintln(depth);
}