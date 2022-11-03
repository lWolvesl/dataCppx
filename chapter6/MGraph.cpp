//
// Created by wolves on 2022/9/18.
//

#pragma once //确保此作为头文件对时候只会引用一次

#include "../tools.cpp"

// 最大顶点数
#define MaxVertexNum 100

/**
 * 图的邻接矩阵表示实现  采用C++类实现
 * 数据结构相当于
 *
 *  struct data {                            // 数据域
 *      int data;
 *      bool isDeleted;                     //逻辑删除位置
 *  };
 *  typedef struct{
 *      data Vex[MaxVertexNum];       // 定点表
 *      int Edge[MaxVertexNum][MaxVertexNum]; // 边表
 *      int vexnum,arcnum;  // 图当前含有的定点数和弧数
 *      int directed;       // 该图是否有向
 *  }
 */
class MGraph {
    struct data {                            // 数据域
        int data;
        bool isDeleted;                     //逻辑删除位置
    };
public:
    data Vex[MaxVertexNum]{};                  // 顶点表
    int Edge[MaxVertexNum][MaxVertexNum]{};   // 边表
    int vexnum{}, arcnum{};                     // 图当前含有的定点数和弧数
    int directed;       // 该图是否有向

    MGraph() {
        directed = 0;
    }

    /**
    * 创建一个含有 num 个顶点的随机图
    * @param num 顶点总数
    * @param directed 是否有向
    */
    MGraph(int num, bool isDirected) {
        tLog("创建图");
        directed = isDirected;
        if (directed) {
            if (num > MaxVertexNum) {
                tWarn("所需顶点总数超过100，自动重设为100");
                vexnum = 100;
            }
            tPrintTimeInfo();
            cout << "顶点列表 ";
            for (int i = 0; i < num;) {
                if (InsertVertex(tRandomNoSame())) {
                    cout << Vex[i].data << " ";
                    i++;
                }
            }
            tEnter();

            int total = tRandom(0, num * (num - 1));

            for (int i = 0; i < total;) {
                int x = tRandomNoSame() % num;
                int y = tRandomNoSame() % num;
                if (AddEdge(Vex[x].data, Vex[y].data)) {
                    tPrintTimeInfo();
                    cout << "顶点 " << Vex[x].data << (Vex[x].data < 10 ? " " : "") << " 指向顶点 " << Vex[y].data
                         << (Vex[y].data < 10 ? " " : "") << " 相连" << endl;
                    ++i;
                }
            }

            tPrintTimeInfo();
            cout << "共有 " << vexnum << (vexnum < 10 ? " " : "") << " 顶点以及 " << arcnum << (arcnum < 10 ? " " : "")
                 << " 条弧" << endl;

        } else {
            if (num > MaxVertexNum) {
                tWarn("所需顶点总数超过100，自动重设为100");
                vexnum = 100;
            }

            tPrintTimeInfo();
            cout << "顶点列表 ";
            for (int i = 0; i < num;) {
                if (InsertVertex(tRandomNoSame())) {
                    cout << Vex[i].data << " ";
                    i++;
                }
            }
            tEnter();

            int total = tRandom(0, num * (num - 1) / 2);

            for (int i = 0; i < total;) {
                int x = tRandomNoSame() % num;
                int y = tRandomNoSame() % num;
                if (AddEdge(Vex[x].data, Vex[y].data)) {
                    tPrintTimeInfo();
                    cout << "顶点 " << Vex[x].data << (Vex[x].data < 10 ? " " : "") << " 与顶点 " << Vex[y].data
                         << (Vex[y].data < 10 ? " " : "") << " 相连" << endl;
                    ++i;
                }
            }

            tPrintTimeInfo();
            cout << "共有 " << vexnum << (vexnum < 10 ? " " : "") << " 顶点以及 " << arcnum << (arcnum < 10 ? " " : "")
                 << " 条弧" << endl;
        }
        tPrintTimeInfo();
        cout << "该图为" << (directed ? "有向图" : "无向图") << endl;
    }

    /**
     * 手动定义一个已知图，方便测试
     * 2022/09/18 23:59:39 info      顶点列表 0 60 95 84 65
     * 2022/09/18 23:59:39 info      顶点 65 与顶点 60 相连
     * 2022/09/18 23:59:39 info      顶点 65 与顶点 0  相连
     * 2022/09/18 23:59:39 info      顶点 0  与顶点 60 相连
     * 2022/09/18 23:59:39 info      顶点 84 与顶点 60 相连
     * 2022/09/18 23:59:39 info      顶点 95 与顶点 60 相连
     * 2022/09/18 23:59:39 info      共有 5  顶点以及 5  条弧
     * 2022/09/18 23:59:39 info      该图为无向图
     */
    void CreateByHandF() {
        InsertVertex(0);
        InsertVertex(60);
        InsertVertex(95);
        InsertVertex(84);
        InsertVertex(65);
        AddEdge(65, 60);
        AddEdge(65, 0);
        AddEdge(0, 60);
        AddEdge(84, 60);
        AddEdge(95, 60);
    }

