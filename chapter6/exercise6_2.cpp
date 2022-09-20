//
// Created by wolves on 2022/9/20.
//

#include "./ALGraph.cpp"
#include "./MGraph.cpp"

/**
 * 从邻接表转换为邻接矩阵
 * @param G
 * @return
 */
MGraph exercises4(ALGraph G) {
    MGraph graph;
    //先添加节点
    for (int i = 0; i < G.arcnum; ++i) {
        graph.InsertVertex(G.vertices[i].data);
    }
    //再添加边
    for (int i = 0; i < G.arcnum; ++i) {
        ArcNode *node = G.vertices[i].first;
        while (node) {
            graph.AddEdge(G.vertices[i].data, node->adjvex);
            node = node->next;
        }
    }
    return graph;
}