#include "./tools.cpp"
#include "chapter6/DFS.cpp"

void hello() {
    tLog("Hello!");
    tWarn("Welcome to my space!");
    tWrong("Have a good time!");
}

/**
 * 为规范输出
 * 请将运行时代码填入此方法
 */
void runCode() {
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

int main() {
    //运行环境：1 为make/cLon   2 code runner
    RUN_ENV = 1;

    tStart();
    runCode();
    tEnd();
    return 0;
}