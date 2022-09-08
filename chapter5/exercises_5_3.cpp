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
    push(queue, root);                         //根节点首先入队
    while (!empty(queue)) {                          //此处判断队列是否为空
        BitTree temp = pop(queue);                  //队首出队
        if (temp != NULL) {                              //此处节点不为空
            push(queue, temp->LNode);          //此处对于节点入队不判断是否为空
            push(queue, temp->RNode);            //为后序判断树中是否有空节点留下伏笔
        } else {                                          //此处发现一个空节点，开始判断后序是否还有节点，由于前面一定没有空节点
            while (!empty(queue)) {                  //立刻开始从队列出队
                temp = pop(queue);
                if (temp != NULL) {                     //此时队列中的节点均为此空节点后面的节点
                    return false;                      //对剩下队列的节点判断，若出现非空节点，则说明后序节点有值，不为满二叉
                }
            }
        }
    }
    return true;
}

// 第七题测试
void run7() {
    BitTree pNode = CreateFullTree(10);
    tLog(exercises7(pNode));                //bool转int 默认即为 true/false = 1/0
}

/**
 * @brief 统计所有双分支节点个数，即统计同时含有左孩子和右孩子的节点的个数。
 *
 * @思想  使用层次遍历/先序/中序/后序，遍历每一个节点是否同时含有左右孩子，若含有则总个数+1
 *       由于要判断同时含有左右孩子节点的节点个数，设置一个标志值，每次发现有左/右孩子时就将该标志+1，
 *       每个节点遍历完时判断tag是否加了两次即为2，若为2则将总数加一。
 * @param root
 * @return int
 */
int exercise8(BitTree root) {
    tQueue<BitTree> queue = tCreateQueue<BitTree>();  //层序遍历所用队列
    int tag = 0;                                      //标志值
    int count = 0;                                    //双分支节点个数
    push(queue, root);
    while (!empty(queue)) {
        BitTree node = pop(queue);
        if (node->LNode) {
            tag++;                                    //存在左节点，标志值+1
            push(queue, node->LNode);
        }
        if (node->RNode) {
            tag++;                                    //存在右节点，标志值+1
            push(queue, node->RNode);
        }
        if (tag == 2) {
            count++;                                  //标志为2，代表含双分支
        }
        tag = 0;
    }
    return count;
}

//测试第八题
void run8() {
    auto root = CreateFullTree(10);
    tLog(exercise8(root));
}

/**
 * @brief 9.交换各个节点的左右子树，即交换各个节点的左右孩子节点
 *
 * @思路 使用层序/先序/中序/后序遍历树，并在遍历到每个节点时交换左右孩子节点
 *
 * @param root
 * @return BitTree
 */
BitTree exercises9(BitTree root) {
    tQueue<BitTree> queue = tCreateQueue<BitTree>();  //层序遍历所用队列
    push(queue, root);
    while (!empty(queue)) {
        BitTree node = pop(queue);
        BitTree temp = node->LNode;                   //此下三行为交换孩子节点
        node->LNode = node->RNode;
        node->RNode = temp;
        if (node->LNode) {
            push(queue, node->LNode);
        }
        if (node->RNode) {
            push(queue, node->RNode);
        }
    }
    return root;
}

// 测试第九题
void run9() {
    auto root = CreateFullTree(10);
    visitQueue(LevelOrder(root));
    exercises9(root);
    visitQueue(LevelOrder(root));
}

/**
 * @brief 10.求先序遍历中第k个节点的值
 *
 * @思想 在先序遍历中加入判断当前进行的是第几个节点的遍历，若等于k则输出此节点的值
 *
 * @param root
 * @param k
 * @return int
 */
