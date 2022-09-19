//
// Created by wolves on 2022/9/18.
//

#include "../tools.cpp"

// 图的邻接表表示法
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
    while (node && node->next) {
        if (node->adjvex == value) {
            return true;
        }
        node = node->next;
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
    return G.vertices[m].first->next;
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
    while (node != nullptr) {
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
    ArcNode temp{y, 0, nullptr};
    ArcNode *node = G.vertices[m].first;
    if (!node) {
        G.vertices[m].first = &temp;
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
        node->next = &temp;
    }
    G.arcnum++;

    // 此处判断是否是无向图，若是无向图，则需要将另一个顶点的邻接表也设置一下
    if (!G.directed) {
        ArcNode tempY{x, 0, nullptr};
        ArcNode *nodeY = G.vertices[n].first;
        if (!nodeY) {
            G.vertices[n].first = &tempY;
        } else {
            while (nodeY) {
                if (nodeY->adjvex == x) {
                    tWarn("2该边已存在");
                    return false;
                }
                if (nodeY->next) {
                    nodeY = nodeY->next;
                } else {
                    break;
                }
            }
            nodeY->next = &tempY;
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
    while (node && node->next) {
        if (node->next->adjvex == y) {
            node->next = node->next->next;
            tagX = 1;
            G.arcnum--;
            break;
        }
        node = node->next;
    }
    if (tagX == 0) {
        return false;
    }
    if (!G.directed) {
        ArcNode *nodeY = G.vertices[n].first;
        while (nodeY && nodeY->next) {
            if (nodeY->next->adjvex == x) {
                nodeY->next = nodeY->next->next;
                G.arcnum--;
                return true;
            }
            nodeY = nodeY->next;
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
    if (node && node->next) {
        return node->next->adjvex;
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
    ArcNode *temp;
    while (node && node->next) {
        if (node->next->adjvex == y) {
            temp = node->next;
        }
    }
    if (temp && temp->next) {
        return temp->next->adjvex;
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
    while (node && node->next) {
        if (node->next->adjvex == y) {
            return node->next->power;
        }
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
    while (node && node->next) {
        if (node->next->adjvex == y) {
            node->next->power = v;
            if (!G.directed) {
                ArcNode *nodeY = G.vertices[y].first;
                while (nodeY && nodeY->next) {
                    if (nodeY->next->adjvex == x) {
                        nodeY->next->power = v;
                    }
                }
            }
            return true;
        }
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
 * 手动创建一个图
 * 2022/09/19 23:43:18 info      插入顶点 86 5 3 38 55
2022/09/19 23:43:18 info      顶点 5 与(指向)顶点 55 相连
2022/09/19 23:43:18 info      顶点 38 与(指向)顶点 86 相连
2022/09/19 23:43:18 info      顶点 55 与(指向)顶点 38 相连
2022/09/19 23:43:18 info      顶点 55 与(指向)顶点 5 相连
2022/09/19 23:43:18 info      共有 5 个顶点和 10 条弧
 * @return
 */
ALGraph createALHand(){

}
void testAL() {
    ALGraph G = CreateALGraph(5, false);

}