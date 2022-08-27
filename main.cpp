//#include "tools.cpp"
#include "chapter5/BiTNode.cpp"

/**
 * 为规范输出
 * 请将运行时代码填入此方法
 */
void runCode() {
    auto tree = CreateFullTree(10);
    auto queue = InOrder(tree);
    visitQueue(queue);
}

int main() {
    //运行环境：1 为cmake   2 为code runner
    RUN_ENV = 1;
    tStart();
    runCode();
    tEnd();
    return 0;
}