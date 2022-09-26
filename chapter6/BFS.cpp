//
// Created by wolves on 2022/9/20.
//
#pragma once //确保此作为头文件对时候只会引用一次

#include "./ALGraph.cpp"
#include "./MGraph.cpp"

/**
 * 图的深度优先遍历类似与树的层次遍历，只不过需要判断此节点是否已被访问
 *  由于已实现了图的基本方法，因此无论图的内部结构是怎样实现的，在外部调用时，所使用的方法是一样的
 *   上下两种方法，前者为结构体方式调用，后者为类调用，逻辑一致
 */

// 判断节点是否已经被访问的数组，C语言编译时每个值默认为 0/false
bool visited[MaxVertexNum];

void BFS_help(tQueue<int> &queue, ALGraph G, int i) {
    visited[i] = true;
    tQueue<int> q = tCreateQueue<int>();
    push(q, G.vertices[i].data);
    while (!empty(q)) {
        int temp = pop(q);
        push(queue, temp);
        for (int j = FirstNeighbor(G, temp); j >= 0; j = NextNeighbor(G, temp, j)) {
            int index = indexAL(G, j);
            if (!visited[index]) {
                push(q, G.vertices[index].data);
                visited[index] = true;
            }
        }
    }
}

tQueue<int> BFS(ALGraph G) {
    tQueue<int> queue = tCreateQueue<int>();
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            BFS_help(queue, G, i);
        }
    }
    return queue;
}


//---------------------------------------------------------------------------------------------------------------------
void BFS_help(tQueue<int> &queue, MGraph G, int i) {
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
            }
        }
    }
}

tQueue<int> BFS(MGraph G) {
    tQueue<int> queue = tCreateQueue<int>();
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            BFS_help(queue, G, i);
        }
    }
    return queue;
}

void runBFS1() {
    ALGraph G = createALHand1();
    tQueue<int> queue = BFS(G);
    while (!empty(queue)) {
        tLog(pop(queue));
    }
}

void runBFS2() {
    MGraph G = createMHand1();
    tQueue<int> queue = BFS(G);
    while (!empty(queue)) {
        tLog(pop(queue));
    }
}

void runBFS() {
    runBFS2();
}