    /**
     * 获取顶点 x 在邻接矩阵中的索引
     * @param x
     * @return
     */
    int indexM(int x) {
        for (int i = 0; i < vexnum; ++i) {
            if (x == Vex[i].data && !Vex[i].isDeleted) {
                return i;
            }
        }
        return -1;
    }

    /**
     * 判断图中是否存在边 <x,y>
     * @param x
     * @param y
     * @return
     */
    bool Adjacent(int x, int y) {
        int m = indexM(x);
        int n = indexM(y);
        return Edge[m][n];
    }

    /**
     * 辅助函数,主要方法
     * 列举出顶点 x 的邻接的边
     * @param x
     */
    tQueue<data> Neighbors_help(int x) {
        tQueue<data> queue = tCreateQueue<data>();
        for (int i = 0; i < vexnum; ++i) {
            if (Edge[x][i]) {
                push(queue, Vex[i]);
            }
        }
        return queue;
    }

    /**
     * 列举出顶点 x 的邻接的边
     * @param x
     */
    void Neighbors(int x) {
        int i = indexM(x);
        if (i == -1) {
            tWrong("顶点不存在,检索失败");
            return;
        }
        auto queue = Neighbors_help(i);
        tPrintTimeInfo();
        cout << "顶点" << x << "邻接的边为 ";
        while (!empty(queue)) {
            cout << pop(queue).data << " ";
        }
        tEnter();
    }

    /**
     * 向图中插入顶点 x , 即直接向顶点表中增加一个顶点，然后对总顶点数+1即可，注意不能超过最大顶点
     * @param x
     * @return
     */
    bool InsertVertex(int x) {
        if (vexnum + 1 > MaxVertexNum) {
            tWrong("图中顶点已满,插入失败");
            return false;
        }

        if (indexM(x) != -1) {
            tWarn("顶点已存在，插入失败");
            return false;
        }

        Vex[vexnum++].data = x;
        return true;
    }

    /**
     * 使用逻辑删除,因此 arcnum 不会减少
     * 若不使用逻辑删除，即在数组中移动值，则需要将 arcnum 减少
     * @param x
     * @return
     */
    bool DeleteVertexLogic(int x) {
        int i = indexM(x);
        if (indexM(x) == -1) {
            tWrong("顶点不存在，删除失败");
            return false;
        }
        Vex[i].isDeleted = true;
        tLog("逻辑删除成功");
        return true;
    }

    /**
     * 非逻辑删除
     * @param x
     * @return
     */
    bool DeleteVertex(int x) {
        int i = indexM(x);
        if (indexM(x) == -1) {
            tWrong("顶点不存在，删除顶点失败");
            return false;
        }
        // 平移数组值
        for (int j = i; j < vexnum - 1; ++j) {
            Vex[j] = Vex[j + 1];                        // 移动data数组
            for (int k = 0; k < vexnum - 1; ++k) {
                Edge[k][j] = Edge[k][j + 1];            // 横向移动edge数组
                Edge[j][k] = Edge[j + 1][k];            // 纵向移动edge数组
            }
        }
        arcnum--;
        tLog("删除顶点成功");
        return true;
    }

    /**
     * 向图中添加弧
     * @param x
     * @param y
     * @return
     */
    bool AddEdge(int x, int y) {
        int m = indexM(x);
        int n = indexM(y);
        if (x == y) {
            return false;
        }
        if (m == -1 || n == -1) {
            tWrong("顶点不存在，添加弧失败");
            return false;
        }
        if (Edge[m][n]) {
            tWarn("该弧已存在，添加弧失败");
            return false;
        }
        if (!directed) {
            Edge[n][m] = 1;
        }
        Edge[m][n] = 1;
        arcnum++;
        return true;
    }

    /**
     * 从图中删除弧
     * @param x
     * @param y
     * @return
     */
    bool RemoveEdge(int x, int y) {
        int m = indexM(x);
        int n = indexM(y);
        if (m == -1 || n == -1) {
            tWrong("顶点不存在，删除弧失败");
            return false;
        }
        if (Edge[m][n] == 0) {
            tWarn("不存在弧，删除弧失败");
            return false;
        }
        if (!directed) {
            Edge[n][m] = 0;
        }
        Edge[m][n] = 0;
        arcnum--;
        tLog("删除弧成功");
        return true;
    }

    /**
     * 获取顶点x的第一个邻接点，若有则返回定点号，若无则返回-1
     * @param x
     * @return
     */
    int FirstNeighbor(int x) {
        int m = indexM(x);
        if (m == -1) {
            tWrong("顶点不存在，检索失败");
            return 0;
        }
        for (int n = 0; n < vexnum; ++n) {
            int i = Edge[m][n];
            if (i != 0) {
                return n;
            }
        }
        return -1;
    }

