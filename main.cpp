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
    tStart();
    runCode();
    tEnd();
    return 0;
}