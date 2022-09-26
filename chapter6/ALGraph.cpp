//
// Created by wolves on 2022/9/18.
// 图的邻接表表示法
//
#pragma once //确保此作为头文件对时候只会引用一次

#include "../tools.cpp"

// 邻接表中最大顶点数为100
#define MaxVertexNum 100

typedef struct ArcNode {
    int adjvex;
    int power;
    struct ArcNode *next;
} ArcNode;

typedef struct VNode {
    int data;
    ArcNode *first;
} VNode, AdjList[MaxVertexNum];

typedef struct {
    AdjList vertices;
    bool directed;                  // 图是否有向
    int vexnum, arcnum;
} ALGraph;

/**
 * 获取值 x 所在 邻接表矩阵 中的索引
 * @param G
 * @param x
 * @return
 */
int indexAL(ALGraph G, int x) {
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.vertices[i].data == x) {
            return i;
        }
    }
    return -1;
}

/**
 * 判断是否存在边<x,y>
 * @param G
 * @param x
 * @param y
 * @return
 */
bool Adjacent(ALGraph G, int x, int y) {
    int m = indexAL(G, x);
    int n = indexAL(G, y);
    if (m == -1 || n == -1) {
        tWrong("顶点不存在");
        return false;
    }
    ArcNode *node = G.vertices[m].first;
    int value = G.vertices[n].data;
    while (node) {
        if (node->adjvex == value) {
            return true;
        }
        if (node->next) {
            node = node->next;
        } else {
            break;
        }
    }
    return false;
}

/**
 * 获取图G中与顶点x邻接的边
 * @param G
 * @param x
 * @return
 */
ArcNode *NeighborsList(ALGraph G, int x) {
    int m = indexAL(G, x);
    if (m == -1) {
        tWrong("顶点不存在");
    }
    assert(m != -1);                                  // 此处使用断言终止程序
    return G.vertices[m].first;
}

/**
 * 列出图G中与顶点x邻接的边
 * @param G
 * @param x
 */
void Neighbors(ALGraph G, int x) {
    ArcNode *node = NeighborsList(G, x);
    tPrintTimeInfo();
    cout << "与顶点 " << x << " 邻接的有";
    while (node != NULL) {
        cout << node->adjvex << " ";
        node = node->next;
    }
    tEnter();
}

/**
 * 向图中添加<x,y>边
 * @param G
 * @param x
 * @param y
 * @return
 */
bool AddEdge(ALGraph &G, int x, int y) {
    int m = indexAL(G, x);
    int n = indexAL(G, y);
    if (m == -1 || n == -1) {
        tWrong("顶点不存在");
        return false;
    }
    if (m == n) {
        tWarn("出现自环");
    }
    ArcNode *temp = (ArcNode *) malloc(sizeof(ArcNode));
    temp->adjvex = y;
    temp->next = NULL;
    ArcNode *node = G.vertices[m].first;
    if (!node) {
        G.vertices[m].first = temp;
    } else {
        while (node) {
            if (node->adjvex == y) {
                tWarn("1该边已存在");
                return false;
            }
            if (node->next) {
                node = node->next;
            } else {
                break;
            }
        }
        node->next = temp;
    }
    G.arcnum++;

    // 此处判断是否是无向图，若是无向图，则需要将另一个顶点的邻接表也设置一下
    if (!G.directed) {
        ArcNode *tempY = (ArcNode *) malloc(sizeof(ArcNode));
        tempY->adjvex = x;
        tempY->next = NULL;
        ArcNode *nodeY = G.vertices[n].first;
        if (!nodeY) {
            G.vertices[n].first = tempY;
        } else {
            while (nodeY) {
                if (nodeY->next) {
                    nodeY = nodeY->next;
                } else {
                    break;
                }
            }
            nodeY->next = tempY;
        }
        G.arcnum++;
    }
    return true;
}

/**
 * 从图G中删除<x,y>边
 * @param G
 * @param x
 * @param y
 * @return
 */
bool RemoveEdge(ALGraph &G, int x, int y) {
    int m = indexAL(G, x);
    int n = indexAL(G, y);
    int tagX = 0;
    if (m == -1 || n == -1) {
        tWrong("顶点不存在");
        return false;
    }
    ArcNode *node = G.vertices[m].first;
    if (!node) {
        return false;
    }
    if (node->adjvex == y) {
        G.vertices[m].first = node->next;
        tagX = 1;
    } else {
        while (node->next) {
            if (node->next->adjvex == y) {
                node->next = node->next->next;
                tagX = 1;
                G.arcnum--;
                break;
            }
            if (node->next) {
                node = node->next;
            } else {
                break;
            }
        }
    }
    if (tagX == 0) {
        return false;
    }
    if (!G.directed) {
        ArcNode *nodeY = G.vertices[n].first;
        if (!nodeY) {
            return false;
        }
        if (nodeY->adjvex == x) {
            G.vertices[n].first = nodeY->next;
        } else {
            while (nodeY->next) {
                if (nodeY->next->adjvex == x) {
                    nodeY->next = nodeY->next->next;
                    G.arcnum--;
                    break;
                }
                if (nodeY->next) {
                    nodeY = nodeY->next;
                } else {
                    break;
                }
            }
        }
    }
    return false;
}

