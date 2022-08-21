#include <cstring>
#include "tools.cpp"

void test() {
    char *s = "12345";
    int i = 1;
    tLog(i);
}

int main() {
    char *g = getTime();
    printf("%s",g);
    printf(getTime());
    printf("\n");
    return 0;
}