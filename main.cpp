#include "tools.cpp"
#include "chapter5/BiTNode.cpp"

/**
 * 为规范输出
 * 请将运行时代码填入此方法
 */
void runCode() {
    TreeNode *root = CreateTree(6);
    LevelOrder(*root);
}

int main() {
    tStart();
    runCode();
    tEnd();
    return 0;
}