/**
 * 在图G中插入顶点x
 * @param G
 * @param x
 * @return
 */
bool InsertVertex(ALGraph &G, int x) {
    if (G.vexnum + 1 == MaxVertexNum) {
        tWrong("顶点已满，插入失败");
        return false;
    }
    int m = indexAL(G, x);
    if (m != -1) {
        tWarn("顶点已存在，插入失败");
        return false;
    }
    G.vertices[G.vexnum++] = VNode{x, nullptr};
    return true;
}

/**
 * 从图中删除顶点x
 *  先删除数组中顶点，再遍历删除其他顶点中含有的连接
 * @param G
 * @param x
 * @return
 */
bool DeleteVertex(ALGraph &G, int x) {
    int m = indexAL(G, x);
    if (m == -1) {
        tWarn("顶点不存在，删除失败");
        return false;
    }
    for (int i = 0; i < G.vexnum; ++i) {
        RemoveEdge(G, G.vertices[i].data, x);
    }
    for (int i = m; i < G.vexnum; ++i) {
        G.vertices[i] = G.vertices[i + 1];
    }
    G.vexnum--;
    return true;
}

/**
 * 获取x的第一个邻接顶点值，若无则返回-1
 * @param G
 * @param x
 * @return
 */
int FirstNeighbor(ALGraph G, int x) {
    int m = indexAL(G, x);
    if (m == -1) {
        tWarn("顶点不存在，检索失败");
        return -1;
    }
    ArcNode *node = G.vertices[m].first;
    if (node) {
        return indexAL(G, node->adjvex);
    }
    return -1;
}

/**
 * 获取x的邻接点中点y的下一个邻接值
 * @param G
 * @param x
 * @param y
 * @return
 */
int NextNeighbor(ALGraph G, int x, int y) {
    int m = indexAL(G, x);
    int n = indexAL(G, y);
    if (m == -1 || n == -1) {
        tWrong("顶点不存在");
        return -1;
    }
    ArcNode *node = G.vertices[m].first;
    while (node) {
        if (node->adjvex == y) {
            if (node->next) {
                return indexAL(G, node->next->adjvex);
            }
        }
        node = node->next;
    }
    return -1;
}

/**
 * 获取图中边<x,y>对应的权值
 * @param G
 * @param x
 * @param y
 * @return
 */
int Get_edge_value(ALGraph G, int x, int y) {
    int m = indexAL(G, x);
    int n = indexAL(G, y);
    if (m == -1 || n == -1) {
        tWrong("顶点不存在");
        return -1;
    }
    ArcNode *node = G.vertices[m].first;
    while (node) {
        if (node->adjvex == y) {
            return node->power;
        }
        node = node->next;
    }
    return -1;
}

/**
 * 设置图中边<x,y>的权值
 * @param G
 * @param x
 * @param y
 * @param v
 * @return
 */
bool Set_edge_value(ALGraph &G, int x, int y, int v) {
    int m = indexAL(G, x);
    int n = indexAL(G, y);
    if (m == -1 || n == -1) {
        tWrong("顶点不存在");
        return false;
    }
    ArcNode *node = G.vertices[m].first;
    while (node) {
        if (node->adjvex == y) {
            node->power = v;
            if (!G.directed) {
                ArcNode *nodeY = G.vertices[n].first;
                while (nodeY) {
                    if (nodeY->adjvex == x) {
                        nodeY->power = v;
                        return true;
                    }
                    nodeY = nodeY->next;
                }
            }
            return true;
        }
        node = node->next;
    }
    return false;
}

/**
 * 创建一个具有 num 个顶点的随机图
 * @param num
 * @param isDirected 是否有向
 * @return
 */
ALGraph CreateALGraph(int num, bool isDirected) {
    ALGraph G;
    G.directed = isDirected;
    G.arcnum = 0;
    G.vexnum = 0;
    int total = tRandomNoSame() % (num * (num - 1) + 1);
    if (total % 2) {
        total++;
    }
    tPrintTimeInfo();
    cout << "插入顶点 ";
    for (int i = 0; i < num;) {
        int temp = tRandomNoSame();
        if (InsertVertex(G, temp)) {
            cout << G.vertices[i].data << " ";
            ++i;
        }
    }
    tEnter();
    for (; G.arcnum < total;) {
        int x = tRandomNoSame() % num;
        int y = tRandomNoSame() % num;
        while (x == y) {
            y = tRandomNoSame() % num;
        }
        if (AddEdge(G, G.vertices[x].data, G.vertices[y].data)) {
            tPrintTimeInfo();
            cout << "顶点 " << G.vertices[x].data << " 与(指向)顶点 " << G.vertices[y].data << " 相连" << endl;
        }
    }
    tPrintTimeInfo();
    cout << "共有 " << G.vexnum << " 个顶点和 " << G.arcnum << " 条弧" << endl;
    return G;
}

