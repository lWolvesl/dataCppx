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
    for (int j = FirstNeighbor(G, G.vertices[i].data);
         j >= 0; j = NextNeighbor(G, G.vertices[i].data, G.vertices[j].data)) {
        if (!visited[j]) {
            DFS_help(queue, G, j);
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

//----------------------------------------------------------------------------------------------------------

void DFS_help(tQueue<int> &queue, MGraph G, int i) {
    visited[i] = true;
    push(queue, G.Vex[i].data);
    for (int j = G.FirstNeighbor(G.Vex[i].data); j >= 0; j = G.NextNeighbor(G.Vex[i].data, G.Vex[j].data)) {
        if (!visited[j]) {
            DFS_help(queue, G, j);
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

/**
* 非递归实现
*/
tQueue<int> DFS_F(ALGraph graph) {
    tQueue<int> queue = tCreateQueue<int>();    //初始化队列
    tStack<int> stack = tCreateStack<int>();    //初始化栈
    push(stack, graph.vertices[0].data);       //将根节点放入栈中
    visited[0] = true;
    while (!empty(stack)) {                         //当栈不空时，代表还有节点未遍历
        int temp = pop(stack);                //节点出栈
        int index = indexAL(graph, temp);
        push(queue, temp);                                //节点输出入队

        for (int w = FirstNeighbor(graph, temp); w >= 0; w = NextNeighbor(graph, temp, graph.vertices[w].data)) {
            if (!visited[w]) {
                push(stack, graph.vertices[w].data);
                visited[w] = true;
            }
        }
    }
    return queue;
}

void runDFS1() {
    ALGraph G = createALHand1();
    tQueue<int> queue = DFS(G);
    while (!empty(queue)) {
        tLog(pop(queue));
    }
}

void runD2() {
    ALGraph G = CreateALGraph(5, false);
    tQueue<int> queue = DFS(G);
    while (!empty(queue)) {
        tLog(pop(queue));
    }
    MGraph graph = MGraph(5, false);
    queue = DFS(graph);
    while (!empty(queue)) {
        tLog(pop(queue));
    }
}

void runDFS2() {
    MGraph G = createMHand1();
    tQueue<int> queue = DFS(G);
    while (!empty(queue)) {
        tLog(pop(queue));
    }
}

void runDFS() {
    runDFS1();
}