//
// Created by wolves on 2022/9/18.
//

#define MaxVertexNum 100

typedef struct ArcNode {
    int adjvex;
    struct ArcNode *next;
} ArcNode;

typedef struct VNode {
    int data;
    ArcNode *first;
} VNode, AdjList[MaxVertexNum];

typedef struct {
    AdjList vertices;
    int vex, arcnum;
} ALGraph;