    /**
     * 返回下一个x的邻接点中的下一个邻接点
     * @param x
     * @param y
     * @return
     */
    int NextNeighbor(int x, int y) {
        int m = indexM(x);
        if (m == -1 && indexM(y) == -1) {
            tWrong("顶点不存在，检索失败");
            return 0;
        }
        for (int n = indexM(y) + 1; n < vexnum; ++n) {
            int i = Edge[m][n];
            if (i != 0) {
                return n;
            }
        }
        return -1;
    }

    /**
     * 获取图中边<x,y>对应的权值
     * @param x
     * @param y
     * @return
     */
    int Get_edge_value(int x, int y) {
        int m = indexM(x);
        int n = indexM(y);
        if (m == -1 || n == -1) {
            tWrong("顶点不存在，检索失败");
            return 0;
        }
        return Edge[m][n];
    }

    /**
     * 设置图中边<x,y>对应的权值
     * @param x
     * @param y
     * @param v
     * @return
     */
    bool Set_edge_value(int x, int y, int v) {
        int m = indexM(x);
        int n = indexM(y);
        if (m == -1 || n == -1) {
            tWrong("顶点不存在，检索失败");
            return false;
        }
        if (!directed) {
            Edge[n][m] = v;
        }
        Edge[m][n] = v;
        return true;
    }
};

/**
 * 手动创建一个无向图，含有5个顶点和4条弧
 *    图示 王道2023 年 P226 图 6.17  /  当前文件夹中的 IMG_6_1.jpg
 * @return
 */
MGraph createMHand1() {
    MGraph G;
    G.directed = true;
    G.arcnum = 0;
    G.vexnum = 0;
    G.InsertVertex(1);
    G.InsertVertex(2);
    G.InsertVertex(3);
    G.InsertVertex(4);
    G.InsertVertex(5);

    G.AddEdge(1, 2);
    G.AddEdge(1, 5);
    G.AddEdge(2, 5);
    G.AddEdge(5, 2);
    G.AddEdge(2, 3);
    G.AddEdge(3, 4);
    G.AddEdge(4, 3);
    G.AddEdge(5, 4);
    G.AddEdge(4, 1);
    G.AddEdge(5, 3);

    // 赋权值
    G.Set_edge_value(1, 2, 10);
    G.Set_edge_value(1, 5, 5);
    G.Set_edge_value(2, 5, 2);
    G.Set_edge_value(5, 2, 3);
    G.Set_edge_value(2, 3, 1);
    G.Set_edge_value(3, 4, 4);
    G.Set_edge_value(4, 3, 6);
    G.Set_edge_value(5, 4, 2);
    G.Set_edge_value(4, 1, 7);
    G.Set_edge_value(5, 3, 9);

    tPrintTimeInfo();
    cout << "共有 " << G.vexnum << " 个顶点和 " << G.arcnum << " 条弧" << endl;
    return G;
}

/**
 * 手动创建一个无向图，含有5个顶点和4条弧
 *    图示 王道2023 年 P227 图 6.19  /  当前文件夹中的 IMG_6_2.jpg
 * @return
 */
MGraph createMHand2() {
    MGraph G;
    G.directed = true;
    G.arcnum = 0;
    G.vexnum = 0;
    G.InsertVertex(0);
    G.InsertVertex(1);
    G.InsertVertex(2);

    G.AddEdge(0, 2);
    G.AddEdge(2, 0);
    G.AddEdge(0, 1);
    G.AddEdge(1, 0);
    G.AddEdge(1, 2);

    // 赋权值
    G.Set_edge_value(0, 1, 6);
    G.Set_edge_value(1, 0, 10);
    G.Set_edge_value(0, 2, 13);
    G.Set_edge_value(2, 0, 5);
    G.Set_edge_value(1, 2, 4);

    tPrintTimeInfo();
    cout << "共有 " << G.vexnum << " 个顶点和 " << G.arcnum << " 条弧" << endl;
    return G;
}

/**
 *
 */
void testM() {
    MGraph graph;
    graph.CreateByHandF();
    graph.Neighbors(60);
    tPrintTimeInfo();
    cout << graph.Adjacent(0, 60) << endl;
    graph.RemoveEdge(0, 60);
    tPrintTimeInfo();
    cout << graph.Adjacent(0, 60) << endl;
    graph.DeleteVertex(84);
    tPrintTimeInfo();
    cout << graph.indexM(84) << endl;
    tPrintTimeInfo();
    cout << graph.FirstNeighbor(0) << endl;
    tPrintTimeInfo();
    cout << graph.NextNeighbor(60, 0) << endl;
    tPrintTimeInfo();
    cout << graph.Get_edge_value(60, 65) << endl;
    graph.Set_edge_value(60, 65, 10);
    tPrintTimeInfo();
    cout << graph.Get_edge_value(60, 65) << endl;
}