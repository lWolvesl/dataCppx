//
// Created by wolves on 2022/9/20.
//
#pragma once //确保此作为头文件对时候只会引用一次

#include "./ALGraph.cpp"
#include "./MGraph.cpp"

/**
 * 深度优先遍历，实现方式与树的先序遍历类似，均为一路走到头，在回溯找其他顶点
 *  由于已实现了图的基本方法，因此无论图的内部结构是怎样实现的，在外部调用时，所使用的方法是一样的
 *   上下两种方法，前者为结构体方式调用，后者为类调用，逻辑一致
 *    深度优先遍历使用递归算法相对较易
 *     若要使用非递归，可以使用栈并参考第五章的非递归先序遍历算法，内使用栈保存数据，切换数据使用NextNeighbor方法即可
 */

// 判断节点是否已经被访问的数组，C语言编译时每个值默认为 0/false
bool visited[MaxVertexNum];

void DFS_help(tQueue<int> &queue, ALGraph G, int i) {
    visited[i] = true;
    push(queue, G.vertices[i].data);
    for (int j = FirstNeighbor(G, G.vertices[i].data); j >= 0; j = NextNeighbor(G, G.vertices[i].data, j)) {
        int index = indexAL(G, j);
        if (!visited[index]) {
            DFS_help(queue, G, index);
        }
    }
}

tQueue<int> DFS(ALGraph G) {
    tQueue<int> queue = tCreateQueue<int>();
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            DFS_help(queue, G, i);
        }
    }
    return queue;
}

void DFS_help(tQueue<int> &queue, MGraph G, int i) {
    visited[i] = true;
    push(queue, G.Vex[i].data);
    for (int j = G.FirstNeighbor(G.Vex[i].data); j >= 0; j = G.NextNeighbor(G.Vex[i].data, j)) {
        int index = G.indexM(j);
        if (!visited[index]) {
            DFS_help(queue, G, index);
        }
    }
}

tQueue<int> DFS(MGraph G) {
    tQueue<int> queue = tCreateQueue<int>();
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            DFS_help(queue, G, i);
        }
    }
    return queue;
}