int exercises10(BitTree root, int k) {
    if (k == 1) {                                    //若k = 1，即代表先序遍历的第一个节点（根节点）为所求节点,即无需进入方法
        return root->data;
    }
    tQueue<BitTree> queue = tCreateQueue<BitTree>();    //初始化队列
    tStack<BitTree> stack = tCreateStack<BitTree>();    //初始化栈
    push(stack, root);                        //将跟节点放入栈中
    int index = 1;
    while (!empty(stack)) {                         //当栈不空时，代表还有节点未遍历
        TreeNode *node = pop(stack);                //节点出栈
        if (k == index++) {
            return node->data;
        }
        push(queue, node);                    //节点输出入队
        if (node->RNode != NULL) {                      //先判断是否存在右节点
            push(stack, node->RNode);         //存在即将右节点入队
        }                                               //若下面没有左节点了，即下次循环就会对右节点操作，即先序遍历右子树
        if (node->LNode != NULL) {                      //判断是否存在左节点
            push(stack, node->LNode);         //此时左节点入栈
        }                                               //下次递归这个左节点就在栈顶，然后继续对此节点向下遍历
    }
    tLog("非递归式先序遍历完成");
    return -1;
}

//测试第十题
void run10() {
    auto root = CreateFullTree(10);
    visitQueue(PreOrder(root));
    tLog(exercises10(root, 7));
}

/**
 * @brief 11.删除数中所有值为x的节点的子树。
 *
 * @思想  首先要遍历数查看节点值，即在层序/先序/中序/后序遍历中选取遍历方法，对于此题来说
 *       未避免出现空指针或访问空内存的情况，先序/中序/后序遍历过程中删除子树都可能会造成
 *       这种情况，而对于层序遍历自上而下，从左到右的遍历，就不会出现上述问题，因此我采用
 *       非递归式层序遍历完成。
 *       具体实现就是层序遍历判断值，然后发现值为x时暂停遍历，转而释放左右孩子，然后继续执
 *       行遍历，直至完成层序遍历。
 * @freeTree  此方法为 chapter5/BiTNode.cpp 文件中的 freeTree 方法，作用为释放树。
 * @return BitTree
 */
BitTree exercises11(BitTree root, int x) {
    tQueue<BitTree> queue = tCreateQueue<BitTree>();  //层序遍历所用队列
    push(queue, root);
    while (!empty(queue)) {
        BitTree node = pop(queue);
        if (node->data == x) {                          //发现值为x的节点
            freeTree(node->LNode);                    //释放其左孩子
            freeTree(node->RNode);                    //释放其右孩子
            node->LNode = NULL;                       //将左孩子引用置空
            node->RNode = NULL;                       //将有孩子引用置空
        }
        if (node->LNode) {
            push(queue, node->LNode);
        }
        if (node->RNode) {
            push(queue, node->RNode);
        }
    }
    return root;
}


//测试第11题
void run11() {
    auto root = CreateFullTree(10);
    visitQueue(LevelOrder(root));
    exercises11(root, 62);
    visitQueue(LevelOrder(root));
}

/**
 * @brief 12.打印值为x的节点的所有祖先
 *
 * @思路 首先遍历节点，即在层序/先序/中序/后序遍历中选取遍历方法，当找到值为x的节点时，
 *      层序遍历队列保存的是是x之前的节点，不符合，先序遍历栈中保存的是其上所有节点的
 *      兄弟节点，不符合，中序遍历情况分两种，第一种是最开始遍历的左枝节点，栈中保存的
 *      确实是其祖先节点，但一旦遍历右枝时，右枝的父节点必出栈，不符合。对于后序遍历，
 *      找到目标节点时，栈中储存的就是所有的父节点（遍历左节点即为其所有祖先节点，遍历
 *      右节点的时候由于后序 左->右->中 ，栈中必无左兄弟节点，只剩所有的祖先节点。
 *
 * @param root
 * @return tQueue<BitTree>
 */
