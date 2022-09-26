//
// Created by wolves on 2022/9/20.
//
/**
 * 默认使用邻接矩阵，若用邻接表请将 MGraph替换为 ALGraph 并将类调用方法改为标准函数式调用
 * 注：由于本节写于结构重构前，因此只提供思路，函数执行未验证
 */
#include "./MGraph.cpp"
#include "./ALGraph.cpp"

/**
 * @details 2. 判断一个无向图是否为一棵树   注意是一棵
 * Method 1
 *  直接魔改 BFS 算法 ，若在主函数中发现求证节点是否访问过时，发现节点已访问过，直接返回 false
 *   并且由于是一棵树，大调用只能调用一次，超过一次也判 false
 *   遍历的结果也要为所有节点，否则代表存在森林，也不为一棵树
 * @param graph
 * @return
 */

// 判断节点是否已经被访问的数组，C语言编译时每个值默认为 0/false
bool visited[MaxVertexNum];

/**
 * 主函数
 * @param G
 * @param i
 * @return
 */
bool exercises2_help(tQueue<int> &queue, MGraph G, int i) {
    visited[i] = true;
    tQueue<int> q = tCreateQueue<int>();
    push(q, G.Vex[i].data);
    while (!empty(q)) {
        int temp = pop(q);
        push(queue, temp);
        for (int j = G.FirstNeighbor(temp); j >= 0; j = G.NextNeighbor(temp, G.Vex[j].data)) {
            if (!visited[j]) {
                push(q, G.Vex[j].data);
                visited[j] = true;
            } else {
                return false;                      // 此处只要判断到访问过，即代表访问了已访问的数据，即代表存在环
            }
        }
    }
    return true;
}

/**
 * 调用函数
 * @param G
 * @return
 */
bool exercises2(MGraph G) {
    tQueue<int> queue = tCreateQueue<int>();
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    bool tag = true;
    int i;
    for (i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            tag = exercises2_help(queue, G, i);
        }
    }
    if (i > 1 || !tag || size(queue) != G.vexnum) {         // 此处进行三连判断
        return false;
    }
    return true;
}

/**
* 3.DFS非递归算法，见 chapter6/DFS.cpp 的 DFS_F(ALGraph graph) 函数
*/

/**
* 4.1 用深度优先遍历算法辨别以 邻接表 方式存储的 有向图 中是否存在由 i 到 j 的路径
*      无论深度优先还是广度优先，都先找到节点位置，然后进行遍历，深度优先的方法每次遍历都储存到栈中
 *      若出现目标 j 节点，则为存在此队列，若未发现队列，则出栈并继续查找，若栈空则表明不存在路径。
* @param G
* @return
*/
bool exercises4_1_help(tQueue<int> &queue, ALGraph G, int i, int j) {
    visited[i] = true;
    push(queue, G.vertices[i].data);
    for (int k = FirstNeighbor(G, G.vertices[i].data);
         k >= 0; k = NextNeighbor(G, G.vertices[i].data, G.vertices[k].data)) {
        if (G.vertices[k].data == j) {
            return true;
        }
        if (!visited[k]) {
            exercises4_1_help(queue, G, k, j);
        }
    }
    return false;
}

bool exercises4_1(ALGraph G, int i, int j) {
    tQueue<int> queue = tCreateQueue<int>();
    for (int m = 0; m < G.vexnum; ++m) {
        visited[m] = false;
    }
    int index = indexAL(G, i);
    bool check = exercises4_1_help(queue, G, index, j);
    if (check) {
        return true;
    }
    return false;
}

/**
* 4.1 用广度优先遍历算法辨别以 邻接表 方式存储的 有向图 中是否存在由 i 到 j 的路径
*      无论深度优先还是广度优先，都先找到节点位置，然后进行遍历，广度优先遍历方法即正常遍历，当发现节点时即
 *      代表存在路径，若遍历结束依旧未发现，则代表不存在队列。
* @param G
* @return
*/
bool exercises4_2_help(ALGraph G, int i, int k) {
    visited[i] = true;
    tQueue<int> q = tCreateQueue<int>();
    push(q, G.vertices[i].data);
    while (!empty(q)) {
        int temp = pop(q);
        for (int j = FirstNeighbor(G, temp); j >= 0; j = NextNeighbor(G, temp, G.vertices[j].data)) {
            if (G.vertices[j].data == k) {
                return true;
            }
            if (!visited[j]) {
                push(q, G.vertices[j].data);
                visited[j] = true;
            }
        }
    }
    return false;
}

bool exercises4_2(ALGraph G, int m, int n) {
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    bool check = exercises4_2_help(G, indexAL(G, m), n);
    if (check) {
        return true;
    }
    return false;
}

/**
 * 5.输出所有简单路径
      使用广度优先遍历，每找到一个序列就放入大序列
 * @param graph
 * @param m
 * @param n
 * @return
 */
void BFS_help(tQueue<tQueue<int>> &queue, ALGraph G, int i, int n) {
    visited[i] = true;
    tQueue<int> q = tCreateQueue<int>();
    push(q, G.vertices[i].data);
    while (!empty(q)) {
        int temp = pop(q);
        for (int j = FirstNeighbor(G, temp); j >= 0; j = NextNeighbor(G, temp, G.vertices[j].data)) {
            if (n == j) {
                push(queue, tCpyQueue(q));
                for (int k = 0; k < G.vexnum; ++k) {
                    visited[k] = false;                     //重置已访问列表
                }
                visited[i] = true;
                continue;
            }
            if (!visited[j]) {
                push(q, G.vertices[j].data);
                visited[j] = true;
            }
        }
    }
}

tQueue<tQueue<int>> exercises5(ALGraph G, int m, int n) {
    tQueue<tQueue<int>> queue = tCreateQueue<tQueue<int>>();
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    BFS_help(queue, G, indexAL(G, m), n);
    return queue;
}