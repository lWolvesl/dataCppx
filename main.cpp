#include "tools.cpp"
#include "chapter5/BiTNode.cpp"

/**
 * 为规范输出
 * 请将运行时代码填入此方法
 */
void runCode() {
    visitQueue(LevelOrder(*CreateTree(8)));
}

int main() {
    tStart();
    runCode();
    tEnd();
    return 0;
}