tQueue<BitTree> exercise12(BitTree root, int x) {
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
                if (node->data == x) {                           //判断节点值是否为 x
                    break;                                      //结束遍历
                }

                temp = node;                                    //保存此节点表示已访问
                node = NULL;                                    //此时下轮循环便会读从栈顶出栈，然后判断右节点是否访问
            }                                                   //注意：左兄弟节点一定先于右兄弟节点出栈
        }
    }                                                           //为了从根节点开始输出以便观察，因此将栈倒置再入队
    tStack<BitTree> stacks = tCreateStack<BitTree>();           //将栈倒置
    while (!empty(stack)) {
        push(stacks, pop(stack));
    }
    tQueue<BitTree> queue = tCreateQueue<BitTree>();            //入队输出
    while (!empty(stacks)) {
        push(queue, pop(stacks));
    }
    return queue;
}

//测试第十二题
void run12() {
    auto root = CreateFullTree(10);
    visitQueue(LevelOrder(root));
    visitQueue(exercise12(root, 25));
}

/**
 * @brief 13.寻找最近共同父节点。
 *
 * @思路  由于第十二题提供了为节点寻找父节点的方法，此题不难想到寻找祖先节点序列，
 *       然后对序例进行对比，找到最长的共同点，即为最近的共同父节点。
 *       由于要调用十二题的方法，因此此处算法的前 2 行为处理传参，不为核心算法。
 * @param root
 * @param p
 * @param q
 * @return BitTree
 */
BitTree exercise13(BitTree root, BitTree p, BitTree q) {
    int x = p->data;
    int y = p->data;
    /* 获取每个节点的所有祖先节点序列 */
    tQueue<BitTree> queue1 = exercise12(root, x);
    tQueue<BitTree> queue2 = exercise12(root, y);
    /* 开始比较队列 */
    int Size = tMinInt(size(queue1), size(queue2));          //此处选择较短队列是为了防止比较时出现空引用
    BitTree node = root;
    for (int i = 0; i < Size; i++) {                         //开始比较祖先队列
        BitTree temp = pop(queue1);
        if (temp == pop(queue2)) {
            node = temp;
        } else {
            break;
        }
    }
    return node;
}

//测试第十三题
void run13() {
    auto root = CreateFullTree(10);
    visitQueue(LevelOrder(root));
    BitTree p = findNode(root, 4);
    tLog(p->data);
    BitTree q = findNode(root, 5);
    tLog(q->data);
    tEnter();
    tLog(exercise13(root, p, q)->data);
}

/**
 * @brief 14.求树的宽度，即最宽的一层的宽度
 *
 * @思想  求最宽的树的宽度，不难想到遍历算法中的层序遍历，每次遍历一层，
 *       然后求最宽的一层即为所求答案。
 *
 * @param root
 * @return int
 */
int exercises14(BitTree root) {
    if (root == NULL) {
        return 0;
    }
    int width = 0;
    tQueue<tQueue<BitTree>> queues = tCreateQueue<tQueue<BitTree>>();
    tQueue<BitTree> roots = tCreateQueue<BitTree>();
    /* 先把root入栈 */
    push(roots, root);
    push(queues, roots);
    width = tMaxInt(width, size(roots));
    while (!empty(queues)) {                                     //开始对每一层遍历
        tQueue<BitTree> queue = pop(queues);
        tQueue<BitTree> queuex = tCreateQueue<BitTree>();
        while (!empty(queue)) {
            BitTree node = pop(queue);
            if (node->LNode) {
                push(queuex, node->LNode);
            }
            if (node->RNode) {
                push(queuex, node->RNode);
            }
        }
        if (size(queuex)) {                                      //防止无效操作以及防止无限循环
            push(queues, queuex);
            width = tMaxInt(width, size(queuex));
        }
    }
    return width;
}

//测试第十四题
void run14() {
    auto root = CreateFullTree(14);
    tLog(exercises14(root));
}

