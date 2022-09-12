//
// Created by wolves on 2022/9/12.
//

#include "BiTNode.cpp"

/**
 * @details
 * 6.判断二叉树是否为二叉排序树。
 *  是否为排序树就是对每个节点判断其左孩子是否小于自己，右孩子是否大于自己
 *   而要对每个节点判断，即要遍历二叉树，即在 前/中/后/层序 遍历中找一个遍
 *   历方法，而中序遍历为左中右，若是二叉排序树，则其中序遍历的队列一定是从
 *   小到大的序列。因此对中序遍历判断值大小即可。
 *
 *  此处注意
 *  二叉排序树（Binary Sort Tree）或者是一颗空树；或者是具有下列性质的二叉树：
 *   （1）若左子树不为空，则左子树上所有结点的值均小于它的根节点的值
 *   （2）若右子树不为空，则右子树上所有结点的值均大于它的根节点的值
 *   （3）左右子树自己也是二叉排序树
 *
 *  并且二叉排序树是一个动态查找树，只有当树中无对应值节点时，才会插入，因此：
 *     二叉排序树中不存在相同值的节点
 *
 *  因此判断时，等于号视为非二叉排序树
 * @return
 */
bool exercises6(BitTree root) {
    if (!root) {
        return false;                         //对树判断是否为空，防止野指针
    }
    tQueue<BitTree> queue = InOrder(root);    //获取二叉树的中序遍历队列
    BitTree node = pop(queue);
    while (!empty(queue)) {
        BitTree temp = pop(queue);
        if (node->data >= temp->data) {
            return false;                    //若前一个节点值大于后一个节点值，即不是二叉排序树
        }
        node = temp;
    }
    return true;
}

//测试第六题
void run6() {
    BitTree root = CreateAVLTree(10);
    visitQueue(LevelOrder(root));
    tLog(exercises6(root));
}

/**
 * @details
 *  7. 判断节点在排序树中的层次
 *  二叉排序树查找节点，小于此节点值即向左孩子跳转，反之则向右节点跳转
 *  每次跳转时，层数+1，并重复以上步骤
 *
 * @param root 指定的树
 * @param data 指定的值
 * @return
 */
int exercises7(BitTree root, int data) {
    if (!root) {
        return -1;                          //对树判断是否为空，防止野指针
    }
    int height = 1;
    BitTree node = root;
    while (node) {
        int value = node->data;
        if (value == data) {
            return height;
        }
        node = data < value ? node->LNode : node->RNode;    //此处使用了三元表达式
        height++;
    }
    return -1;                              //数值不可达
}

//测试第七题
void run7() {
    BitTree root = CreateAVLTree(10);
    tQueue<BitTree> queue = LevelOrder(root);
    visitQueue(queue);
    for (int i = 0; i < 4; ++i) {
        pop(queue);
    }
    int node = pop(queue)->data;
    tLog(exercises7(root, node));
}

/**
 * @details
 * 8.判断是否为平衡二叉树
 *  由平衡二叉树定义可知，树中任何一个节点的左右两子树高度之差小于1。
 *  因此采用递归的方式，分别求左右两子树层次，然后判断左右高度之差绝对值是否小于1
 *
 *  注：此次实现算法采用的写法易于理解，但是运行效率较低
 * @param root
 * @return
 */
int help8_getDepth(BitTree node) {                               //获取节点深度
    if (node == NULL)
        return 0;
    int Left_Depth = help8_getDepth(node->LNode);
    int Right_Depth = help8_getDepth(node->RNode);
    return Left_Depth > Right_Depth ? Left_Depth + 1 : Right_Depth + 1;
}

bool exercises8(BitTree root) {
    if (root == NULL)
        return true;//当根节点为空是，返回true
    int Left = help8_getDepth(root->LNode);                //获取左子树的深度
    int Right = help8_getDepth(root->RNode);               //获取右子树的深度
    if (Left - Right > 1 || Right - Left > 1)                    //判断左右子树的深度相差是否大于1
        return false;
    else {
        return exercises8(root->LNode) && exercises8(root->RNode);//递归判断每个子树都否都为平衡二叉树
    }
}

/**
 * @details
 *  9.获取二叉排序树中的最大值和最小值
 *   由于二叉排序树性质
 *   自根节点一路向左，最后一个非空节点即为最小值
 *   自根节点一路向右，最后一个非空节点即为最大值
 *
 *   为了算法的方便性，这里定义一个结构体，可以使函数返回两个值
 */
typedef struct {
    int min;
    int max;
} result9;

result9 exercises9(BitTree root) {
    BitTree temp1 = root;                   //暂存最小值节点
    BitTree temp2 = root;                   //暂存最大值节点
    while (temp1->LNode) {
        temp1 = temp1->LNode;               //一路向左
    }
    while (temp2->RNode) {
        temp2 = temp2->RNode;               //一路向右
    }
    return result9{temp1->data, temp2->data};    //此处可以返回两个值
}

//测试第九题
void run9() {
    BitTree root = CreateAVLTree(10);
    visitQueue(LevelOrder(root));
    result9 result = exercises9(root);
    tLog(result.min);
    tLog(result.max);
}

/**
 * @details
 * 10.从大到小输出所有不小于k的二叉搜索树节点的值
 *  前提思想：请看第六题
 *  中序遍历得到的结果为从小到大，因此只需要在队列中找到符合节点的值，将其后的节点入栈，再出栈输出即可
 *
 *  注：书本方法思想类似，但为递归，此版本实现的为非递归
 * @param root
 * @param k
 */
void exercises10(BitTree root, int k) {
    if (!root) {
        tLog("树为空");                            //对树判断是否为空，防止野指针
    }
    tQueue<BitTree> queue = InOrder(root);             //获取中序遍历队列
    tStack<BitTree> stack = tCreateStack<BitTree>();   //暂存栈
    BitTree node;
    while (!empty(queue)) {
        node = pop(queue);
        if (node->data >= k) {
            push(stack, node);
        }
    }
    visitQueue(stack);
}

//测试第十题
void run10() {
    BitTree root = CreateAVLTree(10);
    visitQueue(InOrder(root));
    exercises10(root, 44);
}

/**
 * @details
 * 12.获取总节点数为n的二叉排序树中第k小的节点指针
 *  前提思想：第六题
 *  中序遍历第k个值就是第k小节点
 *  又由于随机生成的二叉排序树默认高度就是 log2 N，而搜索的时间复杂度就是高度。
 *
 * 要求2：结构体中需要一个新的值count，意为此节点子树的总节点数字,此编写只对输
 *  出的节点进行结构体改变，若有特殊需求请改写 chapter5/BiTNode.cpp 中的
 *  CreateAVLTree()方法以实现需求。
 * @param n
 * @param k  1 =< k <= n
 * @return
 */
typedef struct {
    int data;
    struct TreeNode *LNode, *RNode;
    int count;
} result12;

result12* exercises12(int n, int k) {
    BitTree root = CreateAVLTree(n);           //生成总节点为n的随机二叉排序树
    tQueue<BitTree> queue = InOrder(root);              //获取中序遍历序列
    visitQueue(queue);                                  //从小到大打印
    BitTree node;
    while (k) {
        node = pop(queue);
        k--;
    }
    result12 result{node->data, node->LNode, node->RNode, getDepth(node)};
    return &result;
}

//测试第十二题
void run12() {
    result12* result = exercises12(10, 4);
    tLog(result->data);
}