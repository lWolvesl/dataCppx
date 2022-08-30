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

/**
 * 6.先序+中序构成数，数字不重复，递归算法, 暂为用非递归实现成功，与书上一致使用递归算法
 * @思想  先序加中序构成树，可以①从根节点拆分为两棵子树，每棵子树的根节点，即为大树根节点的左右
 *      孩子，再对左右两子树分别进行①操作，即可确定每棵子树的左右孩子节点，直到拆分两颗子树的节
 *      点序列长度为0时，代表无左右孩子，即可生成题意所求树。
 *
 * @param queue1 先序遍历序列（数组）
 * @param queue2 中序遍历序列（数组）
 * @param preStart 该子树先序遍历开始节点下标
 * @param perEnd 该子树先序遍历结束节点下标
 * @param inStart 该子树中序遍历开始节点下标
 * @param inEnd 该子树中序遍历结束节点下标
 * @return
 */
BitTree PreInCreat(int queue1[], int queue2[], int preStart, int perEnd, int inStart, int inEnd) {
    BitTree root = CreateNode(queue1[preStart]);
    int i;
    for (i = inStart; queue2[i] != root->data; ++i) {}     //在中序找到前序遍历中的第一个节点值所在的下标，通过此下标拆分两棵子树
    int LLength = i - inStart;
    int RLength = inEnd - i;
    if (LLength != 0) {                                    //若左边没有节点，即表示该树的左节点为空，否则就是左子树的根节点
        root->LNode = PreInCreat(queue1, queue2, preStart + 1,
                                 preStart + LLength, inStart, inStart + LLength - 1);
        //参数说明：左子树的先序范围就是去除根节点加上左子树长度
        //        左子树的中序范围就是去除根节点，然后从开始下标加长度
    } else {
        root->LNode = NULL;
    }
    if (RLength != 0) {                                    //若右边没有节点，即表示该树的右节点为空，否则就是右子树的根节点
        root->RNode = PreInCreat(queue1, queue2,
                                 perEnd - RLength + 1, perEnd, inEnd - RLength + 1, inEnd);
        //参数说明：右子树的先序范围就是左子树先序结束的地方的下一个开始，到结束
        //        左子树的中序范围就是去除根节点，然后从根节点的下一个开始到结束
    } else {
        root->RNode = NULL;
    }
    return root;
}

/**
 * 转换函数，将传进来的队列转换为数组，方便读取。
 * @param queue_Pre
 * @param queue_In
 * @return
 */
BitTree exercises6(tQueue<BitTree> queue_Pre, tQueue<BitTree> queue_In) {
    int length = size(queue_In);
    int queue1[length];
    int queue2[length];
    for (int i = 0; i < length; ++i) {
        queue1[i] = pop(queue_Pre)->data;
        push(queue_Pre, CreateNode(queue1[i]));          //保证队列不变
    }
    for (int i = 0; i < length; ++i) {
        queue2[i] = pop(queue_In)->data;
        push(queue_In, CreateNode(queue2[i]));
    }                                                                   //转换完成 前序 queue1 中序 queue2
    return PreInCreat(queue1, queue2, 0, 9, 0, 9);
}

// 测试第六题
void run6() {
    BitTree pNode = CreateFullTree(10);
    visitQueue(LevelOrder(pNode));
    visitQueue(PreOrder(pNode));
    visitQueue(InOrder(pNode));
    visitQueue(LevelOrder(exercises6(PreOrder(pNode), InOrder(pNode))));
}

/**
 * 7.判断是否为完全二叉树
 * @思路  1.首先空树符合完全二叉树定义，因此空树是完全二叉树/满二叉树
 *       2.由于完全二叉树除了最后一层的节点数量不固定，上层的节点数均为 2^(n-1) 个节点，因此采用层次遍历，将每一层的节点固定存入为队列
 *          若队列的值不符合标准值，直接判断非完全二叉树
 *       3.对于最后一层，遍历时要求从左到右不能间断，因此在取出倒数第二层的节点遍历最后一层时，先获取最后一层的总数，再对遍历倒数第二层，
 *          判断最后一层是否连续，即判断间断节点的节点是否为最后一个节点，若是最后一个节点，则为完全二叉树，若不是，则不是完全二叉树
 *       综上所述，只要遇到空节点，就判断其后是否还存在非空节点，若有则不是完全二叉树，若无则为完全二叉树
 * @param root
 * @return
 */
bool exercises7(BitTree root) {
    if (root == NULL) {
        return true;                                    //空树为满二叉树
    }
    tQueue<BitTree> queue = tCreateQueue<BitTree>();    //层序遍历所用队列
    push(queue,root);                         //根节点首先入队
    while (!empty(queue)){                          //此处判断队列是否为空
        BitTree temp = pop(queue);                  //队首出队
        if (temp != NULL){                              //此处节点不为空
            push(queue,temp->LNode);          //此处对于节点入队不判断是否为空
            push(queue,temp->RNode);            //为后序判断树中是否有空节点留下伏笔
        }else{                                          //此处发现一个空节点，开始判断后序是否还有节点，由于前面一定没有空节点
            while (!empty(queue)){                  //立刻开始从队列出队
                temp = pop(queue);
                if (temp != NULL){                     //此时队列中的节点均为此空节点后面的节点
                    return false;                      //对剩下队列的节点判断，若出现非空节点，则说明后序节点有值，不为满二叉
                }
            }
        }
    }
    return true;
}

void run7(){
    BitTree pNode = CreateFullTree(10);
    tLog(exercises7(pNode));                //bool转int 默认即为 true/false = 1/0
}