/**
 * * @brief 15.已知满二叉树的先序遍历，求其后续遍历
 *
 * @思想  首先，满二叉树满足节点总数为 2^n - 1,n为层数
 *       对于每个节点的左右子树的节点总个数一定相同
 *
 *   eg                 14
 *                   /      \
 *                  47       32
 *                /    \   /    \
 *               18    51 36    22
 *
 *   其先序遍历为  14 47 18 51 32 36 22
 *   其后续遍历为  18 51 47 36 22 32 14
 *
 *          首先，对于整颗树，其先序遍历的第一个节点一定是最后一个
 *      节点即将第一个节点移动到最后一个节点，而又由于先序为中左右，
 *      后序为左右中，可知其左右顺序不变，又因为满二叉树的每个节点
 *      的左右子树节点数相同，因此可以将其分块，即为
 *      pre: 14 (47 18 51) (32 36 22)
 *     post: (18 51 47) (36 22 32) 14
 *          对比可知，可以采取分治的思想，对左右子树分别进行头->尾
 *      的操作，对所有左右节点完成分治后，即可将先序转换为后序。
 *
 *   采用递归方法完成
 * @核心部分
 * @param pre       先序遍历数组
 * @param perStart
 * @param perEnd
 * @param post      将生成对后序遍历数组
 * @param postStart
 * @param postEnd
 */
void PreToPost(int pre[], int perStart, int perEnd, int post[], int postStart, int postEnd) {
    int half;
    if (perEnd >= perStart) {
        post[postEnd] = pre[perStart];
        half = (perEnd - perStart) / 2;
        /**
         * 左子树
         * 在先序遍历起始位置就是原本的起始位置值+1，终止位置就是起始位置+子树的长度（即原树的二分之一）
         * 在后序遍历的位置因为只在后面添加了值，所以起始位置不变，终止位置就是原树分一半再减去一（下标从0开始）
         */
        PreToPost(pre, perStart + 1, perStart + half, post, postStart, postStart + half - 1);
        /**
         * 右子树
         * 在先序遍历的起始位置就是左子树结束位置的下一个，终止位置就是原树的终止位置（每次只处理第一个节点）
         * 在后序遍历的起始位置就是左子树结束位置的下一个，终止位置就是原树的最后的位置-1（在后面添加了值）
         */
        PreToPost(pre, perStart + half + 1, perEnd, post, postStart + half, postEnd - 1);
    }
}

/**
 * @调用部分
 * @param queue
 * @return
 */
tQueue<BitTree> exercises15(tQueue<BitTree> queue) {
    int length = size(queue);
    int pre[length];
    int post[length];
    for (int i = 0; i < size(queue); i++) {          //转换队列为数组，方便读取
        BitTree node = pop(queue);
        push(queue, node);
        pre[i] = node->data;
    }
    PreToPost(pre, 0, length - 1, post, 0, length - 1);
    tQueue<BitTree> q = tCreateQueue<BitTree>();        //转换为标准队列
    for (int i = 0; i < length; i++) {
        push(q, CreateNode(post[i]));
    }
    return q;
}

// 测试第十五题
void run15() {
    BitTree root = CreateFullTree(15);
    tQueue<BitTree> queue = exercises15(PreOrder(root));
    visitQueue(PostOrder(root));
    visitQueue(queue);
}

/**
 * 16.使用叶节点从左到右创建链表，由于是从左到右，即前/中/后序遍历均可，只需要在
 * 将前一个节点保存（第一个节点就是head）,然后在遍历时的入队操作改为判断是否为叶
 * 子节点，若是则与前一个节点链接（即双向链表链接），最后将第一个节点（head）设置
 * 其前为空，最后一个节点后节点设置为空，再返回head，此head即为最后节点。
 * @param head
 * @return
 */
BitTree exercises16(BitTree head) {
    BitTree list = head;
    BitTree node;
    tQueue<BitTree> queue = InOrder(head);
    while (!empty(queue)) {
        node = pop(queue);
        if (node->LNode == NULL && node->RNode == NULL) {
            node->LNode = list;
            list->RNode = node;
            list = node;
        }
    }
    list->RNode = NULL;
    head->LNode = NULL;
    return head;
}

//测试函数
void tPrint16(BitTree head) {
    BitTree node = head;
    tPrintTimeInfo();
    while (node != NULL) {
        tPrint(node->data);
        tPrint(" ");
        node = node->RNode;
    }
    tEnter();
}