/**
 * 手动创建一个无向图，含有5个顶点和4条弧
 * 2022/09/20 17:55:33 info      插入顶点 68 36 43 84 80
 * 2022/09/20 17:55:33 info      顶点 43 与(指向)顶点 80 相连
 * 2022/09/20 17:55:33 info      顶点 36 与(指向)顶点 84 相连
 * 2022/09/20 17:55:33 info      顶点 43 与(指向)顶点 36 相连
 * 2022/09/20 17:55:33 info      顶点 80 与(指向)顶点 68 相连
 * 2022/09/20 17:55:33 info      共有 5 个顶点和 8 条弧
 * @return
 */
ALGraph createALHand() {
    ALGraph G;
    G.directed = false;
    G.arcnum = 0;
    G.vexnum = 0;
    InsertVertex(G, 68);
    InsertVertex(G, 36);
    InsertVertex(G, 43);
    InsertVertex(G, 84);
    InsertVertex(G, 80);

    AddEdge(G, 43, 80);
    AddEdge(G, 36, 84);
    AddEdge(G, 43, 36);
    AddEdge(G, 80, 68);
    tPrintTimeInfo();
    cout << "共有 " << G.vexnum << " 个顶点和 " << G.arcnum << " 条弧" << endl;
    return G;
}

/**
 * 手动创建一个无向图，含有5个顶点和4条弧
 *    图示 王道2023 年 P226 图 6.17  /  当前文件夹中的 IMG_6_1.jpg
 * @return
 */
ALGraph createALHand1() {
    ALGraph G;
    G.directed = true;
    G.arcnum = 0;
    G.vexnum = 0;
    InsertVertex(G, 1);
    InsertVertex(G, 2);
    InsertVertex(G, 3);
    InsertVertex(G, 4);
    InsertVertex(G, 5);

    AddEdge(G, 1, 2);
    AddEdge(G, 1, 5);
    AddEdge(G, 2, 5);
    AddEdge(G, 5, 2);
    AddEdge(G, 2, 3);
    AddEdge(G, 3, 4);
    AddEdge(G, 4, 3);
    AddEdge(G, 5, 4);
    AddEdge(G, 4, 1);
    AddEdge(G, 5, 3);

    // 赋权值
    Set_edge_value(G, 1, 2, 10);
    Set_edge_value(G, 1, 5, 5);
    Set_edge_value(G, 2, 5, 2);
    Set_edge_value(G, 5, 2, 3);
    Set_edge_value(G, 2, 3, 1);
    Set_edge_value(G, 3, 4, 4);
    Set_edge_value(G, 4, 3, 6);
    Set_edge_value(G, 5, 4, 2);
    Set_edge_value(G, 4, 1, 7);
    Set_edge_value(G, 5, 3, 9);

    tPrintTimeInfo();
    cout << "共有 " << G.vexnum << " 个顶点和 " << G.arcnum << " 条弧" << endl;
    return G;
}

/**
 * 测试基础方法
 */
void testAL() {
    ALGraph graph = createALHand();
    Neighbors(graph, 36);
    tPrintTimeInfo();
    cout << Adjacent(graph, 36, 84) << endl;
    tPrintTimeInfo();
    cout << Adjacent(graph, 84, 36) << endl;
    tPrintTimeInfo();
    cout << Adjacent(graph, 68, 36) << endl;
    tPrintTimeInfo();
    cout << Adjacent(graph, 68, 80) << endl;
    RemoveEdge(graph, 68, 80);
    tPrintTimeInfo();
    cout << Adjacent(graph, 68, 80) << endl;
    tPrintTimeInfo();
    cout << Adjacent(graph, 80, 68) << endl;
    DeleteVertex(graph, 80);
    tPrintTimeInfo();
    cout << indexAL(graph, 80) << endl;
    tPrintTimeInfo();
    cout << FirstNeighbor(graph, 36) << endl;
    tPrintTimeInfo();
    cout << FirstNeighbor(graph, 68) << endl;
    tPrintTimeInfo();
    cout << NextNeighbor(graph, 36, 84) << endl;
    tPrintTimeInfo();
    cout << Get_edge_value(graph, 36, 43) << endl;
    Set_edge_value(graph, 36, 43, 10);
    tPrintTimeInfo();
    cout << Get_edge_value(graph, 36, 43) << endl;
    tPrintTimeInfo();
    cout << Get_edge_value(graph, 43, 36) << endl;
}