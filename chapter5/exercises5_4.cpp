//
// Created by wolves on 2022/9/10.
//

#include "./BiTNode.cpp"
#include "../tools.cpp"

/**
 * 第五题 树结构如下
 * typedef struct TreeNode {
 *   int data;
 *   struct TreeNode *LNode, *RNode;
 * } *BitTree;
 * 由于孩子兄弟表示法所用的树与正常二叉树无异，因此用此表示
 *      LNode 表示孩子节点
 *      RNode 表示兄弟节点
 *
 * 求原树叶子节点数
 * 例：         A         ｜       A        C       F
 *          /     \      ｜     / ｜ \             ｜
 *         B       C     ｜    B  E  G             H
 *      /     \     \    ｜    ｜
 *     D       E     F   ｜    D
 *              \   /    ｜
 *               G H     ｜
 *
 *     观察此树，可以得到以下几种情况
 *      1.B 含有左孩子且含有有孩子，代表B有孩子并且有兄弟，而其左孩子没有孩子，因此其左孩子就是根节点
 *      2.E 仅含有右孩子，代表有右兄弟，并且它没有孩子节点，此时它就是叶子节点
 *      3.G 无孩子，即为叶子节点
 *      4.C 情况与 E 类似，只不过它即是树根节点也是叶子节点
 *      5.F 含有左孩子但无有孩子，代表其没有兄弟但是有孩子，它不是叶子节点
 *      6.H 情况与G类似
 *
 *     由此可得，当遍历节点时，需要判断它是否有左孩子，若有，则它一定不是叶子节点，若无左孩子，则其一定
 *      是叶子节点，对每个节点进行此判断，即可找到原树中所有的叶子节点
 *
 *     因此算法使用层序遍历即可，对每个节点依次判断是否有左孩子，即是否在原树中有孩子，若无则为叶节点，
 *      总数加一即可。
 * @param tree
 * @return
 */
int exercises5(BitTree tree) {
    int count = 0;                                    // 记录总叶节点数
    tQueue<BitTree> queue = LevelOrder(tree);    // 生成孩子兄弟树的层序遍历序列
    while (!empty(queue)) {
        BitTree node = pop(queue);
        if (node->LNode == NULL) {
            count++;                                  // 左孩子不存在，表明为叶子节点，总数加一
        }
    }
    return count;
}

void run5() {
    BitTree tree = CreateRandomTree(5);
    tLog(exercises5(tree));
}

/**
 * 求深度
 *  已知孩子兄弟树求原树深度算法与二叉树求深度类似，只不过在向右节点跳转时，孩子兄弟树的右节点
 *    代表的是此节点的兄弟，因此层数不加，其他过程与普通二叉树求深度相同
 * @param tree
 * @return
 */
int exercises6(BitTree tree) {
    int highL = 0, highR = 0;
    if (tree == NULL) {
        return 0;
    } else {
        highL = exercises6(tree->LNode);
        highR = exercises6(tree->RNode);
        if (highL + 1 > highL) {
            return highL + 1;
        } else {
            return highR;
        }
    }
}

void run6(){
    BitTree tree = CreateRandomTree(5);
    tLog(exercises6(tree));
}