// 测试16题
void run16() {
    BitTree root = CreateFullTree(10);
    visitQueue(LevelOrder(root));
    tPrint16(exercises16(root));
}

/**
 * 17.此相似最后效果为两树是否具有相同的结构，判断结构是否相似即可
 *  1.使用递归将很轻易实现，思路为判断当前节点是否同时为空，若是，
 *  则返回1，若不是都为空（一个为空一个不是）则返回0，若有子节点，
 *  则递归子节点做同样的操作，最后返回一个并值（&）
 *  2.不使用递归，即使用遍历手法，即使用前/中/后序遍历方法，当转向
 *  时判断另一棵树是否转向，若转向一旦出现不同，则两树不相似。提示
 *  判断两树是否有相同的转向方式，可以使用标记值，每次循环重制即可。
 *  此处使用非递归中序遍历，递归方案在书上有详解
 * @return
 */
// 17题辅助函数，中序遍历返回转向表
int *help17(BitTree root) {
    tQueue<BitTree> queue = tCreateQueue<BitTree>();
    tStack<BitTree> stack = tCreateStack<BitTree>();
    BitTree node = root;
    int index = 0;
    int *ret = (int *) malloc(sizeof(int) * getSize(root) * 3); //此处放置一个长度为3倍树节点的数组，放置溢出
    while (node != NULL || !empty(stack)) {
        if (node != NULL) {
            push(stack, node);
            node = node->LNode;
            ret[index++] = 1;//向左即为1
        } else {
            node = pop(stack);
            push(queue, node);
            node = node->RNode;
            ret[index++] = 2;//向右即为2
        }
    }
    return ret;
}

int exercises17(BitTree tree1, BitTree tree2) {
    if (getSize(tree1) != getSize(tree2)) {  //先判断节点数是否相同，若不相同则一定不相似
        return 0;
    }
    int *itree1 = help17(tree1);
    int *itree2 = help17(tree2);
    for (int i = 0; i < getSize(tree1); ++i) {
        if (itree1[i] != itree2[i]) {
            return 0;
        }
    }
    return 1;
}

//测试第17题
void run17() {
    BitTree tree1 = CreateFullTree(10);
    BitTree tree2 = CreateRandomTree(10);
    tLog(exercises17(tree1, tree2));
}

// 18题未实现线索二叉树，历年真题未考察，不做实现

/**
 * 19. 2014统考真题 求树带权路径之和
 *
 * 注：链表树节点data即为题意中的weight
 *
 * @details 思路基本相同，节点权重乘节点深度然后求和，在第12题时求解过单个节点
 *  的祖先节点队列，因此其返回的队列的长度-1就是其深度
 *
 * 注：大量使用前方法，需整合
 * @param root
 * @return int 带权路径只和
 */
int exercises19(BitTree root) {
    tQueue<BitTree> queue = LevelOrder(root);                               //获取各个节点
    BitTree node;
    int weight = 0;
    while (!empty(queue)) {
        node = pop(queue);
        weight += node->data * (exercise12(root, node->data).size - 1);  //获取深度再乘权重再求和
    }
    return weight;
}

void run19() {
    BitTree root = CreateFullTree(10);
    tLog(exercises19(root));
}

//20题所用结构体
typedef struct node20 {
    char data[10];
    struct node20 *left, *right;
} BTree;

/**
 * 20题 2017年统考真题
 *
 * 算法即中序遍历，但是需要处理，每棵子树下的节点需要扩号以确保正确性。
 * 此题使用递归相对方便，只需在外部前加入左括号，后部加入右括号，即可保证
 * 算式正确性
 *
 * @param root
 * @return
 */
void exercises20(BTree *root, int deep){
    if (root == NULL){
        return;
    } else if(root->left==NULL&&root->right==NULL){
        tPrint(root->data);
    } else{
        if (deep>1){
            tPrint("(");
        }
        exercises20(root->left,deep+1);
        tPrint(root->data);
        exercises20(root->right,deep+1);
        if (deep>1){
            tPrint(")");
        }
    }
}