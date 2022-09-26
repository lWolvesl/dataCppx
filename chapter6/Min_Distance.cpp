//
// Created by wolves on 2022/9/23.
//
#include "../tools.cpp"
#include "./ALGraph.cpp"

// 设置不可达为 999999，也可以将此值改为int最大值
#define Unreachable 999999

// 记录距离
int dist[MaxVertexNum];
bool visited[MaxVertexNum];

/**
 * 单源路径最短长度
 * @param G
 * @param u
 */
void BFS_MIN_Distance(ALGraph G, int u) {
    for (int i = 0; i < G.vexnum; ++i) {
        dist[i] = Unreachable;
        visited[i] = false;
    }
    int index = indexAL(G, u);
    if (index == -1) {
        return;
    }

    visited[index] = true;
    dist[index] = 0;

    tQueue<int> queue = tCreateQueue<int>();
    push(queue, u);
    int temp;
    while (!empty(queue)) {
        temp = indexAL(G, pop(queue));
        for (int i = FirstNeighbor(G, G.vertices[temp].data);
             i >= 0; i = NextNeighbor(G, G.vertices[temp].data, G.vertices[i].data)) {
            if (!visited[i]) {
                visited[i] = true;
                dist[i] = dist[temp] + 1;
                push(queue, G.vertices[i].data);
            }
        }
    }
}

void testBFS_MIN() {
    ALGraph G = createALHand1();
    BFS_MIN_Distance(G, 1);
    tLog("最短长度");
    for (int i = 0; i < G.vexnum; ++i) {
        tLog(dist[i]);
    }
}

// 标识路径
int path[MaxVertexNum];

/**
 * 不适用于带有负权值边的图
 * 狄杰斯科拉算法，仅做参考
 * 笔试主要要求手写，不做实现要求
 * 具体思想请参考王道网课
 */
void Dijkstra(ALGraph G, int u) {
    for (int i = 0; i < G.vexnum; ++i) {
        dist[i] = Unreachable;
        visited[i] = false;
        path[i] = -1;
    }

    int index = indexAL(G, u);
    if (index == -1) {
        return;
    }
    dist[index] = 0;

    // 第一次执行初始化
    ArcNode *node = G.vertices[index].first;
    while (node) {
        int i = indexAL(G, node->adjvex);
        if (node->power + dist[index] < dist[i]) {
            dist[i] = node->power + dist[index];
            path[i] = index;
        }
        node = node->next;
    }

    visited[index] = true;

    int v = G.vexnum;
    v--;

    while (v != 0) {
        // 查找未查找到的节点的最小值
        int in = -1;
        for (int i = 0; i < G.vexnum; ++i) {
            if (in == -1 && !visited[i]) {
                in = i;
                continue;
            }
            if (!visited[i] && dist[in] > dist[i]) {
                in = i;
            }
        }

        // 对节点判断是否路径更小，若更小则修改长度和来源
        ArcNode *nodeX = G.vertices[in].first;
        while (nodeX) {
            int i = indexAL(G, nodeX->adjvex);
            if (!visited[i] && nodeX->power + dist[in] < dist[i]) {
                dist[i] = nodeX->power + dist[in];
                path[i] = in;
            }
            nodeX = nodeX->next;
        }

        visited[in] = true;
        v--;
    }

}

void testDj() {
    ALGraph G = createALHand1();
    Dijkstra(G, 1);
    tLog("最短长度");
    for (int i = 0; i < G.vexnum; ++i) {
        tLog(dist[i]);
    }
    tLog("来源");
    for (int i = 0; i < G.vexnum; ++i) {
        tLog(path[i]);
    }
}
